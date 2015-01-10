#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv){
	std::string name("hanhui");

	std::cout<<name<<std::endl;

	string::iterator iter=name.begin();

	std::cout<<"iter++: "<<*(++iter)<<std::endl;
	std::cout<<"iter+1: "<<*(iter+1)<<std::endl;

	return 0;
}
