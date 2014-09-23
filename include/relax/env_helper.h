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
