#include <gtest/gtest.h>
#include <relax/env_helper.h>

using namespace std;


TEST(env_helper, common_actions)
{
    using ::relax::utility::EnvHelper;

    cout<<"PATH Variable:"<<EnvHelper::GetVariable("PATH")<<endl;

    cout<<"not existed Variable:"<<EnvHelper::GetVariable("fdafdxxxx_existed")<<endl;
    cout<<"GOROOT Variable:"<<EnvHelper::GetVariable("GOROOT")<<endl;

    //内容长度=0
    EXPECT_STREQ("/bin/bash", EnvHelper::GetVariable("SHELL").c_str());
    EXPECT_EQ(0, EnvHelper::GetVariable("fdafdxxxx_existed").size());
}
