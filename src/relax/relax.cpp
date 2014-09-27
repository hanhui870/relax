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

Status::Status(Status&& rvalue) : code_(rvalue.code_), message_(std::move(rvalue.message_)){}
Status::Status(Status& rvalue) : code_(rvalue.code_), message_(rvalue.message_){}

Status& Status::operator=(Status&& rvalue){
    if(this != &rvalue){
        code_=rvalue.code_;
        message_=std::move(rvalue.message_);
    }

    return *this;
}

Status& Status::operator=(Status& rvalue){
    if(this != &rvalue){
        code_=rvalue.code_;
        message_=rvalue.message_;
    }

    return *this;
}

} //relax
