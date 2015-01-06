#include "string_parser.h"
#include <relax/env_helper.h>
#include <relax/string_helper.h>

namespace relax {
namespace utility {

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
		if(iter2 != iter1){
			if('\0' == separator){
				if( kStringDelimiter[sepnow]!= separator){
					token=string(iter1, iter2);
					Debug::out(token);
					return Status::GetOK();
				}else{
					//字符串结束
				}
			}else{// !=\0


			}
		}else{
			separator=*iter2;
		}
		iter1=iter2;
	}

	return Status::GetOK();
}

} //relax
} //utility
