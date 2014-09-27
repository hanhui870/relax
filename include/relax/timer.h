/**
 * Relax library
 *
 * boost 运行时间检测库
 *
 * #include <relax/timer.h>
 * relax::timer t;
 *
 * link dependency:
 * -lboost_timer.dll -lboost_system.dll
 *
 * @author 祝景法
 * @email zhujingfa@gmail.com
 *
 * @since 2014/09/17
 */
#include <boost/timer/timer.hpp>

#ifndef RELAX_TIMER_H_
#define RELAX_TIMER_H_

namespace relax {

using boost::timer::auto_cpu_timer;

class timer{
public:
    timer() : impl_(auto_cpu_timer()) {

    }
private:
    auto_cpu_timer impl_;
};

} //relax

#endif
