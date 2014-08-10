#include <random>
#include <iostream>
#include <cstdlib>

//直接调用居然每次值都一致
void printNumbers(std::default_random_engine& dre) {
	for (int i = 0; i <6; ++i) {
		std::cout << dre() << " ";
	}
	std::cout << std::endl;
}

//直接调用居然每次值都一致
void printDistr(std::default_random_engine& dre) {
	std::uniform_int_distribution<> dr(0, 50);

	std::cout << "a:" << dr.a()  << "	b:" << dr.b()  << "	min:" << dr.min() << "	max:" << dr.max() << std::endl;

	for (int i = 0; i < 6; ++i) {
		std::cout << dr(dre) << " ";
	}
	std::cout << std::endl;
}

//调用C的随机算法
void printCRand() {
	//如果seed相同每次随机产生的值相同
	srand( static_cast<unsigned>(32432));

	for (int i = 0; i < 6; ++i) {
		std::cout << "rand:" << rand() << std::endl;
	}
}

int main(int argc, char* argv[]) {
	std::default_random_engine dre;

	printNumbers(dre);

	printDistr(dre);

	printCRand();

	return 0;
}
