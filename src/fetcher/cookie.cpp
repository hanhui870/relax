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
 * ietf cookie: http://www.ietf.org/rfc/rfc6265.txt
 *
 * Set-Cookie:Token=v2gscbncfz5gk5bx4xphlkma4rlnvm13l65er8ix; expires=Fri, 20-Sep-2019 03:16:02 GMT; path=/; HttpOnly; secure;
 * Set-Cookie:spanner=peFXug9jwtvpRIuthTpRynbA4ws1VM1/;path=/;secure;
 * Set-Cookie:umt=HBf4721f420e82d869184a949e2eefcc2a; Domain=.alipay.com; Path=/; HttpOnly
 * Set-Cookie:CAT=deleted; expires=Fri, 27-Sep-2013 15:21:13 GMT
 * Set-Cookie:OUTFOX_SEARCH_USER_ID=551468692@58.101.75.242; domain=huihui.cn; path=/; expires=Mon, 19-Sep-2044 15:21:15 GMT
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
            //parse 这里的解析应该用at，而不是直接数组。参数env_helper
           if(result.at(0).find(kAssign)!=string::npos){
               name_=result.at(0).substr(0, result.at(0).find(kAssign));
               value_=result.at(0).substr(result.at(0).find(kAssign)+1);
           }else{
               name_=result.at(0);
               value_=string();
           }

           if(result.at(1)){

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
