/**
 * Relax library
 *
 * @author 祝景法
 * @email zhujingfa@gmail.com
 *
 * @since 2014/09/17
 */
#include <map>
#include <string>

namespace relax {
namespace fetcher {

using std::map;
using std::string;

class IniNode;
class NodeValue;

class IniHelper {
public:
    IniHelper(string filename) {

    }

    ~IniHelper() {

    }

    /**
     * 获取一个cookie实例
     */
    IniNode& Get(string env);

private:
    /**
     * environment => IniNode
     *
     * 不在命名空间下的是global环境，全局可用。其他通过继承关系解析。
     */
    map<string, IniNode> container_;
};

class IniNode {
public:
    IniNode() {

    }

    ~IniNode() {

    }

    /**
     * 获取一个cookie实例
     */
    IniNode& Get(string env);

private:

    map<string, NodeValue> container_;
};

class NodeValue {
public:
    NodeValue(IniNode* value) :
            value_(value), type_(NODE_BRANCH) {
    }

    NodeValue(string value) :
            value_(value), type_(NODE_LEAF) {
    }

    ~NodeValue() {
        if(type_==NODE_BRANCH){
            delete value_.node;
        }
    }

    enum ValueType {
        NODE_LEAF, NODE_BRANCH
    };
private:
    ValueType type_;

    union Value {
        IniNode* node;
        string value;
    };

    Value value_;
};

} //relax
} //utility
