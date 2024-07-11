#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <pthread.h>
// #include "curl/curl.h"
#include "json/json.h"

extern "C" {
#include "network_ipc.h"
}

char buf[256];
std::ifstream updateFile;

int verbose = 1;
static pthread_mutex_t mymutex;
static pthread_cond_t cv_end = PTHREAD_COND_INITIALIZER;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    std::ofstream *file = static_cast<std::ofstream*>(userp);
    file->write(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

// int curlWritetoFile(const std::string& url) {
//     CURL *curl;
//     CURLcode res;

//     std::ofstream file("output.txt", std::ofstream::binary);

//     curl_global_init(CURL_GLOBAL_DEFAULT);
//     curl = curl_easy_init();
//     if (curl) {
//         curl_easy_setopt(curl, CURLOPT_URL, url);
//         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
//         curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);

//         res = curl_easy_perform(curl);
//         if (res != CURLE_OK) {
//             fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
//         }

//         curl_easy_cleanup(curl);
//     }

//     file.close();
//     return 0;
// }

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

int readimage(char **pbuf, int *size)
{
    updateFile.read(buf, sizeof(buf));
	*pbuf = buf;
	return updateFile.gcount();
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
		msg.data.procmsg.len = 0;
		// if (ipc_postupdate(&msg) != 0 || msg.type != ACK) {
        //     std::fprintf(stderr, "Running post-update failed!\n");
		// 	end_status = EXIT_FAILURE;
		// }
	}

	pthread_mutex_lock(&mymutex);
	pthread_cond_signal(&cv_end);
	pthread_mutex_unlock(&mymutex);

	return 0;
}

int swupdate_test_func(const std::string& url, const Json::Value& target) {
    // std::cout << "URL: " << url << std::endl;
    // std::cout << "JSON data: " << target.toStyledString() << std::endl;

    struct swupdate_request req;
    int rc;

    updateFile.open("../swupdate-torizon-benchmark-image-verdin-imx8mm.swu");

    if (!updateFile) {
        std::cout << "Error opening file" << std::endl;
    }

    swupdate_prepare_req(&req);

    rc = swupdate_async_start(readimage, printstatus, end, &req, sizeof(req));
    if (rc < 0) {
        std::cout << "swupdate start error" << std::endl;
        return -1;
    }

    pthread_mutex_lock(&mymutex);
	pthread_cond_wait(&cv_end, &mymutex);
	pthread_mutex_unlock(&mymutex);

    updateFile.close();

    return 0;
}

int main() {
    std::string url = "https://example.com/update";
    std::string jsonFilePath = "../test.json";

    Json::Value jsonData;
    if (parseJsonFile(jsonFilePath, jsonData) == 0) {
        swupdate_test_func(url, jsonData);
    }

    return 0;
}