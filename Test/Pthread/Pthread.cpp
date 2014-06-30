#include<unistd.h>
#include <pthread.h>
#include <iostream>
using namespace std;

void iter(void);

int main(int argc, char* argv[]){
	pid_t pidMain=getpid();
	cout<<"Started main process, pid:"<<pidMain<<";"<<endl;

	cout<<"Spawn a child process.\n"<<endl;
	pid_t child=0;
	child=fork();
	if(child){//this is parent
		cout<<"Created child process: "<<child<<endl;
	}else{
		cout<<"This is child process."<<endl;//child is 0
	}
	cout<<endl;

	iter();

	return 0;
}

void iter(void){
	pid_t pid=getpid();
	for(int iter=0 ; ;  iter++){
		cout<<"Iter now:"<<iter<<"; Pid is "<<pid<<endl;
		usleep(1500000);//1500ms
	}
}
