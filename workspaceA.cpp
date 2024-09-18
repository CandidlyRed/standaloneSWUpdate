#include <iostream>
#include <fstream>
#include <string>
#include <pthread.h>
#include "json/json.h"
#include "libaktualizr/packagemanagerfactory.h"
#include "http/httpclient.h"
#include <unistd.h>  // For the read system call
#include <fcntl.h>   // For open, O_RDONLY

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

#include <mutex>
#include <condition_variable>
#include <queue>

std::mutex buffer_mutex;
std::condition_variable buffer_cv;
std::queue<std::vector<char>> data_queue; // A queue to hold chunks of data

// Flags to control the flow
bool pause_download = false;
bool stop_download = false;

struct DownloadMetaStruct {
 public:
  DownloadMetaStruct(Uptane::Target target_in, FetcherProgressCb progress_cb_in, const api::FlowControlToken* token_in)
      : hash_type{target_in.hashes()[0].type()},
        target{std::move(target_in)},
        token{token_in},
        progress_cb{std::move(progress_cb_in)},
        time_lastreport{std::chrono::steady_clock::now()} {
    // Open the file for writing in the constructor
    fhandle.open("output_file_path", std::ios::binary | std::ios::out);
    if (!fhandle.is_open()) {
        std::cerr << "Failed to open the file for writing." << std::endl;
        throw std::runtime_error("Failed to open file");
    }
  }
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

std::string url = "https://link.storjshare.io/s/jwlztdmw6o6rizo6nj3f2bo6obka/gsoc/swupdate-torizon-benchmark-image-verdin-imx8mm-20240907181051.swu?download=1";
std::shared_ptr<HttpInterface> http;
std::unique_ptr<DownloadMetaStruct> ds;

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
        std::cerr << "Download size exceeds expected length." << std::endl;
        return downloaded + 1; // Abort download
    }

    try {
        if (!dst->fhandle.is_open()) {
            std::cerr << "File not open for writing in DownloadHandler." << std::endl;
            return 0; // Abort download
        }

        dst->fhandle.write(contents, static_cast<std::streamsize>(downloaded));
        if (!dst->fhandle) {
            std::cerr << "Error writing to file." << std::endl;
            return 0; // Abort download
        }

        dst->hasher().update(reinterpret_cast<const unsigned char*>(contents), downloaded);
        dst->downloaded_length += downloaded;
        // std::cout << "Downloaded: " << dst->downloaded_length << "/" << expected << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception in DownloadHandler: " << e.what() << std::endl;
        return 0; // Abort download
    }

    return downloaded;
}


int readimage(char** pbuf, int* size) {
    std::unique_lock<std::mutex> lock(buffer_mutex);

    // Wait until there is data in the buffer or download is stopped
    while (data_queue.empty() && !stop_download) {
        buffer_cv.wait(lock);
    }

    if (stop_download) {
        return -1;
    }

    // Get the data from the queue
    auto& buffer = data_queue.front();
    *pbuf = const_cast<char*>(buffer.data());
    *size = static_cast<int>(buffer.size());
    data_queue.pop();

    return *size;
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
  ds->fhandle.flush();
  if (!ds->fhandle) {
      std::cerr << "Error flushing file." << std::endl;
      return 0; // Abort download
  }

  int end_status = (status == SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE;
  std::printf("SWUpdate %s\n", (status == FAILURE) ? "*failed* !" : "was successful !");

  if (status == SUCCESS) {
    std::printf("Executing post-update actions.\n");
    // Finalize the hash
    auto final_hash = ds->hasher().getHash().HashString();
    std::printf("Final hash %s", final_hash.c_str());
    std::string val = "";
    // val = jsonDataOut["custom"]["swupdate"]["rawHashes"]["sha256"].asString();
    if (final_hash != val) {
      std::fprintf(stderr, "Running post-update failed!\n");
      end_status = EXIT_FAILURE;
    }
  }

  // Close the file handle
  if (ds->fhandle.is_open()) {
    ds->fhandle.close();
  }

  pthread_mutex_lock(&mymutex);
  pthread_cond_signal(&cv_end);
  pthread_mutex_unlock(&mymutex);

  return end_status;
}

int swupdate_test_func() {
  struct swupdate_request req;
  int rc;

  http = std::make_shared<HttpClient>();
  Uptane::Target target("test", jsonDataOut);
  ds = std_::make_unique<DownloadMetaStruct>(target, nullptr, nullptr);

  swupdate_prepare_req(&req);

  rc = swupdate_async_start(readimage, printstatus, end, &req, sizeof(req));
  if (rc < 0) {
    std::cout << "swupdate start error" << std::endl;
    pthread_mutex_unlock(&mymutex);
    return -1;
  }

  HttpResponse response = http->download(
    url,
    DownloadHandler,
    nullptr,  // ProgressHandler can be added if needed
    ds.get(), // userp
    static_cast<curl_off_t>(ds->downloaded_length)  // from
  );

  {
      std::unique_lock<std::mutex> lock(buffer_mutex);
      stop_download = true;
      buffer_cv.notify_all(); // Notify to break out of waiting in readimage
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