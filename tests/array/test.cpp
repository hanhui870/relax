#include <iostream>
#include <string>
#include <array>

using namespace std;

int main(int argc, char **argv){
    array<string, 10> as={"你好吗？", "我真的需要你的帮忙！", "这是一个什么样的社会"};

    cout<<as[0]<<as[2].c_str()<<endl;
}
