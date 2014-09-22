#include <relax/env_helper.h>
#include <relax/string_helper.h>
#include <cctype>
#include <cassert>
#include <map>
#include <stdio.h>

extern char ** environ;

namespace relax {
namespace utility {

using std::map;

namespace {
class Variable {
public:
    Variable();
    ~Variable();

    string Get(string key);

    string Set(string key, string value);

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
        auto result=StringHelper::explode(*env, "=");
        try{
            container_[result.at(0)]=result.at(1);
        }catch(std::out_of_range& exception){
            container_[result.at(0)]="";
        }
    }
}

string Variable::Get(string key) {
    if(container_.count(key)){
        return container_[key];
    }

    return string();
}

}//anonymous ns

string EnvHelper::GetVariable(string key) {
    Variable* var=Variable::GetInstance();
    return var->Get(key);
}

} //relax
} //utility
