#include <gtest/gtest.h>
#include <relax/timer.h>
#include "curl.h"

TEST(curl, fetch_baidu_com)
{
	relax::timer t;

	using ::relax::fetcher::Curl;
	Curl* curl=new Curl();

	//内容长度>0
	EXPECT_LT(0, curl->get("www.baidu.com").length());
}

TEST(curl, fetch_taobao_com)
{
    relax::timer t;

	using ::relax::fetcher::Curl;
	Curl* curl=new Curl();

	//内容长度>0
	EXPECT_LT(0, curl->get("www.taobao.com").length());
}

TEST(curl, fetch_google_com)
{
    relax::timer t;

    using ::relax::fetcher::Curl;
    Curl* curl=new Curl();

    EXPECT_LT(0, curl->get("www.google.com").length());
}

TEST(curl, fetch_not_exists)
{
    relax::timer t;

    using ::relax::fetcher::Curl;
    Curl* curl=new Curl();

    //内容长度>0 比如电信存在域名不存在页面的，会出现返回内容
    EXPECT_EQ(0, curl->get("fdddddddddddddddddddddddddddddd.com").length());
}
