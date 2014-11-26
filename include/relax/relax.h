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
#include <iostream>

namespace relax {

using std::string;

//relax 公共类
//接口调用状态 Status
class Status{
public:
    static Status GetOK(){
        return Status(STATUS_OK);
    }

    static Status GetFail(){
        return Status(STATUS_FAIL);
    }

    //默认正常状态
    Status() : code_(STATUS_OK) {};
    Status(int code_) : code_(code_) {};
    Status(int code_, string message) : code_(code_), message_(message) {};
    ~Status(){};

    Status(Status&& rvalue);
    Status(Status& rvalue);
    Status& operator=(Status&& rvalue);
    Status& operator=(Status& rvalue);

    /**
     * 设置状态
     */
    Status& set_code(int code){
        code_=code;

        return *this;
    }

    /**
     * 设置状态的消息内容
     */
    Status& set_message(string message){
        message_=message;
        return *this;
    }

    bool IsOK(){
        return code_>=0;
    }

    bool IsFail(){
        return code_<0;
    }

    string message(){
        return message_;
    }

    int code(){
        return code_;
    }

private:
    enum Code{
        STATUS_OK=0,
        STATUS_FAIL=-1,
    };

    /**
     * 状态code
     *
     * >=0成功
     * <0失败
     */
    int code_;

    /**
     * 状态消息内容
     */
    string message_;
};

/**
 * 调试类
 */
class Debug{
public:
    template<class T>
    static void out(T);

};

/**
 * 模板类的定义需要放在头文件
 */
template<class T>
void Debug::out(T var){
    std::cout<<var<<std::endl;
}

} //relax

#endif//RELAX_RELAX_H_

