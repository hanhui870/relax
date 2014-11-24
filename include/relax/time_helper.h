/**
 * Relax library
 *
 * @author 祝景法
 * @email zhujingfa@gmail.com
 *
 * @since 2014/09/17
 */
#ifndef RELAX_UTILITY_TIME_HELPER_H_
#define RELAX_UTILITY_TIME_HELPER_H_

#include <ratio>
#include <ctime>
#include <string>
#include <cstring>
#include <time.h>
#include <sys/time.h>
#include <relax/relax.h>

namespace relax {
namespace utility {

using std::string;
using std::memset;

class TimeHelper{
public:
	typedef long long micro;
	typedef time_t second;

	static const int kMicroRatio=1000000;
	static const int kBufferSize=100;
	static const char* kCookieFormat;

    /**
     * 获取UTC微秒级时间戳
     */
	static micro MicroTime(){
		struct timeval timestamp;

		//return 0 for success, or -1 for failure
		if(gettimeofday(&timestamp, NULL)==-1){
			return -1;
		}

		return static_cast<micro>(timestamp.tv_sec)*kMicroRatio+timestamp.tv_usec;
	}

    /**
     * 获取UTC秒级时间戳
     */
    static second Time(){
    	return time(NULL);
    }

    /**
	* 将tm时间转换为Unix时间戳
	*/
   static Status TmToStamp(struct tm &tm, second& sec);

    /**
     * 将Cookie时间转换为时间戳
     */
    static Status CookieTimeToStamp(string str, second& sec);

    /**
     * 将时间戳转换为Cookie时间
     */
    static Status StampToCookieTime(second sec, string& result){
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

};

} //relax
} //utility

#endif//RELAX_UTILITY_TIME_HELPER_H_
