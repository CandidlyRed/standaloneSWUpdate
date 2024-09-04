#include <iostream>
#include <fstream>
#include <string>
#include <pthread.h>
#include "json/json.h"
#include "libaktualizr/packagemanagerinterface.h"
#include "libaktualizr/packagemanagerfactory.h"
#include "libaktualizr/config.h"
#include "http/httpclient.h"
#include "storage/invstorage.h"

extern "C" {
#include "network_ipc.h"
}

Json::Value jsonDataOut;

static pthread_mutex_t mymutex;
static pthread_cond_t cv_end = PTHREAD_COND_INITIALIZER;

int verbose = 1;
char buf[256];
size_t bytes_read;

std::shared_ptr<HttpInterface> http;
std::shared_ptr<INvStorage> storage;
std::shared_ptr<PackageManagerInterface> packageManager;

int parseJsonFile(const std::string& jsonFilePath, Json::Value& jsonData) {
  std::ifstream jsonFile(jsonFilePath, std::ifstream::binary);
  if (!jsonFile.is_open()) {
    std::cerr << "JSON could not be opened: " << jsonFilePath << std::endl;
    return 1;
  }

  Json::CharReaderBuilder readerBuilder;
  std::string errs;

  if (!Json::parseFromStream(readerBuilder, jsonFile, &jsonData, &errs)) {
    return 1;
  }
  return 0;
}

int readimage(char **pbuf, int *size) {
  std::string target_url = jsonDataOut["target"]["url"].asString();

  auto response = http->download(target_url,
    [](const void* contents, size_t sizeT, size_t nmemb, void* userp) {
      size_t downloaded = size * nmemb;
      auto* ds = reinterpret_cast<DownloadState*>(userp);
      ds->hasher().update(reinterpret_cast<const unsigned char*>(contents), downloaded);
      return downloaded;
    },
    nullptr,  // ProgressHandler can be added if needed
    *pbuf,
    0
  );

  // if (response == CURLE_OK) {
  //   *size = bytes_read;
  //   return 0;
  // }
  return -1;
}

int printstatus(ipc_message *msg) {
  if (verbose) {
    std::printf("Status: %d message: %s\n",
              msg->data.notify.status,
              msg->data.notify.msg);
  }
  return 0;
}

int end(RECOVERY_STATUS status) {
  int end_status = (status == SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE;
  std::printf("SWUpdate %s\n", (status == FAILURE) ? "*failed* !" : "was successful !");

  if (status == SUCCESS) {
    std::printf("Executing post-update actions.\n");
    // Finalize the hash
    // https://github.com/rborn-tx/aktualizr/blob/ada682bac636f351d7811a498efbf5ff2b64760c/src/libaktualizr/package_manager/ostreemanager.cc#L384
    // auto final_hash = packageManager->getCurrentHash();
    // if (final_hash != jsonDataOut["custom"]["swupdate"]["rawHashes"]["sha256"].asString()) {
    //   std::fprintf(stderr, "Running post-update failed!\n");
    //   end_status = EXIT_FAILURE;
    //   // does end_status actually cancel the update?
    // }
  }

  pthread_mutex_lock(&mymutex);
  pthread_cond_signal(&cv_end);
  pthread_mutex_unlock(&mymutex);

  return end_status;
}

int swupdate_test_func(const std::string& url) {
  struct swupdate_request req;
  int rc;

  // Initialize the actual `PackageManagerInterface`
  PackageConfig pconfig;
  BootloaderConfig bconfig;
  packageManager = PackageManagerFactory::makePackageManager(pconfig, bconfig, storage, http);

  swupdate_prepare_req(&req);

  rc = swupdate_async_start(readimage, printstatus, end, &req, sizeof(req));
  if (rc < 0) {
    std::cout << "swupdate start error" << std::endl;
    pthread_mutex_unlock(&mymutex);
    return -1;
  }

  pthread_mutex_lock(&mymutex);
  pthread_cond_wait(&cv_end, &mymutex);
  pthread_mutex_unlock(&mymutex);

  return 0;
}

int main() {
  std::string url = "https://link.storjshare.io/s/juoufh4dg6rfg4jkbcmyu5lvsggq/gsoc/swupdate-torizon-benchmark-image-verdin-imx8mm-20240702064741.swu?download=1";
  std::string jsonFilePath = "../test.json";

  if (parseJsonFile(jsonFilePath, jsonDataOut) == 0) {
      swupdate_test_func(url);
  }

  return 0;
}
