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
    StringParser p("'Route'NAME_SEP'Controller'NAME_SEP'Base'");
    string out;
    Status s=p.get(out);
    if(s.IsOK()){
    	cout<<"Result for 'Route'NAME_SEP'Controller'NAME_SEP'Base': "<<out<<endl;
    }else{
    	cout<<"Result faild: "<<s.message()<<endl;
    }

}
