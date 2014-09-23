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
#include <sys/time.h>

namespace relax {
namespace utility {

class TimeHelper{
public:
	typedef long long micro;
	typedef time_t second;

	static const int kMicroRatio=1000000;

    /**
     * 按字符串拆字符
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
     * 移除两边的空格
     */
    static second Time(){
    	return time(NULL);
    }
};

} //relax
} //utility

#endif//RELAX_UTILITY_TIME_HELPER_H_
