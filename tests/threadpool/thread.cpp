#include "Poco/Thread.h"
#include "Poco/ThreadPool.h"
#include "Poco/Runnable.h"
#include "Poco/Mutex.h"
#include "Poco/RunnableAdapter.h"
#include "Poco/Exception.h"
#include <iostream>
#include <exception>
#include <assert.h>

using Poco::Mutex;
using Poco::ThreadPool;
using Poco::RunnableAdapter;
using Poco::Thread;
using namespace std;

Mutex _mutex;

class HelloRunnable: public Poco::Runnable {
public:
	HelloRunnable() : _event(false), Runnable(){
	}

	virtual void run() {
		_event.wait();
		Mutex::ScopedLock lock(_mutex);
		std::cout << "Hello, world!" << std::endl;
	}

	Poco::Event _event;
};

int main(int argc, char** argv) {
	HelloRunnable runnable;

	std::cout<<"thread pool test: "<<std::endl;

	ThreadPool pool(2, 3, 3);
	pool.setStackSize(1);

	assert (pool.allocated() == 2);
	assert (pool.used() == 0);
	assert (pool.capacity() == 3);
	assert (pool.available() == 3);
	pool.addCapacity(1);
	assert (pool.allocated() == 2);
	assert (pool.used() == 0);
	assert (pool.capacity() == 4);
	assert (pool.available() == 4);

	RunnableAdapter<HelloRunnable> ra(runnable, &HelloRunnable::run);
	pool.start(ra);
	assert (pool.allocated() == 2);
	assert (pool.used() == 1);
	assert (pool.capacity() == 4);
	assert (pool.available() == 3);

	pool.start(ra);
	assert (pool.allocated() == 2);
	assert (pool.used() == 2);
	assert (pool.capacity() == 4);
	assert (pool.available() == 2);

	pool.start(ra);
	assert (pool.allocated() == 3);
	assert (pool.used() == 3);
	assert (pool.capacity() == 4);
	assert (pool.available() == 1);

	pool.start(ra);
	assert (pool.allocated() == 4);
	assert (pool.used() == 4);
	assert (pool.capacity() == 4);
	assert (pool.available() == 0);

//没资源，执行不了
	try{
		pool.start(ra);
	}catch (Poco::NoThreadAvailableException&){
		std::cout<<"NoThreadAvailableException"<<std::endl;
	}catch (...){
		std::cout<<"wrong exception thrown"<<std::endl;
	}

	runnable._event.set(); // go!!!

	pool.joinAll();

	std::cout<<"single pool test: "<<std::endl;
	Poco::Thread thread;
	thread.start(runnable);
	//runnable._event.set(); // go!!!
	thread.join();

	thread.start(runnable);
	//runnable._event.set(); // go!!!
	thread.join();


	return 0;
}
