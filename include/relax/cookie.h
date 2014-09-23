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

class Cookie;

class CookieManager {
public:
    CookieManager() {
    }

    ~CookieManager() {

    }

    /**
     * 获取一个cookie管理实例
     */
    static CookieManager* GetInstance();

    /**
     * 获取一个cookie实例
     */
    Cookie& GetCookie(string domain);

private:
    //domain => cookie
    map<string, Cookie> container_;

    static CookieManager* instance_;
};

//原始cookie解析字符串
class CookieString;
//cookie值
class CookieValue;

class Cookie {
public:
    Cookie() {
    }

    ~Cookie() {

    }

    /**
     *添加一个cookie，多次添加直接覆盖
     */
    Cookie* Add(CookieString cookie_obj);
    Cookie* Add(const char* cookie_str);
    Cookie* Add(string name, string value);

    //获取Cookie
    string Get(string name);

    bool Delete(string name) {
        decltype(container_)::size_type deleted=container_.erase(name);

        if(deleted>0){
            return true;
        }else{
            return false;
        }
    }

    string ToString();

private:
    // name => value
    map<string, CookieValue> container_;
};

} //relax
} //fetcher
