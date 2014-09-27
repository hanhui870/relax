/**
 * Relax library
 *
 * 公共头文件
 * #include <relax/relax.h>
 *
 * @author 祝景法
 * @email zhujingfa@gmail.com
 *
 * @since 2014/09/17
 */
#ifndef RELAX_RELAX_H_
#define RELAX_RELAX_H_

#include <string>

namespace relax {

using std::string;

//输出变量
#define RELAX_OUT;
//输入变量，默认
#define RELAX_IN;

//relax 公共类
//接口调用状态 Status
class Status;

class Status{
public:
    Status() : status_(false) {};

    Status(bool status, string message) : status_(status), message_(message) {};

    /**
     * 设置状态
     */
    Status* set_status(bool status){
        status_=status;
        return this;
    }

    /**
     * 设置状态的消息内容
     */
    Status* set_message(string message){
        message_=message;
        return this;
    }

    ~Status();

    bool OK(){
        return status_==true;
    }

    bool Fail(){
        return status_==false;
    }

    string message(){
        return message_;
    }

private:
    bool status_;
    string message_;
};

} //relax

#endif//RELAX_RELAX_H_

