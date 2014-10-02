#include <vector>
#include <relax/cookie.h>

namespace relax {
namespace fetcher {

CookieValue& CookieValue::operator=(const CookieValue& rvalue){
    if(this != &rvalue){
        value_=rvalue.value_;
        path_=rvalue.path_;
        expire_=rvalue.expire_;
        httponly_=rvalue.httponly_;
        secure_=rvalue.secure_;
    }

    return *this;
}

CookieString::CookieString(string key, CookieValue value) :
    name_(key), value_(value.value()), path_(value.path()), expire_(value.expire()),
    httponly_(value.httponly()), secure_(value.secure()) {
}

CookieString& CookieString::operator=(const CookieString& rvalue){
    if(this != &rvalue){
        name_=rvalue.name_;
        value_=rvalue.value_;
        path_=rvalue.path_;
        expire_=rvalue.expire_;
        httponly_=rvalue.httponly_;
        secure_=rvalue.secure_;
    }

    return *this;
}

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

Status Cookie::Add(CookieString& cookie_obj) {
    container_[cookie_obj.name()] = CookieValue(cookie_obj);

    return Status::GetOK();
}

Status Cookie::Add(string cookie_str) {
    try{
        CookieString s(cookie_str);

        return Add(s);
    }catch(std::exception & exception){
        return Status::GetFail().set_message(exception.what());
    }
}

Status Cookie::Add(string name, string value) {
    container_[name] = CookieValue(value);

    return Status::GetOK();
}

/**
 * 获取cookie
 *
 * 客户端自己保证value的值是未使用过的，避免初始值的问题
 */
Status Cookie::Get(string name, CookieValue& value) {
    if(container_.count(name)){
        value=container_[name];
        return Status::GetOK();
    }

    return Status::GetFail();
}
//获取为CookieString版本
Status Cookie::Get(string name, CookieString& obj) {
    if(container_.count(name)){
        CookieValue value=container_[name];
        obj=CookieString(name, value);
        return Status::GetOK();
    }

    return Status::GetFail();
}

} //relax
} //fetcher
