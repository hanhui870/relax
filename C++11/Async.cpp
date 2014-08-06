#include <iostream>
#include <event.h>
#include <thread>
#include <future>
#include <chrono>

using namespace std;

void echo1(){
	int i=0;
	while(i<10){
		cout<<"echo1"<<endl;
		this_thread::sleep_for(chrono::microseconds(100000));
		i++;
	}
}

void echo2(){
	int i=0;
	while(i<10){
		cout<<"echo2"<<endl;
		this_thread::sleep_for(chrono::microseconds(100000));
		i++;
	}
}

int main(int argc, char* argv[]){
	auto result1=async(echo1);

	//auto result2=async(echo2);
	echo2();

	result1.get();
	//result2.get();
    return 0;
}
