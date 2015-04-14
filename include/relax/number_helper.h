/**
 * Relax library
 *
 * @author 祝景法
 * @email zhujingfa@gmail.com
 *
 * @since 2014/09/17
 */
#ifndef RELAX_UTILITY_NUMBER_HELPER_H_
#define RELAX_UTILITY_NUMBER_HELPER_H_

#include <string>
#include <relax/relax.h>

namespace relax {

using std::string;

class NumberHelper{
public:
    /**
     * 整型转换为字符串
     */
	static Status IntegerToString(int num, string& value);
	static Status IntegerToString(long num, string& value);
	static Status IntegerToString(long long num, string& value);
	static Status IntegerToString(short num, string& value);

    /**
     * 浮点数转换为字符串
     */
    static Status FloatToString(float num, string& value);
    static Status FloatToString(double num, string& value);
    static Status FloatToString(long double num, string& value);

private:
};

} //relax

#endif//RELAX_UTILITY_NUMBER_HELPER_H_
