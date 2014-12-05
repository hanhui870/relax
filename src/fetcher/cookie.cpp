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

CookieString::CookieString(string str) :
		CookieValue(){

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

CookieString::CookieString(string key, CookieValue value) :
    name_(key), CookieValue(value) {
}

string CookieString::ToString() {
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
    //有效期小于当前删除Cookie
    if(cookie_obj.expire()>0 && cookie_obj.expire()<TimeHelper::Time()){
        return Delete(cookie_obj.name()).set_message("expire<Now, delete it.");
    }
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
    value.Reset();
    return Status::GetFail();
}
//获取为CookieString版本
Status Cookie::Get(string name, CookieString& obj) {
    if(container_.count(name)){
        CookieValue value=container_[name];
        obj=CookieString(name, value);
        return Status::GetOK();
    }
    obj.Reset();
    return Status::GetFail();
}
//获取所有Cookie键值对
Status Cookie::GetAll(string& value) {
    if(container_.size()>0){
        map<string, CookieValue>::iterator pos;
        string result;
        for(pos=container_.begin(); pos!=container_.end(); pos++ ){
            result+=CookieString(pos->first, pos->second).ToKVString();
        }
        value=result;
        return Status::GetOK();
    }

    value="";
    return Status::GetFail().set_message("Empty cookie.");
}

Status Cookie::Delete(string name) {
	decltype(container_)::size_type deleted=container_.erase(name);

	if(deleted>0) {
		return Status::GetOK();
	} else {
		return Status::GetFail();
	}
}


} //relax
} //fetcher
