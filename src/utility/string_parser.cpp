#include "string_parser.h"
#include <relax/env_helper.h>
#include <relax/string_helper.h>
#include <relax/number_helper.h>
#include <Poco/Ascii.h>
#include <Poco/NumberParser.h>

namespace relax {

using Poco::Ascii;
using Poco::NumberParser;

//必须在类体中声明，类体外定义，并且不能在头文件，不然可能多重定义
//支付分隔符，引号；但是反斜线\只是转义用
const string StringParser::kStringDelimiter("'\"\\");
const char StringParser::kSlashes='\\';
const string StringParser::kSlashesList("ntvbrfa\\?'\"");
const string StringParser::kSlashedList("\n\t\v\b\r\f\a\\\?\'\"");

/**
 * 解析字符串
 *
 * 'Route'NAME_SEP'Controller'NAME_SEP'Base'
 * NAME_SEP'Route'NAME_SEP'Controller'NAME_SEP'Base'
 */
Status StringParser::get(string& output){
	//实际处理的是trim过的str
	string str=StringHelper::Trim(original);

	string::const_iterator start=str.begin();
	string::const_iterator end = str.end();
	string::const_iterator iter1;//分隔符起始
	string::const_iterator iter2;//分隔符终止
	string::size_type sepnow;
	string::size_type slashnow;//当前转义符位置
	char current;
	char sepintial='\0';

	string result;
	string token;
	char separator=sepintial;
	iter1=start;
	while(iter1 != end){
		iter2=iter1;
		while((sepnow=kStringDelimiter.find(*iter2)) == string::npos && iter2!=end) ++iter2;

		if(sepnow != string::npos){
			if(sepintial == separator){
				//处理常量，不能用0，也是索引符号
				if(iter1 != iter2){
					string tmp=StringHelper::Trim(string(iter1, iter2));
					string value;
					Status s=ParseConst(tmp, value);
					if(s.IsFail()){
						return s;
					}
					output.append(value);
				}

				if(kStringDelimiter[sepnow] == kSlashes){
					return Status::GetFail().set_message(string("Invalid string delimiter: ")+kStringDelimiter[sepnow]+" in: "+original);
				}else{
					//设置当前分隔符
					separator=kStringDelimiter[sepnow];
					iter2++;
				}

			}else{//字符串语义中
				//当前分隔符一致
				if( kStringDelimiter[sepnow] == separator){
					output.append(string(iter1, iter2));

					iter2++;
					separator=sepintial;
				//转义符
				}else if(kStringDelimiter[sepnow] == kSlashes){
					if(iter2 != end && iter2+1 != end && (slashnow = kSlashesList.find(*(iter2+1))) != string::npos){
						output.append(string(iter1, iter2)+kSlashedList[slashnow]);
						iter2++;
						iter2++;
					}else{
						return Status::GetFail().set_message(string("Invalid slash escape: ")+original);
					}
				}else{//单引号、双引号等于现有分隔符不同的符号
					output.append(string(iter1, iter2));
					iter2++;
				}
			}
		}else{
			if(sepintial != separator){
				return Status::GetFail().set_message(string("Invalid ini value: ")+original);
			}

			string tmp=StringHelper::Trim(string(iter1, iter2));
			string value;
			Status s=ParseConst(tmp, value);
			if(s.IsFail()){
				return s;
			}
			output.append(value);
			//iter2++;//这里不用加1，前面已经加到end了。
		}

		iter1=iter2;
	}

	return Status::GetOK();
}

/**
 * 常量解析
 *
 * 目前支持: 整数、小数、环境变量解析
 */
Status StringParser::ParseConst(string& key, string& value){
	string::const_iterator start=key.begin();
	if(Ascii::isDigit(*start)){
		if(key.find('.') == string::npos){
			int tmpInt;
			if(NumberParser::tryParse(key, tmpInt)){
				Status s=NumberHelper::IntegerToString(tmpInt, value);
				if(s.IsFail()){
					return Status::GetFail().set_message(string("Failed to converse int to string: ")+key);
				}else{
					return s;
				}
			}else{
				return Status::GetFail().set_message(string("Invalid integer: ")+key);
			}
		}else{// 小数解析
			double tmp;
			if(NumberParser::tryParseFloat(key, tmp)){
				Status s=NumberHelper::FloatToString(tmp, value);
				if(s.IsFail()){
					return Status::GetFail().set_message(string("Failed to converse float to string: ")+key);
				}else{
					return s;
				}
			}else{
				return Status::GetFail().set_message(string("Invalid integer: ")+key);
			}
		}
	}

	//解析环境变量
	Status s=EnvHelper::GetVariable(key, value);
	if(s.IsFail()){
		return Status::GetFail().set_message(string("Failed to fetch env variable: ")+key);
	}

	return Status::GetOK();
}

} //relax
