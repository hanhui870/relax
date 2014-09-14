#include <gtest/gtest.h>
#include "curl.h"
#include <boost/timer/timer.hpp>


TEST(curl, fetch_baidu_com)
{
	boost::timer::auto_cpu_timer t;

	using ::huilib::fetcher::Curl;
	Curl* curl=new Curl();
    std::cout<<"get contents:"<<curl->get("www.baidu.com")<<std::endl;

}

TEST(curl, fetch_taobao_com)
{
	boost::timer::auto_cpu_timer t;

	using ::huilib::fetcher::Curl;
	Curl* curl=new Curl();
    std::cout<<"get contents:"<<curl->get("www.taobao.com")<<std::endl;

}
