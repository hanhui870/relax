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
#include <relax/relax.h>
#include <relax/string_helper.h>
#include <relax/time_helper.h>

namespace relax {
namespace fetcher {

using std::map;
using std::string;
using std::exception;
using std::invalid_argument;
using utility::StringHelper;
using relax::utility::TimeHelper;

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

class CookieValue;

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
class CookieString {
public:
    const char* kDelimiter = ";";
    const char* kAssign = "=";

    CookieString() :
            name_(""), value_(""), path_("/"), expire_(0), httponly_(false), secure_(false) {
    }

    CookieString(string key, CookieValue value);

    CookieString(string str) :
            expire_(0), httponly_(false), secure_(false) {

        using relax::utility::StringHelper;
        auto result = StringHelper::Explode(StringHelper::Trim(str), kDelimiter);

        //处理name
        //parse 这里的解析应该用at，而不是直接数组。参数env_helper
        {
            string& tmp =  result.at(0);
            if (tmp.find(kAssign) != string::npos) {
                name_ = tmp.substr(0, tmp.find(kAssign));
                value_ = tmp.substr(tmp.find(kAssign) + 1);
            } else {
                //Exception 无效的cookie
                throw invalid_argument(string("Invalid cookie string: ") + str);
            }
        }

        std::vector<string>::size_type size;
        for (size = 1; size < result.size(); size++) {
            string& tmp = result.at(size);
            if(StringHelper::Trim(tmp).size()==0) continue;

            if (tmp.find(kAssign) != string::npos) {
                string key = StringHelper::Trim(tmp.substr(0, tmp.find(kAssign)));
                string value = StringHelper::Trim(tmp.substr(tmp.find(kAssign) + 1));
                if(key.size()==0) continue;

                string up;
                StringHelper::ToUpper(key, up);

                if (up.compare("EXPIRES") == 0) {
                    TimeHelper::second sec;
                    Status s=TimeHelper::CookieTimeToStamp(value, sec);
                    if(s.IsOK()){
                        expire_ = sec;
                    }else{
                        throw invalid_argument(string("Invalid cookie expire string: ") + value);
                    }

                } else if (up.compare("PATH") == 0) {
                    path_ = value;
                }

            } else {
                string key = StringHelper::Trim(tmp);
                if(key.size()==0) continue;

                string up;
                StringHelper::ToUpper(key, up);

                if (up.compare("HTTPONLY") == 0) {
                    httponly_ = true;
                } else if (up.compare("SECURE") == 0) {
                    secure_ = true;
                }
            }
        }
    }

    ~CookieString() {

    }

    void Reset() {
        name_ = "";
        value_ = "";
        path_ = "";
        expire_ = 0;
        httponly_ = false;
        secure_ = false;
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

    time_t expire() {
        return expire_;
    }

    bool httponly() {
        return httponly_;
    }

    bool secure() {
        return secure_;
    }

    string ToString() {
        string time;
        TimeHelper::StampToCookieTime(expire_, time);
        string result = name_ + "=" + value_ + ";" + " expires=" + time + ";"+ " path=" + path_ + ";";
        if (httponly_) {
            result += " HttpOnly;";
        }
        if (secure_) {
            result += " Secure;";
        }
        return result;
    }

    string ToKVString() {
        return name_ + "=" + value_ + "; ";
    }

    CookieString& operator=(const CookieString& rvalue);

private:
    string name_;

    string value_;

    string path_;

    time_t expire_;

    bool httponly_;

    bool secure_;
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

    CookieValue(CookieString& cookie_obj) :
            value_(cookie_obj.value()), path_(cookie_obj.path()), expire_(cookie_obj.expire()),
            httponly_(cookie_obj.httponly()), secure_(cookie_obj.secure()) {
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
    Status Get(string name, CookieValue& value);
    Status Get(string name, CookieString& obj);
    Status GetAll(string& value);

    Status Delete(string name) {
        decltype(container_)::size_type deleted=container_.erase(name);

        if(deleted>0) {
            return Status::GetOK();
        } else {
            return Status::GetFail();
        }
    }

    string ToString();

private:
    // name => value
    map<string, CookieValue> container_;
};

}//relax
}//fetcher

#endif//RELAX_FETCHER_COOKIE_H_
