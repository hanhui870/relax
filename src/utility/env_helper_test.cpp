#include <gtest/gtest.h>
#include <relax/env_helper.h>

using namespace std;


TEST(env_helper, common_actions)
{
    using ::relax::utility::EnvHelper;

    string value;

    EXPECT_EQ(true, EnvHelper::GetVariable("PATH", value).IsOK());
    cout<<"PATH Variable:"<<value<<endl;

    //需要客户端自己保证value初始为空。bad action.
    value="";
    relax::Status s=EnvHelper::GetVariable("fdafdxxxx_existed", value);
    EXPECT_EQ(false, s.IsOK());
    cout<<"not existed Variable:"<<value<<endl;
    EXPECT_STREQ("", value.c_str());

    EXPECT_EQ(true, EnvHelper::GetVariable("GOROOT", value).IsOK());
    cout<<"GOROOT Variable:"<<value<<endl;

    //内容长度=0
    EnvHelper::GetVariable("SHELL", value);
    EXPECT_STREQ("/bin/bash", value.c_str());

    EnvHelper::SetVariable("SHELL", "/bin/sh");
    EnvHelper::GetVariable("SHELL", value);
    cout<<"SHELL Variable new value:"<<value<<endl;
    EXPECT_STREQ("/bin/sh", value.c_str());

    EnvHelper::GetVariable("TZ", value);
    cout<<"TZ Variable value:"<<value<<endl;

    //全局变量设置
    EnvHelper::SetGlobal("TZ", "Pacific/Auckland");
    string valnew;
    EnvHelper::GetGlobal("TZ", valnew);
    cout<<"TZ Variable new value:"<<valnew<<endl;
    EXPECT_STREQ("Pacific/Auckland", valnew.c_str());
    EnvHelper::SetGlobal("TZ", value);
    EnvHelper::GetGlobal("TZ", valnew);
    cout<<"TZ Variable reseted:"<<valnew<<endl;
}
