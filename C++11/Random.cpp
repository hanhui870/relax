#include <random>
#include <iostream>

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

int main(int argc, char* argv[]) {
	std::default_random_engine dre;

	printNumbers(dre);

	printDistr(dre);

	return 0;
}
