#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <relax/timer.h>
#include <relax/number_helper.h>

using namespace std;

TEST(number_helper, common_actions) {
    relax::timer t;
    using relax::NumberHelper;

    //测试string的标准长度
    string value;

    relax::Status s;
    s = NumberHelper::IntegerToString(0, value);
    EXPECT_EQ(true, s.IsOK());
    cout << "Inter to string: 0 => " << value << endl;
    EXPECT_STREQ("0", value.c_str());

    s = NumberHelper::IntegerToString(-1342432, value);
    EXPECT_EQ(true, s.IsOK());
    cout << "Inter to string: -1342432 => " << value << endl;
    EXPECT_STREQ("-1342432", value.c_str());

    s = NumberHelper::IntegerToString(-027, value);
    EXPECT_EQ(true, s.IsOK());
    cout << "Inter to string: -027 => " << value << endl;
    EXPECT_STREQ("-23", value.c_str());

    s = NumberHelper::IntegerToString(-0x27, value);
    EXPECT_EQ(true, s.IsOK());
    cout << "Inter to string: -0x27 => " << value << endl;
    EXPECT_STREQ("-39", value.c_str());

    double num=-15.43434343;
    s = NumberHelper::FloatToString(num, value);
    EXPECT_EQ(true, s.IsOK());
    cout << "Double original: " << num << endl;
    cout << "Float to string: -15.43434343 => " << value << endl;
    EXPECT_STREQ("-15.434343", value.c_str());

    long double dnum=15434343.43434343;
    s = NumberHelper::FloatToString(dnum, value);
    EXPECT_EQ(true, s.IsOK());
    cout << "Long double original: " << dnum << endl;
    cout << "Long double to string: 15434343.43434343 => " << value << endl;
    EXPECT_STREQ("15434343.434343", value.c_str());

}
