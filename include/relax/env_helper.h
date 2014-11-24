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
    enum OverWrite {
        NO=0,
        YES=1
    };

    /**
     * 获取系统环境变量值
     *
     * 类似于PATH、SHELL等变量
     */
    static Status GetVariable(string key, string& value);

    /**
     * 新设置或覆盖一个变量
     *
     * 注: 仅修改程序获取的缓存值
     */
    static Status SetVariable(string key, string value);

    /**
     * 获取系统全局环境变量值
     */
    static Status GetGlobal(string key, string& value);

    /**
     * 新设置或覆盖一个全局变量
     *
     * 注: 会对本进程的所有环境变量产生影响
     */
    static Status SetGlobal(string key, string value, OverWrite overwrite=YES);
};


} //relax
} //utility

#endif//RELAX_UTILITY_ENV_HELPER_H_
