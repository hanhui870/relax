#include <relax/timer.h>
#include <relax/ini_helper.h>
#include <iostream>
#include <string>
#include <memory>

using namespace std;
using namespace relax;
using relax::Status;

int main(int argc, char **argv){
	relax::timer t;

    IniHelper* ini=NULL;
	Status s=IniHelper::Factory("ini-test/app-not-exist.ini", &ini);
	if(s.IsFail()){
		cout<<"Failed to factory IniHelper instance: "<<s.message()<<endl;
	}

	{
		relax::timer t2;
		s=IniHelper::Factory("ini-test/app.ini", &ini);
	}
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

	/**
	 * 压测数据
	 *
	 * 压测 10万下，包含env->ToString();
	 * 家里I7，睿频到3GHZ
	 * 		10.334496s wall, 10.343000s user + 0.000000s system = 10.343000s CPU (100.1%)
	 * 公司I3电脑
	 * 		21.433274s wall, 21.372000s user + 0.015000s system = 21.387000s CPU (99.8%)
	 *
	 * 压测 100万下，删除env->ToString();
	 * 公司I3电脑
	 * 		4.181801s wall, 4.165000s user + 0.000000s system = 4.165000s CPU (99.6%)
	 * 		3.597247s wall, 3.603000s user + 0.000000s system = 3.603000s CPU (100.2%) //s=iniptr->Get("development", &env);在循环外
	 *		2.392870s wall, 2.386000s user + 0.000000s system = 2.386000s CPU (99.7%) //键获取减少StringHelper::Trim操作。
	 * 		PHP: 1418619236.2832 1418619239.2769 3s左右，性能也不差啊。
	 * 	家里I7
	 * 		1.208194s wall, 1.187000s user + 0.000000s system = 1.187000s CPU (98.2%) //无trim操作
	 */
	s=iniptr->Get("development", &env);
	for( int iter=0; iter<=1000000; iter++){
		if(s.IsFail()){
			//cout<<"Failed to fetch env development: "<<s.message()<<endl;
		}else{
			string value;
			s=env->Get("app.domain", value);
			if(s.IsFail()){
				//cout<<"Failed to fetch app.domain: "<<s.message()<<endl;
			}else{
				//cout<<"Fetch app.domain: "<<value<<endl;
			}
			//env->ToString();
			//cout<<"IniEnv::ToString() development: "<<endl<<env->ToString()<<endl;
		}
	}
	return 0;
}
