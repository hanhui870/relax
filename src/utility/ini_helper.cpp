/**
 * Relax library
 *
 * @author 祝景法
 * @email zhujingfa@gmail.com
 *
 * @since 2014/09/17
 */
#include <relax/ini_helper.h>
#include <map>

namespace relax {
namespace utility {

using std::map;

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
