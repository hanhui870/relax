#include <gtest/gtest.h>
#include <relax/relax.h>
#include <relax/timer.h>
#include "string_parser.h"

using namespace std;

TEST(string_parser, common_actions)
{
    relax::timer t;

    using ::relax::utility::StringParser;
    using ::relax::Status;
    //const char* a="'Route'NAME_SEP'Controller'NAME_SEP'Base'";
    //使用 StringParser p("'Route'NAME_SEP'Controller'NAME_SEP'Base'"); original内容会变，因为C++字符串中引号需要完全转义
    //StringParser p(a);
    {
    	const char* tmp= "\'Route\'cdev\'Controller\'tech\'Base\'";
    	StringParser p(tmp);//可用，已转义
		string out;
		Status s=p.get(out);
		if(s.IsOK()){
			cout<<"Result for "<<tmp<<": "<<out<<endl;
		}else{
			cout<<"Result faild: "<<s.message()<<endl;
		}
    }

    {
      	StringParser p("2");
  		string out;
  		Status s=p.get(out);
  		EXPECT_STREQ("2", out.c_str());
     }

    {
		StringParser p("2.900006");
		string out;
		Status s=p.get(out);
		EXPECT_STREQ("2.900006", out.c_str());
	 }

    {
   		StringParser p("\tn\ns\'t");//可用，已转义
   		string out;
   		Status s=p.get(out);
   		if(s.IsOK()){
   			cout<<"Result for \\tn\\ns\\'t:"<<out<<out.size()<<endl;
		}else{
			cout<<"Result faild: "<<s.message()<<endl;
		}
   	 }

    {
    	//引号要 \\\'这样才能显示出来
		StringParser p("\"\\\\\tn\ns\\\'t\\\"");//可用，已转义
		string out;
		Status s=p.get(out);
		if(s.IsOK()){
			cout<<"Result :"<<out<<" size: "<<out.size()<<endl;
			EXPECT_EQ(8, out.size());
		}else{
			cout<<"Result faild: "<<s.message()<<endl;
		}
	 }

}
