/**
 * Relax library
 *
 * @author 祝景法
 * @email zhujingfa@gmail.com
 *
 * @since 2014/09/17
 */
#include <relax/ini_helper.h>
#include <relax/number_helper.h>
#include <relax/string_helper.h>
#include <fstream>
#include <stdexcept>
#include <cctype>
#include <cstring>

namespace relax {
namespace utility {

static string GetNumberText(int num);

Status IniHelper::Factory(string filename, IniHelper** instance){
    try{
        *instance=new IniHelper(filename);
    }catch(const std::invalid_argument& e){
        return Status::GetFail().set_message(e.what());
    }

    return Status::GetOK();
}

IniHelper::IniHelper(string& filename){
    using std::ifstream;
    const int kLineBufferSize=1024;

    ifstream ifile(filename);
    if(!ifile){
        string message("File");
        throw std::invalid_argument(message+" "+filename+" doesn't exist.");
    }

    char* buffer=new char[kLineBufferSize];
    //process file
    int line_number=0;
    while(ifile.getline(buffer, kLineBufferSize)){
    	line_number++;
    	char* begin_char=buffer;
    	while(std::isspace(*begin_char) && *begin_char!='\n') begin_char=begin_char+1;

    	switch(*begin_char){
    	//忽略注释行
    	case ';':
    		continue;
    		break;

    	case '[':
    		if(buffer[std::strlen(buffer)-1] != ']'){
    			 string message("Line format error, must begin with \"[\" end with \"]\", line ");
    			 throw std::invalid_argument(message + GetNumberText(line_number) +" read: "+buffer);
    		}

    		string env_text(begin_char+1);
    		env_text.pop_back();
    		//Debug::out(env_text);

    		vector<string> env_info=StringHelper::Explode(env_text, kEnvSeparator);
    		if(env_info.size()>2){
				string message("Env inheritence like [child : parent], no more than 3 level, line ");
    			throw std::invalid_argument(message + GetNumberText(line_number));
    		}

    		IniEnv parent;
    		IniEnv child;
    		if(env_info.size()==2){
    			string env_parent=StringHelper::Trim(env_info[1]);
    			Status s=GetOrAppend(env_parent, NULL, parent);
    			if(s.IsFail()){
    				string message("Fetch parent IniEnv error, line ");
    				throw std::invalid_argument(message + GetNumberText(line_number));
    			}

    			string env_child=StringHelper::Trim(env_info[0]);
    			s=GetOrAppend(env_child, &parent, child);
    			if(s.IsFail()){
					string message("Fetch child IniEnv error, line ");
					throw std::invalid_argument(message + GetNumberText(line_number));
				}
			}else{//child 一级
				string env_child=StringHelper::Trim(env_info[0]);
				Status s=GetOrAppend(env_child, NULL, child);
				if(s.IsFail()){
					string message("Fetch single child IniEnv error, line ");
					throw std::invalid_argument(message + GetNumberText(line_number));
				}
			}




    		break;
    	}

    }








}

/**
 * 获取数字的字符串表示
 */
static string GetNumberText(int num){
	string text;
	NumberHelper::IntegerToString(num, text);

	return text;
}

class NodeValue {
public:
    NodeValue() :
            type_(NODE_OHTER) {
    }

    ~NodeValue() {
    }

    /**
     * 获取或添加一个子节点
     */
    Status GetChildOrAppend(string key, NodeValue& child);

    /**
    * 获取一个子节点
    */
   Status GetChild(string key, NodeValue& child);

    /**
     * 设置节点字符串值
     */
    Status SetValue(string value);


    enum ValueType {
        NODE_LEAF=0,
        NODE_BRANCH=1,
        NODE_OHTER,//未定
    };
private:
    ValueType type_;

    //类型有构造、析构等函数不能作为联合成员
    union Value {
        string* value;
        map<string, NodeValue>* children;
    };

    Value value_;
};

Status NodeValue::SetValue(string value){
    if(type_==NODE_BRANCH){
        return Status::GetFail().set_message("Branch node.");
    }

    type_=NODE_LEAF;
    value_.value=new string(value);

    return Status::GetOK();
}

Status NodeValue::GetChildOrAppend(string key, NodeValue& child){
    if(type_==NODE_LEAF){
        return Status::GetFail().set_message("Leaf node.");
    }

    type_=NODE_BRANCH;
    if(value_.children->count(key)){
        child=value_.children->at(key);
    }else{
        value_.children->insert(std::make_pair(key, NodeValue()));
    }

    return Status::GetOK();
}

Status NodeValue::GetChild(string key, NodeValue& child){
    if(type_==NODE_LEAF){
        return Status::GetFail().set_message("Leaf node.");
    }

    type_=NODE_BRANCH;
    if(value_.children->count(key)){
        child=value_.children->at(key);
        return Status::GetOK();
    }

    return Status::GetFail().set_message("Not exist.");
}

} //relax
} //utility
