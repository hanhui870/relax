#include "string_parser.h"
#include <relax/env_helper.h>
#include <relax/string_helper.h>

namespace relax {
namespace utility {

//必须在类体中声明，类体外定义，并且不能在头文件，不然可能多重定义
const string StringParser::kStringDelimiter="'\"\\";

/**
 * 解析字符串
 *
 * 'Route'NAME_SEP'Controller'NAME_SEP'Base'
 */
Status StringParser::get(string& output){
	string str=StringHelper::Trim(original);

	string::const_iterator start=str.begin();
	string::const_iterator end = str.end();
	string::const_iterator iter1;//分隔符起始
	string::const_iterator iter2;//分隔符终止
	string::size_type sepnow;
	char current;
	char separator='\0';
	string result;
	string token;

	iter1=start;
	while(iter1 != end){
		iter2=iter1;
		while((sepnow=kStringDelimiter.find(*iter2)) == string::npos && iter2!=end) ++iter2;

		return Status::GetOK();
		if(sepnow != string::npos){
			if('\0' == separator){
				//设置当前分隔符
				separator=kStringDelimiter[sepnow];

			}else{
				//当前分隔符一致
				if( kStringDelimiter[sepnow]!= separator){
					token=string(iter1, iter2);
					Debug::out(token);
					return Status::GetOK();
				}
			}
		}else{
			if('\0' != separator){
				return Status::GetFail().set_message(string("Invalid ini value: ")+original);
			}
		}

		iter1=iter2;
	}

	return Status::GetOK();
}

} //relax
} //utility
