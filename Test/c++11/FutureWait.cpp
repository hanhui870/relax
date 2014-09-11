#include <thread>
#include <future>
#include <chrono>
#include <random>
#include <iostream>
#include <exception>
using namespace std;

std::mutex outLock;
void doSomething(char c) {
	// random-number generator (use c as seed to get different sequences)
	default_random_engine dre(c);
	uniform_int_distribution<int> id(10, 1000);
	// loop to print character after a random period of time
	for (int i = 0; i < 1000; ++i) {
		std::lock_guard<mutex> lg(outLock);
		int tmp=id(dre);
		cout<<i<<" "<<" Char: "<<c<<" random:"<<tmp<<endl;
		this_thread::sleep_for(chrono::microseconds(tmp));
	}
}

int main() {
	cout << "starting 2 operations asynchronously" << endl;
	// start two loops in the background printing characters . or +
	auto f1 = async(launch::async, [] {doSomething('.');});
	auto f2 = async(launch::async, [] {doSomething('+');});

	// if at least one of the background tasks is running
	if (f1.wait_for(chrono::seconds(0)) != future_status::deferred
			|| f2.wait_for(chrono::seconds(0)) != future_status::deferred) {
		// poll until at least one of the loops finished
		while (f1.wait_for(chrono::seconds(0)) != future_status::ready
				&& f2.wait_for(chrono::seconds(0)) != future_status::ready) {
			this_thread::yield(); // hint to reschedule to the next thread

			//原例子没有这一行，导致cpu满负荷，哪怕休息一毫秒也是好的
			this_thread::sleep_for(chrono::microseconds(1));
		}
	}

	// wait for all loops to be finished and process any exception
	try {
		f1.get();
		f2.get();
	} catch (const exception& e) {
		cout << "\nEXCEPTION: " << e.what() << endl;
	}
	cout << "\ndone" << endl;
}

