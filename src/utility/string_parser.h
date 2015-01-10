#include <string>
#include <relax/relax.h>

#ifndef RELAX_UTILITY_STRING_PARSER_H_
#define RELAX_UTILITY_STRING_PARSER_H_

namespace relax {
namespace utility {

using std::string;

/**
 * String字符串解析器
 *
 * 	宏观变量解析
 * 	字符串处理
 */
class StringParser{
public:
	StringParser(string str) : original(str){

	}

	Status get(string& output);

private:
	//非字符内解析
	Status ParseConst(string& key, string& value);

	string original;

	//所有分隔符
	const static string kStringDelimiter;
	//转义
	const static char kSlashes;
	//支持的转义序列
	const static string kSlashesList;
	//对应转义序列
	const static string kSlashedList;
};

} //relax
} //utility

#endif//RELAX_UTILITY_STRING_PARSER_H_
