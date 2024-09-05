#include <iostream>
#include <fstream>
#include <string>
#include <pthread.h>
#include "json/json.h"
// #include "libaktualizr/packagemanagerinterface.h"
#include "libaktualizr/packagemanagerfactory.h"
// #include "libaktualizr/config.h"
#include "http/httpclient.h"
// #include "storage/invstorage.h"

extern "C" {
#include "network_ipc.h"
}

#include <sys/statvfs.h>
#include <boost/filesystem.hpp>
#include <chrono>

#include "crypto/crypto.h"
#include "crypto/keymanager.h"
#include "logging/logging.h"
#include "uptane/exceptions.h"
#include "uptane/fetcher.h"
#include "utilities/apiqueue.h"

struct DownloadMetaStruct {
 public:
  DownloadMetaStruct(Uptane::Target target_in, FetcherProgressCb progress_cb_in, const api::FlowControlToken* token_in)
      : hash_type{target_in.hashes()[0].type()},
        target{std::move(target_in)},
        token{token_in},
        progress_cb{std::move(progress_cb_in)},
        time_lastreport{std::chrono::steady_clock::now()} {}
  uintmax_t downloaded_length{0};
  unsigned int last_progress{0};
  std::ofstream fhandle;
  const Hash::Type hash_type;
  MultiPartHasher& hasher() {
    switch (hash_type) {
      case Hash::Type::kSha256:
        return sha256_hasher;
      case Hash::Type::kSha512:
        return sha512_hasher;
      default:
        throw std::runtime_error("Unknown hash algorithm");
    }
  }
  Uptane::Target target;
  const api::FlowControlToken* token;
  FetcherProgressCb progress_cb;
  // each LogProgressInterval msec log dowload progress for big files
  std::chrono::time_point<std::chrono::steady_clock> time_lastreport;

 private:
  MultiPartSHA256Hasher sha256_hasher;
  MultiPartSHA512Hasher sha512_hasher;
};

Json::Value jsonDataOut;

static pthread_mutex_t mymutex;
static pthread_cond_t cv_end = PTHREAD_COND_INITIALIZER;

int verbose = 1;
char buf[256];

std::string url = "https://link.storjshare.io/s/juoufh4dg6rfg4jkbcmyu5lvsggq/gsoc/swupdate-torizon-benchmark-image-verdin-imx8mm-20240702064741.swu?download=1";
std::shared_ptr<HttpInterface> http;
// std::shared_ptr<INvStorage> storage;
// std::shared_ptr<PackageManagerInterface> packageManager;
DownloadMetaStruct* ds;

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

static size_t DownloadHandler(char* contents, size_t size, size_t nmemb, void* userp) {
  assert(userp);
  auto* dst = static_cast<DownloadMetaStruct*>(userp);
  size_t downloaded = size * nmemb;
  uint64_t expected = dst->target.length();
  if ((dst->downloaded_length + downloaded) > expected) {
    return downloaded + 1;  // curl will abort if return unexpected size;
  }

  dst->fhandle.write(contents, static_cast<std::streamsize>(downloaded));
  dst->hasher().update(reinterpret_cast<const unsigned char*>(contents), downloaded);
  dst->downloaded_length += downloaded;
  return downloaded;
}

int readimage(char **pbuf, int *size) {
  // int ret;
	// ret = read(fd, buf, sizeof(buf));
	// *p = buf;
	// *size = ret;
	// return ret;
  // std::string target_url = jsonDataOut["target"]["url"].asString();

  auto response = http->downloadAsync(url,
    DownloadHandler,
    nullptr,  // ProgressHandler can be added if needed
    ds->get(), // userp
    static_cast<curl_off_t>(ds->downloaded_length), // from
    nullptr //curlhandler easyp*
  );

  if (response.isOk()) {
    *size = response;
    return size;
  }

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
    auto final_hash = ds->hasher().getHash().HashString();
    std::string val = "";
    // val = jsonDataOut["custom"]["swupdate"]["rawHashes"]["sha256"].asString();
    if (final_hash != val) {
      std::fprintf(stderr, "Running post-update failed!\n");
      end_status = EXIT_FAILURE;
      // does end_status actually cancel the update?
    }
  }

  pthread_mutex_lock(&mymutex);
  pthread_cond_signal(&cv_end);
  pthread_mutex_unlock(&mymutex);

  return end_status;
}

int swupdate_test_func() {
  struct swupdate_request req;
  int rc;

  // Initialize the actual `PackageManagerInterface`
  http = std::make_shared<HttpClient>();
  // PackageConfig pconfig;
  // BootloaderConfig bconfig;
  // packageManager = PackageManagerFactory::makePackageManager(pconfig, bconfig, storage, http);
  Uptane::Target target("test", jsonDataOut);
  ds = std_::make_unique<DownloadMetaStruct>(target, nullptr, nullptr);

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
  std::string jsonFilePath = "./test.json";

  if (parseJsonFile(jsonFilePath, jsonDataOut) == 0) {
    swupdate_test_func();
  }

  return 0;
}
