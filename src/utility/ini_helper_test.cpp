#include <gtest/gtest.h>
#include <relax/timer.h>
#include <relax/ini_helper.h>
#include <iostream>
#include <string>
#include <memory>

using namespace std;
using relax::utility::IniHelper;
using relax::utility::IniEnv;
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
    EXPECT_EQ(true, s.IsOK());
    if(s.IsFail()){
        cout<<"Failed factory IniHelper instance: "<<s.message()<<endl;
        //构建失败
        return ;
    }else{
        cout<<"Factory IniHelper instance address: "<<ini<<endl;
    }
    std::unique_ptr<IniHelper> iniptr(ini);

    IniEnv* env;
    s=ini->Get("production", &env);
    if(s.IsFail()){
		cout<<"Failed fetch env: "<<s.message()<<endl;
	}else{
		string value;
		s=env->Get("webrun.view.cachePath", value);
		cout<<"Fetch webrun.view.cachePath: "<<value<<endl;
		EXPECT_STREQ("D:\\go\\Data\\View", value.c_str());

		int valueInt;
		s=env->Get("webrun.view.life", valueInt);
		cout<<"Fetch webrun.view.life: "<<valueInt<<endl;
		EXPECT_EQ(86400, valueInt);

		double valueFloat;
		s=env->Get("secure.csrf.float", valueFloat);
		cout<<"Fetch secure.csrf.float: "<<valueFloat<<endl;
		EXPECT_EQ(3.14159, valueFloat);
	}




}
