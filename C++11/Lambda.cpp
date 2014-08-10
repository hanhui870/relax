#include <iostream>
#include <string>
#include <functional>

int global = 11;

void print(std::function<void(void)> func) {
	func();
}

int main(int argc, char* argv[]) {
	int mainInt = 5;

	[=] {
		//如果没处理变量引用，全局变量可以引用，局部变量不能引用，会有错误
		std::cout<<"Hello, global:"<<global<<std::endl;
		//错误：‘mainInt’未被捕获
		std::cout<<"Hello, main:"<<mainInt<<std::endl;
		//mainInt++; //只读不能修改
	}();

	auto func = [&] {
		std::cout<<"Hello, main:"<<mainInt<<std::endl;
		mainInt++;
	};
	func();

	print([=] {
		std::cout<<"Hello, main:"<<mainInt<<std::endl;
	});

	//带参数lambda
	auto func2 = [] (int number) {
		std::cout<<"Hello, number:"<<number<<std::endl;
	};
	func2(88);

	return 0;
}
