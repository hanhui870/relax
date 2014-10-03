#include <gtest/gtest.h>
#include <relax/time_helper.h>

using namespace std;


TEST(time_helper, common_actions)
{
    using ::relax::utility::TimeHelper;

    cout<<"MicroTime:"<<TimeHelper::MicroTime()<<endl;
    cout<<"Second:"<<TimeHelper::Time()<<endl;

    EXPECT_EQ(8, sizeof(TimeHelper::micro));

    //内容长度=0
    EXPECT_LT(static_cast<TimeHelper::micro>(time(NULL))*TimeHelper::kMicroRatio, TimeHelper::MicroTime());

    TimeHelper::second sec;
    relax::Status s=TimeHelper::CookieTimeToStamp("Fri, 20-Sep-2019 03:16:02 GMT", sec);
    if(s.IsOK()){
        cout<<"Second:"<<sec<<endl;
    }else{
        cout<<"Find error:"<<s.message()<<endl;
    }
    EXPECT_EQ(1568920562, sec);

    string result;
    s=TimeHelper::StampToCookieTime(sec, result);
    if(s.IsOK()){
        cout<<"Result string:"<<result<<endl;
    }else{
        cout<<"Find error:"<<s.message()<<endl;
    }
    EXPECT_STREQ("Fri, 20-Sep-2019 03:16:02 CST", result.c_str());

}
