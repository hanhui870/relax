#include <relax/cookie.h>
#include <vector>

namespace relax {
namespace fetcher {

CookieManager* CookieManager::instance_ = NULL;

CookieManager* CookieManager::GetInstance() {
    if (CookieManager::instance_ == NULL) {
        CookieManager::instance_ = new CookieManager();
    }

    return CookieManager::instance_;
}

Cookie* Cookie::Add(CookieString cookie_str) {

    return this;
}

Cookie* Cookie::Add(string name, string value) {
    container_[name] = CookieValue(value);

    return this;
}

class CookieValue {
public:
    CookieValue(string cookie_str) :
            value_(cookie_str), path_("/"), expire_(0), httponly_(false), secure_(false) {
    }

    CookieValue(CookieString cookie_obj) :
            value_(cookie_obj.value()), path_(cookie_obj.path()), expire_(cookie_obj.expire()),
            httponly_(cookie_obj.httponly()), secure_(cookie_obj.secure()) {
    }

    ~CookieValue() {
    }

private:
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

/**
 * CookieString cookie字符串值
 *
 * Set-Cookie:Token=v2gscbncfz5gk5bx4xphlkma4rlnvm13l65er8ix; expires=Fri, 20-Sep-2019 03:16:02 GMT; path=/; HttpOnly; secure;
 */
class CookieString {
public:
    CookieString(string str) :
            expire_(0), httponly_(false), secure_(false) {

        string::size_type pos=str.find(';');


    }

    ~CookieString() {

    }

    string name() {
        return name_;
    }

    string value() {
        return value_;
    }

    string path() {
        return path_;
    }

    string expire() {
        return expire_;
    }

    string httponly() {
        return httponly_;
    }

    string secure() {
        return secure_;
    }

    string ToString() {
        string result = name_ + "=" + value_ + "; " + "path=" + path_ + "; "+ "expires=" + expire_ + "; ";
        if (httponly_) {
            result + " HttpOnly;";
        }
        if (secure_) {
            result + " secure;";
        }
        return result;
    }

private:
    string name_;

    string value_;

    string path_;

    time_t expire_;

    bool httponly_;

    bool secure_;
};

} //relax
} //fetcher
