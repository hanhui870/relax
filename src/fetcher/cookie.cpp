#include <relax/cookie.h>
#include <vector>
#include <relax/string_helper.h>
#include <exception>

namespace relax {
namespace fetcher {

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
    const char kDelimiter=';';
    const char kAssign='=';

    CookieString(string str) :
            expire_(0), httponly_(false), secure_(false) {

        using relax::utility::StringHelper;
        auto result=StringHelper::explode(StringHelper::trim(str), string(kDelimiter));

        try{
            //处理name
            //TODO parse 这里的解析应该用at，而不是直接数组。参数env_helper
           if(result[0].find(kAssign)!=string::npos){
               name_=result[0].substr(0, result[0].find(kAssign));
               value_=result[0].substr(result[0].find(kAssign)+1);
           }else{
               name_=result[0];
               value_=string();
           }

        }catch(std::out_of_range & exception){

        }

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

CookieManager* CookieManager::instance_ = NULL;

CookieManager* CookieManager::GetInstance() {
    if (CookieManager::instance_ == NULL) {
        CookieManager::instance_ = new CookieManager();
    }

    return CookieManager::instance_;
}

Cookie& CookieManager::GetCookie(string domain) {
    return container_[domain];
}

Cookie* Cookie::Add(CookieString cookie_obj) {
    container_[cookie_obj.name()] = CookieValue(cookie_obj);

    return this;
}

Cookie* Cookie::Add(const char* cookie_str) {
    return Add(CookieString(cookie_str));
}

Cookie* Cookie::Add(string name, string value) {
    container_[name] = CookieValue(value);

    return this;
}

string Cookie::Get(string name) {
    if(container_.count(name)){
        return container_[name];
    }

    return string();
}

} //relax
} //fetcher
