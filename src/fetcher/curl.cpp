/**
 * chuilib hui cpp library
 *
 * @author 祝景法
 * @since 2014/06/30
 */
#include <iostream>
#include <relax/curl.h>

namespace relax {
namespace fetcher {

using ::std::cout;
using ::std::endl;

Curl::Curl() :
		max_follow_(5), curl_(NULL) {
    //初始化一次
    std::call_once(global_inited_, GlobalInit);

	error_buffer_ = new char[CURL_ERROR_SIZE];
}

Curl::~Curl() {
	delete[] error_buffer_;
	curl_easy_cleanup(curl_);
}

/**
 * 全局初始化curl一次
 */
bool Curl::GlobalInit() {
	curl_global_init(CURL_GLOBAL_ALL);
	return true;
}

/**
 * 全局清空curl一次
 */
bool Curl::GlobalClean() {
	curl_global_cleanup();

	return true;
}

bool Curl::setMaxFollow(long num) {
	if (num < 0)
		return false;

	max_follow_ = num;
	return true;
}

/**
 * 获取失败返回空结果
 */
string Curl::get(string url) {
	if (curl_ == NULL && !InitCurl()) {
		cout << "Failed to call InitCurl " << error_buffer_ << endl;
		return string();
	}

	CURLcode code = curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
	if (code != CURLE_OK) {
		cout << "Failed to set URL " << error_buffer_ << endl;
		return string();
	}

	code = curl_easy_perform(curl_);
	if (code != CURLE_OK) {
		cout << "Failed to get " << url << " error: " << error_buffer_ << endl;
		return string();
	}

	return responce_;
}

string Curl::get(const char* url) {
	return Curl::get(std::string(url));
}

/**
 * post方式获取远程请求
 *
 * 获取失败返回空结果
 */
string Curl::post(string url, string param) {
	if (curl_ == NULL && !InitCurl()) {
		cout << "Failed to call InitCurl " << error_buffer_ << endl;
		return string();
	}

	CURLcode code = curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
	if (code != CURLE_OK) {
		cout << "Failed to set URL " << error_buffer_ << endl;
		return string();
	}

	code = curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, param.c_str());
	if (code != CURLE_OK) {
		cout << "Failed to set post fields " << error_buffer_ << endl;
		return string();
	}

	code = curl_easy_perform(curl_);
	if (code != CURLE_OK) {
		cout << "Failed to get " << url << " error: " << error_buffer_ << endl;
		return string();
	}

	return responce_;
}

//static 关键词在定义中使用一次即可，外部不能再次使用
int Curl::Writer(char *data, size_t size, size_t nmemb,
		std::string *writer_data) {
	if (writer_data == NULL) {
		return 0;
	}

	writer_data->append(data, size * nmemb);

	return size * nmemb;
}

bool Curl::InitCurl() {
	curl_ = curl_easy_init();
	if (curl_ == NULL) {
		cout << "Call curl_easy_init failed." << endl;
		return false;
	}

	CURLcode code;

	code = curl_easy_setopt(curl_, CURLOPT_ERRORBUFFER, error_buffer_);
	if (code != CURLE_OK) {
		cout << "Failed to set error buffer " << code << endl;
		return false;
	}

	code = curl_easy_setopt(curl_, CURLOPT_FOLLOWLOCATION, max_follow_);
	if (code != CURLE_OK) {
		cout << "Failed to set redirect option " << error_buffer_ << endl;
		return false;
	}

	code = curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, &Curl::Writer);
	if (code != CURLE_OK) {
		cout << "Failed to set writer " << error_buffer_ << endl;
		return false;
	}

	code = curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &responce_);
	if (code != CURLE_OK) {
		cout << "Failed to set write data " << error_buffer_ << endl;
		return false;
	}

	return true;
}

std::once_flag Curl::global_inited_;

} //relax
} //fetcher
