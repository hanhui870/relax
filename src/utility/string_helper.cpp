/**
 * Relax library
 *
 * @author 祝景法
 * @email zhujingfa@gmail.com
 *
 * @since 2014/09/17
 */
#include <relax/string_helper.h>
#include <cctype>
#include <cassert>

namespace relax {
namespace utility {

vector<string> StringHelper::Explode(string str, string delimiter) {
    string::size_type pos = 0;
    string::size_type pos_before = 0;
    vector<string> result;

    while (pos != string::npos) {
        pos_before = pos;
        pos = str.find(delimiter, pos_before + delimiter.size()); //pos自己是delimiter

        if (pos_before) { //非零
            pos_before += delimiter.size();
        }

        if (pos != string::npos) {
            result.push_back(str.substr(pos_before, pos - pos_before));
        } else {
            //最后一段
            result.push_back(str.substr(pos_before));
        }
    }

    return result;
}

string StringHelper::Trim(string str) {
    if (str.empty())
        return str;

    string::size_type start = 0, end = str.size();
    for (auto &elem : str) {
        if (std::isspace(elem)) {
            start++;
        } else {
            break;
        }
    }

    //全部空格
    if (start == end) {
        return string();
    }

    for (auto iter = str.rbegin(); iter != str.rend(); iter++) {
        if (std::isspace(*iter)) {
            end--;
        } else {
            break;
        }
    }

    assert(end > start);
    return str.substr(start, end - start);
}

void StringHelper::ToUpper(string str, string& value) {
    value.reserve(str.size());
    for (auto& c : str) {
        value.push_back(std::toupper(c));
    }
}

void StringHelper::ToUpper(string& str) {
    for (auto& c : str) {
        c = std::toupper(c);
    }
}

void StringHelper::ToLower(string str, string& value) {
    value.reserve(str.size());
    for (auto& c : str) {
        value.push_back(std::tolower(c));
    }
}

void StringHelper::ToLower(string& str) {
    for (auto& c : str) {
        c = std::tolower(c);
    }
}

} //relax
} //utility
