#include <relax/timer.h>
#include <relax/ini_helper.h>
#include <iostream>
#include <string>
#include <memory>

using namespace std;
using relax::utility::IniHelper;
using relax::Status;

int main(int argc, char **argv){
    IniHelper* ini=NULL;
	Status s=IniHelper::Factory("ini-test/app-not-exist.ini", &ini);
	if(s.IsFail()){
		cout<<"Failed factory IniHelper instance: "<<s.message()<<endl;
	}

	s=IniHelper::Factory("ini-test/app.ini", &ini);
	if(s.IsFail()){
		cout<<"Failed factory IniHelper instance: "<<s.message()<<endl;
	}else{
		cout<<"Factory IniHelper instance address: "<<ini<<endl;
	}
	std::unique_ptr<IniHelper> iniptr(ini);

	return 0;
}
