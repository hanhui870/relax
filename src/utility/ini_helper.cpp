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
#include "string_parser.h"
#include <fstream>
#include <stdexcept>
#include <cctype>
#include <cstring>
#include <Poco/NumberParser.h>

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

IniHelper::~IniHelper(){
	for(auto iter : container_){
		delete iter.second;
	}
}

Status IniHelper::GetGlobalIni(IniEnv** global)
{
	*global=NULL;
	Status s=GetOrAppend(kGlobalIni, NULL, global);
	if(s.IsFail()){
		throw std::invalid_argument("Initialize global ini section failed.");
	}
	return s;
}


Status IniHelper::Get(string env, IniEnv** value){
	if(!container_.count(env)){
		Status::GetFail().set_message("Not found.");
	}
	*value=container_[env];
    return Status::GetOK();
}

Status IniHelper::GetOrAppend(string env, IniEnv* parent, IniEnv** value){
	if(!container_.count(env)){
		if(env!=kGlobalIni && parent==NULL){
			Status s;
			if((s=GetGlobalIni(&parent)).IsFail()){
				throw std::invalid_argument(s.message());
			}
		}
		container_.insert(std::make_pair(env, new IniEnv(parent)));
	}
	*value=container_[env];
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
    IniEnv* current=NULL;
    {
    	Status s;
		if((s=GetGlobalIni(&current)).IsFail()){
			throw std::invalid_argument(s.message());
		}
    }

    while(ifile.getline(buffer, kLineBufferSize)){
    	line_number++;
    	char* begin_char=buffer;
    	while(std::isspace(*begin_char)) begin_char=begin_char+1;

    	switch(*begin_char){
    	//忽略注释行
    	case ';':
    	//忽略空行，因为是getline的，是没有\n的
    	case '\0':
    		continue;
    		break;

    	case '[':
    	{//需要大括号规范变量作用域，不然可能报错
    		if(buffer[std::strlen(buffer)-1] != ']'){
    			 string message("Line format error, must begin with \"[\" end with \"]\", line ");
    			 throw std::invalid_argument(message + GetNumberText(line_number) +" read: "+buffer);
    		}

    		string env_text(begin_char+1);
    		env_text.pop_back();
    		//Debug::out(env_text);

    		vector<string> env_info=StringHelper::Explode(env_text, kEnvSeparator);
    		if(env_info.size()>2){
				string message("Env inheritance like [child : parent], no more than 3 level, line ");
    			throw std::invalid_argument(message + GetNumberText(line_number));
    		}

    		IniEnv* parent=NULL;
    		IniEnv* child=NULL;
    		if(env_info.size()==2){
    			string env_parent=StringHelper::Trim(env_info[1]);
    			Status s=GetOrAppend(env_parent, NULL, &parent);
    			if(s.IsFail()){
    				string message("Fetch parent IniEnv error, line ");
    				throw std::invalid_argument(message + GetNumberText(line_number));
    			}

    			string env_child=StringHelper::Trim(env_info[0]);
    			s=GetOrAppend(env_child, parent, &child);
    			if(s.IsFail()){
					string message("Fetch child IniEnv error, line ");
					throw std::invalid_argument(message + GetNumberText(line_number));
				}
			}else{//child 一级
				string env_child=StringHelper::Trim(env_info[0]);
				Status s=GetOrAppend(env_child, NULL, &child);
				if(s.IsFail()){
					string message("Fetch single child IniEnv error, line ");
					throw std::invalid_argument(message + GetNumberText(line_number));
				}
			}
    		current=child;
    		break;
    	}
    	default:
    	{
    		string line(begin_char);
    		//Debug::out(line);

    		if(StringHelper::Trim(line)!="" && line.find('=')==string::npos){
    			string message("Do not find sign equal '=', line ");
				throw std::invalid_argument(message + GetNumberText(line_number));
    		}

    		string name = StringHelper::Trim(line.substr(0, line.find(kAssign)));
    		string value = StringHelper::Trim(line.substr(line.find(kAssign) + 1));
    		Status s=current->Set(name, value);
    		if(s.IsFail()){
				string message("Fail to set value");
				throw std::invalid_argument(message +" message: "+s.message()+", line: "+ GetNumberText(line_number));
			}
    	    break;
    	}
    	}//switch
    }
}

/**
 * Ini值类型
 *
 * 可为树枝，上面可以有几个枝节关联几个页，但不能和页混合；
 * 可为树叶，关联一个具体值。
 */
class NodeValue {
public:
	const char* kKeySeparator=".";

    /**
     * 获取或添加一个子节点
     */
    Status GetChildOrAppend(string key, NodeValue** child);

    /**
    * 获取一个子节点
    */
   Status GetChild(string key, NodeValue** child);

    /**
     * 设置节点字符串值
     */
    Status SetValue(string value);

    /**
     * 递归获取当前node所有值
     */
    Status ToString(string& key, map<string, string>& value);

    enum ValueType {
        NODE_LEAF=0,
        NODE_BRANCH=1,
        NODE_OTHER,//未定
    };

protected:
    NodeValue() :
    	type_(NODE_OTHER){
	}

	~NodeValue();

private:
	friend class IniEnv;
    ValueType type_;

    //禁用拷贝、赋值
    NodeValue(const NodeValue&);
    NodeValue operator=(const NodeValue&);

    //类型有构造、析构等函数不能作为联合成员
    union Value {
    	//Union也需要显示初始化
    	Value() : value(NULL){}

        string* value;
        map<string, NodeValue*>* children;
    };

    Value value_;
};

NodeValue::~NodeValue(){
	if(type_ == NODE_LEAF){
		delete value_.value;
	}else if(type_ == NODE_BRANCH){
		for(auto iter : *value_.children){
			delete iter.second;
		}
	}
}

/**
 * 值设置
 *
 */
Status NodeValue::SetValue(string value){
    if(type_==NODE_BRANCH){
        return Status::GetFail().set_message("Branch node.");
    }else  if(type_==NODE_OTHER){
    	type_=NODE_LEAF;
    }

    if(value_.value!=NULL){
    	delete  value_.value;
    }

    //字符串解析
    StringParser p(value);
    string output;
    Status s=p.get(output);
    if(s.IsFail()){
    	return s;
    }
    value_.value=new string(output);

    return Status::GetOK();
}

Status NodeValue::GetChildOrAppend(string key, NodeValue** child){
	*child=NULL;
    if(type_==NODE_LEAF){
        return Status::GetFail().set_message("Leaf node.");
    }else  if(type_==NODE_OTHER){
    	type_=NODE_BRANCH;
    }

    if(value_.children==NULL){
    	value_.children =new map<string, NodeValue*>();
    }

    if(value_.children->count(key)){
        *child=value_.children->at(key);
    }else{
    	*child=new NodeValue();
        value_.children->insert(std::make_pair(key, *child));
    }

    return Status::GetOK();
}

Status NodeValue::GetChild(string key, NodeValue** child){
    if(type_==NODE_LEAF){
        return Status::GetFail().set_message("Leaf node.");
    }

    type_=NODE_BRANCH;
    if(value_.children->count(key)){
        *child=value_.children->at(key);
        return Status::GetOK();
    }

    return Status::GetFail().set_message("Not exist.");
}

/**
 * 将NodeValue递归转储为字符串
 */
Status NodeValue::ToString(string& key, map<string, string>& value){
	if(type_==NODE_LEAF){
		if(value.count(key)==0){
			value.insert(std::make_pair(key, *value_.value));
		}
	}else if(type_==NODE_BRANCH){
		for(auto iter : *value_.children){
			//传递临时字符串，解决递归bug
			string tmp(key+kKeySeparator+iter.first);
			iter.second->ToString(tmp, value);
		}
	}else{
		Status::GetFail().set_message("Found NODE_OTHER NodeValue.");
	}

	return Status::GetOK();
}

IniEnv::~IniEnv(){
	for(auto iter : container_){
		delete iter.second;
	}
}

/**
 * 获取ini配置值
 *
 * key没有trim操作，客户端自己保证正确
 */
Status IniEnv::Get(string key, string& value){
	vector<string> keyArray=StringHelper::Explode(key, kKeySeparator);
	if(keyArray.size()<1){
		Status::GetFail().set_message("Empty key.");
	}

	NodeValue *current=NULL, *parent=NULL;
	Status s;
	for(std::size_t iter=0; iter<keyArray.size(); ++iter){
		string keyTmp=keyArray[iter];
		if(iter==0){
			if(container_.count(keyTmp)){
				current=container_.at(keyTmp);
			}else{
				if(parent_){
					return parent_->Get(key, value);
				}
				return Status::GetFail().set_message(string("Faild to fetch value begin with ")+keyTmp);
			}
		}else{
			parent=current;
			s=current->GetChild(keyTmp, &current);
			if(s.IsFail()){
				return Status::GetFail().set_message(string("Faild to fetch child ")+keyTmp);
			}
		}
		if(iter==keyArray.size()-1){
			if(current->type_!=NodeValue::NODE_LEAF){
				return Status::GetFail().set_message(string("Value is not is leaf with key ")+key);
			}else{
				value=*(current->value_.value);
			}
		}
	}
	return Status::GetOK();
}

Status IniEnv::Get(string key, int& value){
	string tmp;
	Status s=Get(key, tmp);
	if(s.IsFail()) return s;

	if(Poco::NumberParser::tryParse(tmp, value)){
		return Status::GetOK();
	}else{
		return Status::GetFail().set_message("Invalid number string.");
	}
}

Status IniEnv::Get(string key, double& value){
	string tmp;
	Status s=Get(key, tmp);
	if(s.IsFail()) return s;

	if(Poco::NumberParser::tryParseFloat(tmp, value)){
		return Status::GetOK();
	}else{
		return Status::GetFail().set_message("Invalid number string.");
	}
}

/**
 * 设置解析配置值
 *
 * 需要处理:
 *   解析key的层级结构，放在对的环境下；
 *   正确解析值中的类型，字符串银行、整形浮点、环境常量等；
 *   trim掉键中不必要的空格；
 *
 * webrun.route.Action.Base='Route'NAME_SEP'Action'NAME_SEP'Base'
 */
Status IniEnv::Set(string key, string value){
	vector<string> keyArray=StringHelper::Explode(key, kKeySeparator);
	if(keyArray.size()<1){
		Status::GetFail().set_message("Empty key.");
	}

	NodeValue *current=NULL, *parent=NULL;
	Status s;
	for(std::size_t iter=0; iter<keyArray.size(); ++iter){
		string keyTmp=StringHelper::Trim(keyArray[iter]);
		if(keyTmp.size()<=0) {
			throw std::invalid_argument(string("IniEnv::Set an empty key found:")+key);
		}
		if(iter==0){
			if(container_.count(keyTmp)){
				current=container_.at(keyTmp);
			}else{
				current=new NodeValue();
				container_.insert(std::make_pair(keyTmp, current));
			}
		}else{
			parent=current;
			if(!parent){
				throw std::invalid_argument(string("IniEnv::Set an empty NodeValue *current found:")+key);
			}
			s=parent->GetChildOrAppend(keyTmp, &current);
			if(s.IsFail()){
				return Status::GetFail().set_message("Faild to fetch or append child.");
			}
		}
		if(iter==keyArray.size()-1){
			if(!current){
				throw std::invalid_argument(string("IniEnv::Set an empty NodeValue *current found to SetValue:")+key);
			}
			//最后一个，赋值
			Status s=current->SetValue(value);
			if(s.IsFail()){
				return s;
			}
		}
	}

	 return Status::GetOK();
}

string IniEnv::ToString(){
	string result;

	map<string, string> value;
	ToStringMap(value);

	for(auto iter : value){
		string key=iter.first;
		result.append(key+" "+kAssign+" "+iter.second+"\n");
	}

	return result;
}

Status IniEnv::ToStringMap(map<string, string>& value){
	for(auto iter : container_){
		string key=iter.first;
		iter.second->ToString(key, value);
	}

	//parent后解析 不覆盖
	if(parent_){
		parent_->ToStringMap(value);
	}

	return Status::GetOK();
}

/**
 * 获取数字的字符串表示
 */
static string GetNumberText(int num){
	string text;
	NumberHelper::IntegerToString(num, text);

	return text;
}



} //relax
} //utility
