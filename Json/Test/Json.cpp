#include <iostream>
#include <json/json.h>

using namespace std;
using namespace Json;

int main(int argc, char **argv){
    //void testEncode();
    //testEncode();

	void testDecode();
    testDecode();

	return 0;
}

/**
 * Json encode benchmark测试。
 *
 * 第一次放在内部函数中：1百万耗时就17.742s了。每秒5.6万
 * 第二次：Value初始化放在循环体外，1百万耗时就13.699s了。2nd：13.833s了。每秒7.2万。3th：-O3 0m13.653s
 */
void testEncode(){
    Value value;
    for(int iter=0; iter<1000000; iter++){
        value["name"]="zhujingfa";
        value["age"]=26;
        value["ename"]="hanhui";

        value.toStyledString();
        //cout<<value.toStyledString()<<endl;
    }
}

/**
 * Json encode benchmark测试。
 *
 * 第一次：循环放在main中，1百万耗时就14.681s了。
 * 第二次：循环放在局部函数内，Reader等只初始化一次。1百万耗时8.532s。
 */
void testDecode(){
    Reader *reader=new Reader();
    Value value;
    string jsonString="{\"name\":\"zhujingfa\",\"age\":26,\"ename\":\"hanhui\"}";

    for(int iter=0; iter<1000000; iter++){
        if(reader->parse(jsonString, value)){
            //如果注释，不涉及IO，则快好多。
            //cout<<"Name:"<<value["name"].asCString()<<"\n";
            //cout<<"Age:"<<value["age"].asInt()<<"\n";
            //cout<<"Ename:"<<value["ename"].asCString()<<endl;
        }
    }

    delete reader;
}

