/**
 * Relax library
 *
 * @author 祝景法
 * @email zhujingfa@gmail.com
 *
 * @since 2014/09/17
 */
#include <relax/relax.h>

namespace relax {

//Status 转移复制构造操作符
Status::Status(Status&& rvalue) : code_(rvalue.code_), message_(std::move(rvalue.message_)){}
//Status 普通复制构造操作符
Status::Status(Status& rvalue) : code_(rvalue.code_), message_(rvalue.message_){}

//Status 转移赋值操作符
Status& Status::operator=(Status&& rvalue){
    if(this != &rvalue){
        code_=rvalue.code_;
        message_=std::move(rvalue.message_);
    }

    return *this;
}
//Status 普通赋值操作符
Status& Status::operator=(Status& rvalue){
    if(this != &rvalue){
        code_=rvalue.code_;
        message_=rvalue.message_;
    }

    return *this;
}

} //relax
