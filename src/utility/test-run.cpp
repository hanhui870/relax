#include <relax/timer.h>
#include <relax/ini_helper.h>
#include <iostream>
#include <string>
#include <memory>

using namespace std;
using namespace relax::utility;
using relax::Status;

int main(int argc, char **argv){
    IniHelper* ini=NULL;
	Status s=IniHelper::Factory("ini-test/app-not-exist.ini", &ini);
	if(s.IsFail()){
		cout<<"Failed to factory IniHelper instance: "<<s.message()<<endl;
	}

	s=IniHelper::Factory("ini-test/app.ini", &ini);
	if(s.IsFail()){
		cout<<"Failed factory IniHelper instance: "<<s.message()<<endl;
	}else{
		cout<<"Factory IniHelper instance address: "<<ini<<endl;
	}
	std::unique_ptr<IniHelper> iniptr(ini);

	IniEnv* env;
	s=iniptr->Get("production", &env);
	if(s.IsFail()){
		cout<<"Failed to fetch env production: "<<s.message()<<endl;
	}else{
		string value;
		s=env->Get("app.domain", value);
		if(s.IsFail()){
			cout<<"Failed to fetch app.domain: "<<s.message()<<endl;
		}else{
			cout<<"Fetch app.domain: "<<value<<endl;
		}

		cout<<"IniEnv::ToString() production: "<<endl<<env->ToString()<<endl;
	}

	s=iniptr->Get("development", &env);
	if(s.IsFail()){
		cout<<"Failed to fetch env development: "<<s.message()<<endl;
	}else{
		string value;
		s=env->Get("app.domain", value);
		if(s.IsFail()){
			cout<<"Failed to fetch app.domain: "<<s.message()<<endl;
		}else{
			cout<<"Fetch app.domain: "<<value<<endl;
		}

		cout<<"IniEnv::ToString() production: "<<endl<<env->ToString()<<endl;
	}
	return 0;
}
