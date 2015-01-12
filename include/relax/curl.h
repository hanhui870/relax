/**
 * chuilib hui cpp library
 *
 * curl fetcher http client
 *
 * @author 祝景法
 * @since 2014/06/30
 */
#ifndef RELAX_FETCHER_CURL_H_
#define RELAX_FETCHER_CURL_H_

#include <string>
#include <map>
#include <mutex>
#include <functional>
#include <curl/curl.h>
#include <relax/relax.h>

namespace relax {

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
    Status get(string url, string& responce);

    /**
     * post参数传递通过map
     */
    Status post(string url, string param, string& responce);

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
    Status InitCurl();

    CURL* curl_;

    //响应内容
    string responce_;

    //错误信息
    char* error_buffer_;

    //最大跟踪跳转
    long max_follow_;

    static std::once_flag global_inited_;
};

} //huilib

#endif//RELAX_FETCHER_CURL_H_
