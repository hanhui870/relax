/**
 * chuilib hui cpp library
 *
 * curl fetcher http client
 *
 * @author 祝景法
 * @since 2014/06/30
 */
#ifndef HUILIB_FETCHER_CURL_H_
#define HUILIB_FETCHER_CURL_H_

#include <string>
#include <map>
#include <atomic>
#include <curl/curl.h>

namespace huilib {
namespace fetcher {

using ::std::string;

/**
 * curl资源连接器
 */
class Curl {
public:
	Curl();
    ~Curl();

    /**
     * get参数可以附带在url中
     */
    string get(string url);
    string get(const char* url);

    /**
     * post参数传递通过map
     */
    string post(string url, string param);
    string post(const char* url, const char* param);

    /**
     * 设置最大跟踪数
     */
    bool setMaxFollow(long num);

    /**
     * 全局初始化curl一次
     */
    static bool GlobalInit();

    /**
     * 全局清空curl一次
     */
    static bool GlobalClean();

    /**
     * 响应内容写入工具
     */
    static int Writer(char *data, size_t size, size_t nmemb,std::string *writerData);

private:
    bool InitCurl();

    CURL* curl_;

    //响应内容
    string responce_;

    //错误信息
    char* error_buffer_;

    //最大跟踪跳转
    long max_follow_;

    static std::atomic<bool> global_inited_;

};

std::atomic<bool> Curl::global_inited_(false);

} //huilib
} //fetcher

#endif
