#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <relax/relax.h>

using namespace std;


TEST(relax_common, status_test)
{
    using relax::Status;

    //测试标准长度
    cout<<"std::string size="<<sizeof(string)<<endl;
    EXPECT_EQ(4, sizeof(string));
    cout<<"std::bool size="<<sizeof(bool)<<endl;
    EXPECT_EQ(1, sizeof(bool));

    //有对齐要求，果然是8
    cout<<"sizeof relax::Status="<<sizeof(Status)<<endl;
    EXPECT_EQ(8, sizeof(Status));

    Status s=Status::GetOK();
    EXPECT_EQ(true, s.IsOK());
    EXPECT_EQ(false, s.IsFail());
    s=Status::GetFail();
    EXPECT_EQ(true, s.IsFail());
    EXPECT_EQ(false, s.IsOK());

    s.set_code(1);
    EXPECT_EQ(false, s.IsFail());
    s.set_message("你好");
    cout<<"Status' message:"<<s.message()<<endl;

    Status ss(-1, "失败了");
    EXPECT_EQ(true, ss.IsFail());
    EXPECT_STREQ("失败了", ss.message().c_str());

}
