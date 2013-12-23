#include <rapidjson/document.h>
#include <string>
#include <iostream>

int main() {
    void testDecode();
    testDecode();

    return 0;
}

/**
 * Json encode benchmark测试。
 *
 * 第一次：循环放在局部函数内，1百万耗时0m0.984s。
 * 第二次：document初始化放循环外1千万耗时0m28.713s。有内存泄漏。
 *      rapidjson::Document d;放在循环内部泄漏解除。但是慢了挺多。1千万0m30.415s。
 *      编译优化-O3 运行1千万耗时：0m13.067s，性能提升很大。
 */
void testDecode(){
    std::string str= "{\"name\":\"zhujingfa\",\"age\":26,\"ename\":\"hanhui\"}";

    for(int iter=0; iter<10000000; iter++){
        rapidjson::Document d;
        d.Parse<0>(str.c_str());
        d["name"].GetString();
        //std::cout<<d["name"].GetString();
    }
}
