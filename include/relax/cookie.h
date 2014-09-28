/**
 * Relax library
 *
 * @author 祝景法
 * @email zhujingfa@gmail.com
 *
 * @since 2014/09/17
 */
#ifndef RELAX_FETCHER_COOKIE_H_
#define RELAX_FETCHER_COOKIE_H_

#include <map>
#include <string>
#include <relax/relax.h>

namespace relax {
namespace fetcher {

using std::map;
using std::string;

class Cookie;

class CookieManager {
public:
    CookieManager() {
    }

    ~CookieManager() {

    }

    /**
     * 获取一个cookie管理实例
     */
    static CookieManager* GetInstance();

    /**
     * 获取一个cookie实例
     */
    Cookie& GetCookie(string domain);

private:
    //domain => cookie
    map<string, Cookie> container_;

    static CookieManager* instance_;
};

//原始cookie解析字符串
class CookieString;
//cookie值
class CookieValue;

class Cookie {
public:
    Cookie() {
    }

    ~Cookie() {

    }

    /**
     *添加一个cookie，多次添加直接覆盖
     */
    Status Add(CookieString& cookie_obj);
    Status Add(string cookie_str);
    Status Add(string name, string value);

    //获取Cookie
    Status Get(string name, string& value);

    Status Delete(string name) {
        decltype(container_)::size_type deleted=container_.erase(name);

        if(deleted>0){
            return Status::GetOK();
        }else{
            return Status::GetFail();
        }
    }

    string ToString();

private:
    // name => value
    map<string, CookieValue> container_;
};

} //relax
} //fetcher

#endif//RELAX_FETCHER_COOKIE_H_
