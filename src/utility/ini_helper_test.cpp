#include <gtest/gtest.h>
#include <relax/timer.h>
#include <relax/ini_helper.h>
#include <iostream>
#include <string>
#include <memory>

using namespace std;
using relax::utility::IniHelper;
using relax::Status;


TEST(ini_helper, common_actions)
{
    relax::timer t;

    //测试string的标准长度 64位是8 32位是4
    cout<<"std::string size="<<sizeof(string)<<endl;
    EXPECT_EQ(8, sizeof(string));

    IniHelper* ini=NULL;
    Status s=IniHelper::Factory("ini-test/app-not-exist.ini", &ini);
    if(s.IsFail()){
        cout<<"Failed factory IniHelper instance: "<<s.message()<<endl;
    }

    s=IniHelper::Factory("ini-test/app.ini", &ini);
    if(s.IsFail()){
        cout<<"Failed factory IniHelper instance: "<<s.message()<<endl;
    }else{
        cout<<"Factory IniHelper instance address: "<<ini<<endl;
    }
    std::unique_ptr<IniHelper> iniptr(ini);







}
