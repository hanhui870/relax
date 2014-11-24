#include <relax/time_helper.h>
#include <stdlib.h>
#include "datetime.h"

namespace relax {
namespace utility {

const char* TimeHelper::kCookieFormat = "%a, %d-%b-%Y %T %Z";

/**
 * 将Cookie时间转换为时间戳
 *
 * Fri, 20-Sep-2019 03:16:02 GMT;
 */
Status TimeHelper::CookieTimeToStamp(string str, second& sec) {
    struct tm tm;
    memset(&tm, 0, sizeof(tm));

    try {
        tm = datetimelite::time_from_string(str);
    } catch (std::exception& e) {
        string s("invalid format: ");
        return Status::GetFail().set_message(s+ e.what());
    }

    //mktime也是时区相关的
    second tmp;
    Status s=TmToStamp(tm, tmp);
    if(s.IsOK()){
    	sec=tmp;
    }

    return s;
}

/**
 * 将Cookie时间转换为时间戳
 *
 * 解决时区依赖，转换为UTC情况下的
 */
Status TimeHelper::TmToStamp(struct tm &tm, second& sec){
	//返回的指向内部指针的，因为必须使用string重新拷贝一份
	string value=getenv("TZ");
	setenv("TZ", "", 1);

	sec = static_cast<second>(mktime(&tm));

	setenv("TZ", value.c_str(), 1);

	return Status::GetOK();
}

} //relax
} //utility
