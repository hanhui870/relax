#include <gtest/gtest.h>
#include <relax/timer.h>
#include <relax/curl.h>

using namespace std;
using relax::Status;
using ::relax::fetcher::Curl;

TEST(curl, fetch_baidu_com)
{
    relax::timer t;

    using ::relax::fetcher::Curl;
    Curl* curl=new Curl();

    //内容长度>0
    std::string r;

    Status s=curl->get("www.baidu.com", r);
    EXPECT_EQ(true, s.IsOK());
    if(s.IsFail()) cout<<"Status error message: "<<s.message()<<endl;
    EXPECT_LT(0, r.length());
}

TEST(curl, fetch_taobao_com)
{
    relax::timer t;

    Curl* curl=new Curl();

    //内容长度>0
    std::string r;

    Status s=curl->get("www.taobao.com", r);
    EXPECT_EQ(true, s.IsOK());
    if(s.IsFail()) cout<<"Status error message: "<<s.message()<<endl;
    EXPECT_LT(0, r.length());
}

TEST(curl, fetch_https_alipay_com)
{
    relax::timer t;

    Curl* curl=new Curl();
    std::string r;
    Status s=curl->get("https://www.alipay.com", r);
    EXPECT_EQ(true, s.IsOK());
    if(s.IsFail()) cout<<"Status error message: "<<s.message()<<endl;
    EXPECT_LT(0, r.length());
}

TEST(curl, fetch_not_exists)
{
    relax::timer t;

    using ::relax::fetcher::Curl;
    Curl* curl=new Curl();

    //内容长度>0 比如电信存在域名不存在页面的，会出现返回内容
    std::string r;
    Status s=curl->get("www.fdddddddddddddddddddddddddddddd.com", r);

    EXPECT_EQ(false, s.IsOK());
    if(s.IsFail()) cout<<"Status error message: "<<s.message()<<endl;
    EXPECT_EQ(0, r.length());
}
