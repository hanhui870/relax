#include <iostream>
#include <event.h>
#include <thread>
#include <future>
#include <chrono>
#include <string>
#include <mutex>

using namespace std;

//使用了锁之后就不会出现文字输出和换行交叉出现的情况了
std::mutex outLock;
void echo1() {
	while (true) {
		std::lock_guard<mutex> lg(outLock);
		cout << "echo1" << endl;
		this_thread::sleep_for(chrono::microseconds(100000));
	}
}

void echo2() {
	while (true) {
		std::lock_guard<mutex> lg(outLock);
		cout << "echo2" << endl;
		this_thread::sleep_for(chrono::microseconds(100000));
	}
}

int main(int argc, char* argv[]) {
	auto result1 = async(launch::async, echo1);
	auto result2 = async(launch::async, echo2);

	try {
		result1.get();
		result2.get();
	} catch (exception& e) {

	}

	return 0;
}
