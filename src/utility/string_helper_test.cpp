#include <gtest/gtest.h>
#include <relax/timer.h>
#include <relax/string_helper.h>

using namespace std;


TEST(string_helper, common_actions)
{
    relax::timer t;

    using ::relax::utility::StringHelper;
    vector<string> result=StringHelper::explode("Token=1840m59u5epb5j5znsrwfm6amcrdt4gkdnu52o4f; expires=Fri, 20-Sep-2019 14:06:12 GMT; path=/; HttpOnly; secure  ;;", ";");

    for(auto &elem : result)
        cout<<elem<<"\ntrim:"<<StringHelper::trim(elem)<<endl;

    //内容长度=0
    EXPECT_EQ(7, result.size());
    EXPECT_STREQ("Token=1840m59u5epb5j5znsrwfm6amcrdt4gkdnu52o4f", result[0].c_str());
    EXPECT_STREQ("HttpOnly", StringHelper::trim(result[3]).c_str());

    result=StringHelper::explode("", ";");
    cout<<"StringHelper::explode(\"\", \";\") length="<< result.size()<<endl;
    EXPECT_EQ(1, result.size());
}
