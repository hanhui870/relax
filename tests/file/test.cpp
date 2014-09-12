#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
	ifstream ini;
	ini.open("application.ini");

	string data;
	string tmp;

	while(getline(ini, tmp)){
		data.append(tmp);
		data.append("\n");
	}

	cout<<data<<endl;

    return 0;
}
