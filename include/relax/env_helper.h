/**
 * Relax library
 *
 * @author 祝景法
 * @email zhujingfa@gmail.com
 *
 * @since 2014/09/17
 */
#ifndef RELAX_UTILITY_ENV_HELPER_H_
#define RELAX_UTILITY_ENV_HELPER_H_

#include <string>

namespace relax {
namespace utility {

using std::string;

class EnvHelper{
public:
    /**
     * 获取系统环境变量值
     *
     * 类似于PATH、SHELL等变量
     */
    static string GetVariable(string key);


};


} //relax
} //utility

#endif//RELAX_UTILITY_ENV_HELPER_H_
