#include <gtest/gtest.h>
#include <relax/time_helper.h>
#include <stdlib.h>

using namespace std;


TEST(time_helper, common_actions)
{
    using ::relax::utility::TimeHelper;

    cout<<"MicroTime:"<<TimeHelper::MicroTime()<<endl;
    cout<<"Second:"<<TimeHelper::Time()<<endl;

    EXPECT_EQ(8, sizeof(TimeHelper::micro));

    //内容长度=0
    EXPECT_LT(static_cast<TimeHelper::micro>(time(NULL))*TimeHelper::kMicroRatio, TimeHelper::MicroTime());

    string value=getenv("TZ");
    cout<<"Init TZ is: "<<value<<endl;

    TimeHelper::second sec;
    relax::Status s=TimeHelper::CookieTimeToStamp("Fri, 20-Sep-2019 03:16:02 GMT", sec);
    if(s.IsOK()){
        cout<<"Second:"<<sec<<endl;
    }else{
        cout<<"Find error:"<<s.message()<<endl;
    }
    //这个才是正确的 JS: new Date(1568949362000)=Fri Sep 20 2019 11:16:02 GMT+0800 (中国标准时间)
    EXPECT_EQ(1568949362, sec);

    value=getenv("TZ");
    cout<<"After CookieTimeToStamp, TZ is: "<<value<<endl;

    string result;
    s=TimeHelper::StampToCookieTime(sec, result);
    if(s.IsOK()){
        cout<<"Result string:"<<result<<endl;
    }else{
        cout<<"Find error:"<<s.message()<<endl;
    }
    EXPECT_STREQ("Fri, 20-Sep-2019 03:16:02 GMT", result.c_str());

    value=getenv("TZ");
    cout<<"After StampToCookieTime, TZ is: "<<value<<endl;

}
