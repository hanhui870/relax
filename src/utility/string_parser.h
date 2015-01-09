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
	const static string kStringDelimiter;

public:
	StringParser(string str) : original(str){

	}

	Status get(string& output);

private:
	string original;
};

} //relax
} //utility

#endif//RELAX_UTILITY_STRING_PARSER_H_
