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

#include <string>
#include <relax/relax.h>

namespace relax {
namespace utility {

using std::string;

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
	static micro MicroTime();

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
    static Status StampToCookieTime(second sec, string& result);

};

} //relax
} //utility

#endif//RELAX_UTILITY_TIME_HELPER_H_
