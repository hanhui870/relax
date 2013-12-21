#include <iostream>
#include <json/json.h>

using namespace std;
using namespace Json;

int main(int argc, char **argv){
    void testEncode();
	for(int iter=0; iter<=1000000; iter++){
		testEncode();
	}
	return 0;
}

void testEncode(){
	Reader *reader=new Reader();
	Value value;
	string jsonString="{\"name\":\"zhujingfa\",\"age\":26,\"ename\":\"hanhui\"}";

	if(reader->parse(jsonString, value)){
		cout<<"Name:"<<value["name"].asCString()<<"\n";
		cout<<"Age:"<<value["age"].asInt()<<"\n";
		cout<<"Ename:"<<value["ename"].asCString()<<endl;
	}

	delete reader;
}

