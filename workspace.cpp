#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <pthread.h>
#include <openssl/sha.h>
#include <curl/curl.h>
#include "json/json.h"
#include "libaktualizr/packagemanagerinterface.h"

extern "C" {
#include "network_ipc.h"
}

struct DownloadState {
    std::vector<char> buffer;
    bool pause;
};

Json::Value jsonDataOut;

int connfg;

char buf[256];
// std::ifstream updateFile;
size_t bytes_read;
CURL *curl;
CURLcode res;
DownloadState state = {std::vector<char>(), false};

int verbose = 1;
static pthread_mutex_t mymutex;
static pthread_cond_t cv_end = PTHREAD_COND_INITIALIZER;

SHA256_CTX sha256;

size_t write_callback(void* ptr, size_t, size_t nmemb, void* userdata) {
    size_t totalSize = size * nmemb;
    DownloadState* state = static_cast<DownloadState*>(userdata);
    state->buffer.insert(state->buffer.end(), (char*)ptr, (char*)ptr + totalSize);
    if (state->pause) {
        return CURL_WRITEFUNC_PAUSE;
    }
    return totalSize;
}

size_t read_incrementally(CURL* curl, DownloadState& state, char* buffer, size_t buffer_size) {
    if (state.buffer.empty() && !state.pause) {
        // Resume download if buffer is empty
        curl_easy_pause(curl, CURLPAUSE_CONT);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            return 0;
        }
    }

    // Copy data from the download buffer to the provided buffer
    size_t copy_size = std::min(buffer_size, state.buffer.size());
    std::copy(state.buffer.begin(), state.buffer.begin() + copy_size, buffer);
    state.buffer.erase(state.buffer.begin(), state.buffer.begin() + copy_size);

    return copy_size;
}

std::string hash_to_string(unsigned char hash[SHA256_DIGEST_LENGTH]) {
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}

// json parser
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

// functions for swupdate_async_start
int readimage(char **pbuf, int *size)
{
    //libcurl should incrementally read from url
    // updateFile.read(buf, sizeof(buf));
    while((bytes_read = read_incrementally(curl, state, buf, sizeof(buf))) > 0) {
        *pbuf = buf;
    }
    //updateFile.gcount()
    SHA256_Update(&sha256, buf, bytes_read);

    // SHA256_CTX temp_ctx = sha256;
    // unsigned char temp_hash[SHA256_DIGEST_LENGTH];
    // SHA256_Final(temp_hash, &temp_ctx);

    // if (hash_to_string(temp_hash) != GIVENHASH) {
    //     end(EXIT_FAILURE);
    // }

	// return updateFile.gcount();
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

int end(RECOVERY_STATUS status)
{
	int end_status = (status == SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE;

	std::printf("SWUpdate %s\n", (status == FAILURE) ? "*failed* !" : "was successful !");

	if (status == SUCCESS) {
		std::printf("Executing post-update actions.\n");
		ipc_message msg;
        // final check
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_Final(hash, &sha256)
		if (hash_to_string(hash) != jsonDataOut["custom"]["swupdate"]["rawHashes"]["sha256"].asString()) {
            std::fprintf(stderr, "Running post-update failed!\n");
			end_status = EXIT_FAILURE; // sending exit_failure cancels the rest
		}
	}

	pthread_mutex_lock(&mymutex);
	pthread_cond_signal(&cv_end);
	pthread_mutex_unlock(&mymutex);

	return 0;
}

int swupdate_test_func(const std::string& url) {
    // std::cout << "URL: " << url << std::endl;
    // std::cout << "JSON data: " << target.toStyledString() << std::endl;

    struct swupdate_request req;
    int rc;

    // updateFile.open("../swupdate-torizon-benchmark-image-verdin-imx8mm.swu");
    // if (!updateFile) {
    //     std::cout << "Error opening file" << std::endl;
    //     return -1;
    // }
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl) {
        return -1;
    }
    curl_easy_setopt(curl, CURLOPT_URL, "example.com");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &state);

    SHA256_Init(&sha256)

    swupdate_prepare_req(&req);

    rc = swupdate_async_start(readimage, printstatus, end, &req, sizeof(req));
    if (rc < 0) {
        std::cout << "swupdate start error" << std::endl;
        pthread_mutex_unlock(&mymutex);
        // updateFile.close();
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return -1;
    }

    pthread_mutex_lock(&mymutex);
	pthread_cond_wait(&cv_end, &mymutex);
	pthread_mutex_unlock(&mymutex);

    // updateFile.close();
    curl_easy_cleanup(curl);
    curl_global_cleanup();

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