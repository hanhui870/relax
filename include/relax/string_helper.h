#include <string>
#include <vector>

namespace relax {
namespace utility {

using std::string;
using std::vector;

class StringHelper{
public:
    /**
     * 按字符串拆字符
     */
    static vector<string> explode(string str, string delimiter);

    /**
     * 移除两边的空格
     */
    static string trim(string str);

};

} //relax
} //utility
