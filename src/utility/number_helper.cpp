/**
 * Relax library
 *
 * @author 祝景法
 * @email zhujingfa@gmail.com
 *
 * @since 2014/09/17
 */
#include <cstdio>
#include <relax/number_helper.h>

namespace relax {
namespace utility {
/**
 * 整型转换为字符串
 */
Status NumberHelper::IntegerToString(short num, string& value){
    return IntegerToString(static_cast<long long>(num), value);
}
Status NumberHelper::IntegerToString(int num, string& value){
    return IntegerToString(static_cast<long long>(num), value);
}
Status NumberHelper::IntegerToString(long num, string& value){
    return IntegerToString(static_cast<long long>(num), value);
}
Status NumberHelper::IntegerToString(long long num, string& value){
    char buffer[128];
    value="";

    int len=std::sprintf(buffer, "%d", num);
    if(len>0){
        value.assign(buffer);
        return Status::GetOK();
    }

    return Status::GetFail();
}

/**
 * 浮点数转换为字符串
 */
Status NumberHelper::FloatToString(float num, string& value){
    return FloatToString(static_cast<double>(num), value);
}
Status NumberHelper::FloatToString(double num, string& value){
    char buffer[128];
    value="";

    int len=std::sprintf(buffer, "%f", num);
    if(len>0){
        value.assign(buffer);
        return Status::GetOK();
    }

    return Status::GetFail();
}
Status NumberHelper::FloatToString(long double num, string& value){
    //long double 128长度是不够的
    return FloatToString(static_cast<double>(num), value);
}

} //relax
} //utility

