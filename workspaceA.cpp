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

// Circular buffer class definition
class CircularBuffer {
 public:
  explicit CircularBuffer(size_t size) : buffer_(size), head_(0), tail_(0), full_(false), error_(false), end_of_stream_(false) {}

  bool write(const char* data, size_t bytes) {
    std::unique_lock<std::mutex> lock(mutex_);
    // Block the writer if the buffer is full and wait for the reader to consume
    cond_var_.wait(lock, [&] { return !full_ || error_; });

    if (error_) {
      std::cerr << "Buffer error detected, unable to write." << std::endl;
      return false;
    }

    for (size_t i = 0; i < bytes; ++i) {
      buffer_[head_] = data[i];
      head_ = (head_ + 1) % buffer_.size();
      if (head_ == tail_) {
        full_ = true;  // Buffer is full
        break;
      }
    }
    cond_var_.notify_one();  // Notify reader that data is available
    std::cerr << "Writing " << bytes << " bytes to buffer. Head: " << head_ << " Tail: " << tail_ << std::endl;
    return true;
  }

  size_t read(char* data, size_t max_bytes) {
    std::unique_lock<std::mutex> lock(mutex_);
    // Wait until there's data to read or the stream ends or an error occurs
    cond_var_.wait(lock, [&] { return (head_ != tail_ || end_of_stream_ || error_); });

    if (error_) {
      std::cerr << "Buffer error detected during read." << std::endl;
      return 0;  // Propagate the error
    }

    size_t bytes_read = 0;
    while (bytes_read < max_bytes && tail_ != head_) {
      data[bytes_read++] = buffer_[tail_];
      tail_ = (tail_ + 1) % buffer_.size();
      full_ = false;  // Data was consumed, so buffer is not full anymore
    }

    cond_var_.notify_one();  // Notify writer that space is available
    std::cerr << "Reading " << bytes_read << " bytes from buffer. Head: " << head_ << " Tail: " << tail_ << std::endl;
    return bytes_read;
  }

  void setEndOfStream() {
    std::unique_lock<std::mutex> lock(mutex_);
    end_of_stream_ = true;
    cond_var_.notify_all();
  }

  void setError() {
    std::unique_lock<std::mutex> lock(mutex_);
    error_ = true;
    cond_var_.notify_all();
  }

  bool hasError() const { return error_; }
  bool hasReachedEndOfStream() const { return end_of_stream_; }

 private:
  std::vector<char> buffer_;
  size_t head_, tail_;
  bool full_, error_, end_of_stream_;
  mutable std::mutex mutex_;
  std::condition_variable cond_var_;
};

struct DownloadMetaStruct {
 public:
  DownloadMetaStruct(Uptane::Target target_in, FetcherProgressCb progress_cb_in, const api::FlowControlToken* token_in)
      : hash_type{target_in.hashes()[0].type()},
        target{std::move(target_in)},
        token{token_in},
        progress_cb{std::move(progress_cb_in)},
        time_lastreport{std::chrono::steady_clock::now()},
        has_error(false),
        has_reached_end_of_stream(false) {}

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
  std::chrono::time_point<std::chrono::steady_clock> time_lastreport;

  CircularBuffer buffer{8196};  // Buffer size

  // Flags for error and end-of-stream handling
  bool has_error;
  bool has_reached_end_of_stream;

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
// std::shared_ptr<INvStorage> storage;
// std::shared_ptr<PackageManagerInterface> packageManager;
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

  if (dst->has_error || dst->has_reached_end_of_stream) {
    return CURL_WRITEFUNC_ERROR;  // If an error occurred or the stream ended, abort
  }

  if ((dst->downloaded_length + downloaded) > expected) {
    return downloaded + 1;  // curl will abort if return unexpected size;
  }

  if (!dst->buffer.write(contents, downloaded)) {
    dst->buffer.setError();  // If buffer failed to write, propagate the error
    std::cerr << "Failed to write to buffer." << std::endl;
    return CURL_WRITEFUNC_ERROR;
  }

  dst->fhandle.write(contents, static_cast<std::streamsize>(downloaded));
  dst->hasher().update(reinterpret_cast<const unsigned char*>(contents), downloaded);
  dst->downloaded_length += downloaded;

  // Check if we've reached the end of the download
  if (dst->downloaded_length >= expected) {
      std::cout << "Download complete, setting end of stream." << std::endl;
      dst->buffer.setEndOfStream();  // Signal that no more data is coming
      dst->has_reached_end_of_stream = true;  // Set the flag
  }

  return downloaded;
}

int readimage(char **pbuf, int *size) {
  std::printf("reading..\n");

  static char temp_buf[8196];  // Making this buffer static so it persists
  size_t bytes_read = ds->buffer.read(temp_buf, sizeof(temp_buf));

  std::cerr << "Bytes read from buffer in readimage: " << bytes_read << std::endl;

  if (bytes_read > 0) {
    *pbuf = temp_buf;  // Pointing to the persistent buffer
    *size = bytes_read;
    return bytes_read;
  }

  if (ds->buffer.hasError()) {
    std::fprintf(stderr, "Error occurred while reading downloaded data.\n");
    return -1;
  }

  if (ds->buffer.hasReachedEndOfStream()) {
    std::cerr << "End of stream detected in readimage." << std::endl;
    return 0;  // Signal that no more data is expected
  }

  return 0;
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
    std::printf("Final hash %s", final_hash.c_str());
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

  HttpResponse response = http->download(
    url,
    DownloadHandler,
    nullptr,  // ProgressHandler can be added if needed
    ds.get(), // userp
    static_cast<curl_off_t>(ds->downloaded_length)  // from
  );

  if (!response.isOk()) {
    std::cerr << "Download failed with HTTP response code: " << response.getStatusStr() << std::endl;
    ds->buffer.setError();  // Propagate error to the reader side
  } else {
    std::cout << "Download completed successfully, setting end of stream." << std::endl;
    ds->buffer.setEndOfStream();  // Signal end of stream after download completes
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
