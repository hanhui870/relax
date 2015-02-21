#include "Poco/Thread.h"
#include "Poco/ThreadPool.h"
#include "Poco/Runnable.h"
#include "Poco/Mutex.h"
#include <iostream>

using Poco::Mutex;
Mutex _mutex;

class HelloRunnable: public Poco::Runnable {
	virtual void run() {
		Mutex::ScopedLock lock(_mutex);
		std::cout << "Hello, world!" << std::endl;
	}
};

int main(int argc, char** argv) {
	HelloRunnable runnable;
	Poco::Thread thread;
	thread.start(runnable);
	thread.join();

	thread.start(runnable);
	thread.join();

	std::cout<<"thread pool test: "<<std::endl;

	HelloRunnable poolrun;
	for(int iter=0; iter<1000; iter++){
		Poco::ThreadPool::defaultPool().start(poolrun);
	}

	Poco::ThreadPool::defaultPool().joinAll();


	return 0;
}
