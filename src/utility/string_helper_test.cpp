#include <gtest/gtest.h>
#include <relax/timer.h>
#include <relax/string_helper.h>

using namespace std;


TEST(string_helper, common_actions)
{
    relax::timer t;

    using ::relax::utility::StringHelper;
    vector<string> result=StringHelper::Explode("Token=1840m59u5epb5j5znsrwfm6amcrdt4gkdnu52o4f; expires=Fri, 20-Sep-2019 14:06:12 GMT; path=/; HttpOnly; secure  ;;", ";");

    for(auto &elem : result)
        cout<<elem<<"\ntrim:"<<StringHelper::Trim(elem)<<endl;

    //内容长度=0
    EXPECT_EQ(7, result.size());
    EXPECT_STREQ("Token=1840m59u5epb5j5znsrwfm6amcrdt4gkdnu52o4f", result[0].c_str());
    EXPECT_STREQ("HttpOnly", StringHelper::Trim(result[3]).c_str());

    result=StringHelper::Explode("", ";");
    cout<<"StringHelper::Explode(\"\", \";\") length="<< result.size()<<endl;
    EXPECT_EQ(1, result.size());

    long double dnum=15434343.43434343;
    string value = StringHelper::ConvertToString(dnum);
    cout << "Long double original: " << dnum << endl;
    cout << "Long double to string: 15434343.43434343 => " << value << endl;
    //stream转换法会有科学计数法
    EXPECT_STREQ("1.54343e+07", value.c_str());

    int inum=0x57;
    value = StringHelper::ConvertToString(inum);
    cout << "Long double original: " << inum << endl;
    cout << "Long double to string: 0x57 => " << inum << endl;
    //stream转换法会有科学计数法
    EXPECT_STREQ("87", value.c_str());

    string s1("helLo World.");
    StringHelper::ToUpper(s1);
    EXPECT_STREQ("HELLO WORLD.", s1.c_str());
    string s;
    StringHelper::ToUpper("helLo World.", s);
    cout<<"helLo World."<<" upcase:"<<s<<endl;
    EXPECT_STREQ("HELLO WORLD.", s.c_str());

    string s2("helLo World.");
    StringHelper::ToLower(s2);
    EXPECT_STREQ("hello world.", s2.c_str());
    string s3;
    StringHelper::ToLower("helLo World.", s3);
    cout<<"helLo World."<<" lowercase:"<<s3<<endl;
    EXPECT_STREQ("hello world.", s3.c_str());
}
