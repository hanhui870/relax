#include <iostream>
#include <json/json.h>

using namespace std;
using namespace Json;

int main(int argc, char **argv){
    void testEncode();
	for(int iter=0; iter<1; iter++){
	    testEncode();
	}

	void testDecode();
    for(int iter=0; iter<1; iter++){
        testDecode();
    }
	return 0;
}

void testEncode(){
	Reader *reader=new Reader();
	Value value;
	string jsonString="{\"name\":\"zhujingfa\",\"age\":26,\"ename\":\"hanhui\"}";

	if(reader->parse(jsonString, value)){
	    //如果注释，不涉及IO，则快好多。
		cout<<"Name:"<<value["name"].asCString()<<"\n";
		cout<<"Age:"<<value["age"].asInt()<<"\n";
		cout<<"Ename:"<<value["ename"].asCString()<<endl;
	}

	delete reader;
}

void testDecode(){
    Value value;
    value["name"]="zhujingfa";
    value["age"]=26;
    value["ename"]="hanhui";

    cout<<value.toStyledString()<<endl;
}

