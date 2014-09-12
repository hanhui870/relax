#include <iostream>

using namespace std;

enum company{
	APPPLE=1,
	MICROSOFT,
	GOOGLE
}any=APPPLE;

#define MICROSOFT 3

int main(int argc, char* argv[]){
	//company cmp=MICROSOFT; //error 不能编译
	company cmp=GOOGLE;
	cout<<"Hello world."<<endl;
	cout<<"Google:"<<GOOGLE<<endl;
	cout<<"Mycmp:"<<cmp<<endl;
	cout<<"any:"<<any<<endl;
	return 0;
}
