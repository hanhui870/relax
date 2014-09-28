#include <cctype>
#include <cassert>
#include <map>
#include <stdio.h>
#include <relax/env_helper.h>
#include <relax/string_helper.h>

extern char ** environ;

namespace relax {
namespace utility {

using std::map;

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

    using ::relax::utility::StringHelper;
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
    value.assign("");
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

} //relax
} //utility
