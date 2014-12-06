#include <map>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char** argv){
	map<string, string> list;
	list["hanhui"]="zhejiang";
	list[string("rose")]="hubei";

	cout<<list.at("rose")<<endl;

	string tmp("jack");
	list.insert(make_pair(tmp, string("shanxi")));
	cout<<list.at("jack")<<endl;

	return 0;
}
