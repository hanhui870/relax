/**
 * Relax library
 *
 * @author 祝景法
 * @email zhujingfa@gmail.com
 *
 * @since 2014/09/17
 */
#ifndef RELAX_UTILITY_STRING_HELPER_H_
#define RELAX_UTILITY_STRING_HELPER_H_

#include <string>
#include <sstream>
#include <vector>

namespace relax {
namespace utility {

using std::string;
using std::vector;
using std::stringstream;

class StringHelper{
public:
    /**
     * 按字符串拆字符
     */
    static vector<string> Explode(string str, string delimiter);

    /**
     * 移除两边的空格
     */
    static string Trim(string str);

    /**
    * 将内容转换为string类型
    */
   template <typename T>
   static string ConvertToString(T value);

   /**
    * 转换字符串大小写 分覆盖、返回新两个版本
    */
   void static ToUpper(string str, string& value);
   static void ToUpper(string& str);
   static void ToLower(string str, string& value);
   static void ToLower(string& str);
};

template <typename T>
string StringHelper::ConvertToString(T value){
    stringstream sstream;
    sstream<<value;

    string tmp;
    sstream>>tmp;
    sstream.clear();

    return tmp;
}

} //relax
} //utility

#endif//RELAX_UTILITY_STRING_HELPER_H_
