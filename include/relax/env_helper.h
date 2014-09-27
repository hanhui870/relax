/**
 * Relax library
 *
 * 环境变量库
 * #include <relax/env_helper.h>
 *
 * @author 祝景法
 * @email zhujingfa@gmail.com
 *
 * @since 2014/09/17
 */
#ifndef RELAX_UTILITY_ENV_HELPER_H_
#define RELAX_UTILITY_ENV_HELPER_H_

#include <string>
#include <relax/relax.h>

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
    static Status GetVariable(string key, string& value);

    /**
     * 新设置或覆盖一个变量
     */
    static Status SetVariable(string key, string value);
};


} //relax
} //utility

#endif//RELAX_UTILITY_ENV_HELPER_H_