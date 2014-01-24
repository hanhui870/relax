#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

int main(int argc, char **argv){
	std::string name("hanhui");
	std::string key;
	char temp[100]="";
	std::sprintf(temp, "%d", 10000);
	std::cout<<temp<<"; Len:"<<std::strlen(temp)<<";atoi:"<<std::atoi(temp)<<std::endl;

	return 0;
}
