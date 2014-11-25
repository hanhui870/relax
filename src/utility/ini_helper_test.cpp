#include <gtest/gtest.h>
#include <relax/timer.h>
#include <relax/ini_helper.h>
#include <iostream>
#include <string>

using namespace std;
using relax::utility::IniHelper;


TEST(ini_helper, common_actions)
{
    relax::timer t;

    //测试string的标准长度
    cout<<"std::string size="<<sizeof(string)<<endl;
    EXPECT_EQ(4, sizeof(string));

    IniHelper ini("ini-test/app.ini");


}
