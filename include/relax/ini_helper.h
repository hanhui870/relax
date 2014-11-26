/**
 * Relax library
 *
 * ini配置文件解析库
 * #include <relax/ini_helper.h>
 *
 * @author 祝景法
 * @email zhujingfa@gmail.com
 *
 * @since 2014/09/17
 */
#ifndef RELAX_UTILITY_INI_HELPER_H_
#define RELAX_UTILITY_INI_HELPER_H_

#include <map>
#include <string>
#include <relax/relax.h>

namespace relax {
namespace utility {

using std::map;
using std::string;

class IniEnv;
class NodeValue;

class IniHelper {
public:
    ~IniHelper() {
    }

    /**
     * 获取一个ini实例
     */
     static Status Factory(string filename, IniHelper** instance);

    /**
     * 获取一个环境的值
     */
     Status Get(string env, IniEnv& value);

private:
     IniHelper(string& filename);

    /**
     * environment => IniEnv
     *
     * 不在命名空间下的是global环境，全局可用。其他通过继承关系解析。
     */
    map<string, IniEnv> container_;
};

class IniEnv {
public:
    IniEnv(IniEnv* parent):parent_(parent) {

    }

    ~IniEnv() {

    }

    /**
     * 获取一个键的值
     */
     Status Get(string key, NodeValue& value);

    /**
     * 设置一个键的值
     */
     Status Set(string key, NodeValue value);

private:
     IniEnv* parent_;

     /**
      * key => value
      */
     map<string, NodeValue*> container_;
};

} //relax
} //utility

#endif//RELAX_UTILITY_INI_HELPER_H_
