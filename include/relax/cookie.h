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
#include <exception>
#include <stdexcept>
#include <mutex>
#include <relax/relax.h>

namespace relax {
namespace fetcher {

using std::map;
using std::string;
class Cookie;

class CookieManager {
public:
    /**
     * 获取一个cookie管理实例
     */
    static CookieManager& GetInstance();

    /**
     * 获取一个cookie实例
     * 返回的指针使用完不需要清楚
     *
     * 这里指针返回值比引用好，引用容易被误用，下面缺少&符号就出错了
     * Cookie& ck2=ckm->GetCookie("zjgsdx.com");
     */
    Cookie& GetCookie(string domain);

    /**
	 * 删除一个域名的Cookie实例
	 */
	Status DeleteDomain(string domain);

    /**
     * 重置整个Cookie库
     */
    Status reset();

private:
    CookieManager(){}
    ~CookieManager();
    CookieManager(const CookieManager&);
    CookieManager& operator = (const CookieManager&);

    //domain => cookie
    map<string, Cookie*> container_;
    static CookieManager* instance_;
    static std::mutex mutex_;
};

class CookieValue;
class CookieString;

class Cookie {
public:
    /**
     *添加一个cookie，多次添加直接覆盖
     */
    Status Add(CookieString cookie_obj);
    Status Add(string cookie_str);
    Status Add(string name, string value);

    //获取Cookie
    Status Get(string name, CookieValue& value);
    Status Get(string name, CookieString& obj);
    Status GetAll(string& value);

    Status Delete(string name);

protected:
    friend class CookieManager;
    Cookie(){}
    Cookie(const Cookie&);
    Cookie& operator = (const Cookie&);

private:
    // name => value
    map<string, CookieValue> container_;
    std::mutex mutex_;
};


//cookie值
class CookieValue {
public:
    CookieValue() :
            value_(""), path_("/"), expire_(0), httponly_(false), secure_(false) {
    }

    CookieValue(string cookie_str) :
            value_(cookie_str), path_("/"), expire_(0), httponly_(false), secure_(false) {
    }

    CookieValue(const CookieValue& cookie_obj) :
            value_(cookie_obj.value_), path_(cookie_obj.path_), expire_(cookie_obj.expire_),
            httponly_(cookie_obj.httponly_), secure_(cookie_obj.secure_) {
    }

    ~CookieValue() {
    }

    void Reset() {
        value_ = "";
        path_ = "";
        expire_ = 0;
        httponly_ = false;
        secure_ = false;
    }

    string value() {
        return value_;
    }

    Status set_value(string value) {
    	value_=value;
		return Status::GetOK();
	}

    string path() {
        return path_;
    }

    time_t expire() {
        return expire_;
    }

    bool httponly() {
        return httponly_;
    }

    bool secure() {
        return secure_;
    }

    CookieValue& operator=(const CookieValue& rvalue);

protected:
    string value_;

    string path_;

    /**
     * 过期时间
     *
     * >0 有效期 时间戳
     * =0 无期限
     * =-1 当前session有效
     */
    time_t expire_;

    bool httponly_;

    bool secure_;
};

//原始cookie解析字符串
/**
 * CookieString cookie字符串值
 *
 * ietf cookie: http://tools.ietf.org/html/rfc6265
 *
 * Set-Cookie:Token=v2gscbncfz5gk5bx4xphlkma4rlnvm13l65er8ix; expires=Fri, 20-Sep-2019 03:16:02 GMT; path=/; HttpOnly; secure;
 * Set-Cookie:spanner=peFXug9jwtvpRIuthTpRynbA4ws1VM1/;path=/;secure;
 * Set-Cookie:umt=HBf4721f420e82d869184a949e2eefcc2a; Domain=.alipay.com; Path=/; HttpOnly
 * Set-Cookie:CAT=deleted; expires=Fri, 27-Sep-2013 15:21:13 GMT
 * Set-Cookie:OUTFOX_SEARCH_USER_ID=551468692@58.101.75.242; domain=huihui.cn; path=/; expires=Mon, 19-Sep-2044 15:21:15 GMT
 */
class CookieString : public CookieValue {
public:
    const char* kDelimiter = ";";
    const char* kAssign = "=";

    CookieString() :
            name_(""), CookieValue() {
    }

    CookieString(string key, CookieValue value);

    CookieString(string str);

    ~CookieString() {
    }

    void Reset() {
        name_ = "";

        CookieValue::Reset();
    }

    string name() {
        return name_;
    }

    string ToString();

    string ToKVString() {
        return name_ + "=" + value_ + "; ";
    }

    CookieString& operator=(const CookieString& rvalue);

protected:
    string name_;
};

}//relax
}//fetcher

#endif//RELAX_FETCHER_COOKIE_H_
