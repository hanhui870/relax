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
	Status parse(string input, string output);
};

} //relax
} //utility

#endif//RELAX_UTILITY_STRING_PARSER_H_
