#include <relax/time_helper.h>
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

    sec = static_cast<second>(mktime(&tm));

    return Status::GetOK();
}

} //relax
} //utility
