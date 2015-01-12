#include <cctype>
#include <cassert>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <relax/env_helper.h>
#include <relax/string_helper.h>

extern char ** environ;

namespace relax {

using std::map;

/**
 * ENV辅助类
 */
namespace {
class Variable {
public:
    Variable();
    ~Variable();

    Status Get(string key,  string& value);

    Status Set(string key, string value);

    static Variable* GetInstance();

private:
    //key => value
    map<string, string> container_;

    static Variable* instance_;
};

Variable* Variable::instance_ = NULL;

Variable* Variable::GetInstance() {
    if (Variable::instance_ == NULL) {
        Variable::instance_ = new Variable();
    }

    return Variable::instance_;
}

Variable::Variable() {
    char** env;

    using ::relax::StringHelper;
    for (env = environ; *env != 0; env++) {
        auto result=StringHelper::Explode(*env, "=");
        try{
            container_[result.at(0)]=result.at(1);
        }catch(std::out_of_range& exception){
            container_[result.at(0)]="";
        }
    }
}

Status Variable::Get(string key, string& value) {
    if(container_.count(key)){
        value=container_[key];
        return Status::GetOK();
    }
    return Status::GetFail();
}

Status Variable::Set(string key, string value) {
    container_[key]=value;

    return Status::GetOK();
}

}//anonymous ns

Status EnvHelper::GetVariable(string key, string& value) {
    Variable* var=Variable::GetInstance();
    return var->Get(key, value);
}

Status EnvHelper::SetVariable(string key, string value) {
    Variable* var=Variable::GetInstance();
    return var->Set(key, value);
}


/**
* 新设置或覆盖一个全局变量
*
* 注: 会对本进程的所有环境变量产生影响
*/
Status EnvHelper::GetGlobal(string key, string& value) {
    char* valTmp=getenv(key.c_str());
    if(valTmp==NULL){
        return Status::GetFail().set_message("Not found.");
    }

    value=valTmp;
    return Status::GetOK();
}

/**
 * 获取系统全局环境变量值
 */
Status EnvHelper::SetGlobal(string key, string value, OverWrite overwrite) {
    //setenv() copies its arguments
    if(overwrite==OW_YES){
        setenv(const_cast<char *>(key.c_str()), value.c_str(), 1);
    }else{
        setenv(const_cast<char *>(key.c_str()), value.c_str(), 0);
    }

    return Status::GetOK();
}

} //relax
