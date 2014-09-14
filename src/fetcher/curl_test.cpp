#include <gtest/gtest.h>
#include "curl.h"
#include <boost/timer/timer.hpp>


TEST(curl, fetch_baidu_com)
{
	boost::timer::auto_cpu_timer t;

	using ::huilib::fetcher::Curl;
	Curl* curl=new Curl();

	//内容长度>100
	EXPECT_LT(0, curl->get("www.baidu.com").length());
}

TEST(curl, fetch_taobao_com)
{
	boost::timer::auto_cpu_timer t;

	using ::huilib::fetcher::Curl;
	Curl* curl=new Curl();

	//内容长度>100
	EXPECT_LT(0, curl->get("www.taobao.com").length());
}

TEST(curl, fetch_not_exists)
{
    boost::timer::auto_cpu_timer t;

    using ::huilib::fetcher::Curl;
    Curl* curl=new Curl();

    //内容长度>100
    EXPECT_EQ(0, curl->get("fdddddddddddddddddddddddddddddd.com").length());
}
