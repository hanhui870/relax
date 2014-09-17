#include <boost/timer/timer.hpp>

#ifndef HUILIB_BENCHMARK_TIMER_H_
#define HUILIB_BENCHMARK_TIMER_H_

namespace huilib {
namespace fetcher {

using boost::timer::auto_cpu_timer;

class timer{
    timer() : impl_(auto_cpu_timer()) {

    }
private:
    auto_cpu_timer impl_;
};

} //huilib
} //fetcher

#endif
