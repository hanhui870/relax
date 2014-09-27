#include <gtest/gtest.h>
#include <relax/env_helper.h>

using namespace std;


TEST(env_helper, common_actions)
{
    using ::relax::utility::EnvHelper;

    string value;

    EXPECT_EQ(true, EnvHelper::GetVariable("PATH", value).IsOK());
    cout<<"PATH Variable:"<<value<<endl;

    EXPECT_EQ(false, EnvHelper::GetVariable("fdafdxxxx_existed", value).IsOK());
    cout<<"not existed Variable:"<<value<<endl;

    EXPECT_EQ(true, EnvHelper::GetVariable("GOROOT", value).IsOK());
    cout<<"GOROOT Variable:"<<value<<endl;

    //内容长度=0
    EnvHelper::GetVariable("SHELL", value);
    EXPECT_STREQ("/bin/bash", value.c_str());
}
