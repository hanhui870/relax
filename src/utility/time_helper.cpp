#include <time.h>
#include <sys/time.h>
#include <relax/time_helper.h>
#include <stdlib.h>
#include <cstring>
#include "datetime.h"

namespace relax {
namespace utility {

using std::memset;
const char* TimeHelper::kCookieFormat = "%a, %d-%b-%Y %T %Z";

/**
 * 获取UTC微秒级时间戳
 */
TimeHelper::micro TimeHelper::MicroTime(){
    struct timeval timestamp;

    //return 0 for success, or -1 for failure
    if(gettimeofday(&timestamp, NULL)==-1){
        return -1;
    }

    return static_cast<micro>(timestamp.tv_sec)*kMicroRatio+timestamp.tv_usec;
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
 * 将时间戳转换为Cookie时间
 */
Status TimeHelper::StampToCookieTime(second sec, string& result){
    char buffer[kBufferSize];

    struct tm* tm = gmtime(&sec);

    size_t s=strftime(buffer, kBufferSize, kCookieFormat, tm);
    if (s == 0) {
        return Status::GetFail().set_message("Error strftime.");
    }else{
        result = string(buffer);
        return Status::GetOK();
    }
}

} //relax
} //utility
