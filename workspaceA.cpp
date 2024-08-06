#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <pthread.h>
#include <chrono>
#include "json/json.h"

// Include headers from PackageManagerInterface
#include "libaktualizr/packagemanagerinterface.h"
#include "bootloader/bootloader.h"
#include "crypto/keymanager.h"
#include "http/httpclient.h"
#include "logging/logging.h"
#include "storage/invstorage.h"
#include "uptane/fetcher.h"
#include "utilities/apiqueue.h"

extern "C" {
#include "network_ipc.h"
}

Json::Value jsonDataOut;

struct DownloadState {
    std::vector<char> buffer;
    bool pause;
};

static pthread_mutex_t mymutex;
static pthread_cond_t cv_end = PTHREAD_COND_INITIALIZER;

DownloadState state = {std::vector<char>(), false};
int verbose = 1;
char buf[256];
size_t bytes_read;

size_t read_incrementally(PackageManagerInterface& package_manager, DownloadState& state, char* buffer, size_t buffer_size) {
    if (state.buffer.empty() && !state.pause) {
        // Resume download if buffer is empty
        package_manager.resumeDownload(); // This would be a custom method to handle resuming in your package manager
    }

    // Copy data from the download buffer to the provided buffer
    size_t copy_size = std::min(buffer_size, state.buffer.size());
    std::copy(state.buffer.begin(), state.buffer.begin() + copy_size, buffer);
    state.buffer.erase(state.buffer.begin(), state.buffer.begin() + copy_size);

    return copy_size;
}

std::string hash_to_string(const std::vector<unsigned char>& hash) {
    std::stringstream ss;
    for (const auto& byte : hash) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    return ss.str();
}

int parseJsonFile(const std::string& jsonFilePath, Json::Value& jsonData) {
    std::ifstream jsonFile(jsonFilePath, std::ifstream::binary);
    if (!jsonFile.is_open()) {
        std::cerr << "JSON could not be opened: " << jsonFilePath << std::endl;
        return 1;
    }

    Json::CharReaderBuilder readerBuilder;
    std::string errs;

    if (!Json::parseFromStream(readerBuilder, jsonFile, &jsonData, &errs)) {
        std::cerr << "JSON parsing error: " << errs << std::endl;
        return 1;
    }
    return 0;
}

int readimage(char **pbuf, int *size, PackageManagerInterface& package_manager) {
    while ((bytes_read = read_incrementally(package_manager, state, buf, sizeof(buf))) > 0) {
        *pbuf = buf;
        package_manager.updateHasher(reinterpret_cast<const unsigned char*>(buf), bytes_read);
    }
    return bytes_read;
}

int printstatus(ipc_message *msg) {
    if (verbose) {
        std::printf("Status: %d message: %s\n",
                    msg->data.notify.status,
                    msg->data.notify.msg);
    }
    return 0;
}

int end(RECOVERY_STATUS status, PackageManagerInterface& package_manager) {
    int end_status = (status == SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE;
    std::printf("SWUpdate %s\n", (status == FAILURE) ? "*failed* !" : "was successful !");

    if (status == SUCCESS) {
        std::printf("Executing post-update actions.\n");
        std::vector<unsigned char> hash = package_manager.finalizeHasher();
        if (hash_to_string(hash) != jsonDataOut["custom"]["swupdate"]["rawHashes"]["sha256"].asString()) {
            std::fprintf(stderr, "Running post-update failed!\n");
            end_status = EXIT_FAILURE;
        }
    }

    pthread_mutex_lock(&mymutex);
    pthread_cond_signal(&cv_end);
    pthread_mutex_unlock(&mymutex);

    return 0;
}

int swupdate_test_func(const std::string& url) {
    struct swupdate_request req;
    int rc;

    PackageManagerInterface package_manager;

    // Initialize and set up the package manager
    package_manager.init(url);

    package_manager.initHasher();

    swupdate_prepare_req(&req);

    rc = swupdate_async_start([&package_manager](char** pbuf, int* size) {
        return readimage(pbuf, size, package_manager);
    }, printstatus, [&package_manager](RECOVERY_STATUS status) {
        return end(status, package_manager);
    }, &req, sizeof(req));

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
    std::string url = "https://example.com/update";
    std::string jsonFilePath = "../test.json";

    if (parseJsonFile(jsonFilePath, jsonDataOut) == 0) {
        swupdate_test_func(url);
    }

    return 0;
}
