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
}
