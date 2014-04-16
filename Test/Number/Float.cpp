#include <iostream>
#include <cstdio>
#include <cstdlib>

/**
 * TODO 缘起，处理Dcoin项目狗币委托数量时有小数点问题
 *
 * 由于交易系统内部精确到八位小数点，可是php省略到八位后恰好不能进位
 *
 * var_dump(85379242.9642800000);//85379242.96428
 * var_dump(number_format(85379242.9642800000, 8, '.', ''));//85379242.96427999
 * var_dump(number_format(85379242.9642800000, 12, '.', ''));//85379242.964279994369
 *
 */
int main(int argc, char **argv){
	long double dbtest=85379242.9642800000;
	printf("%f\n", dbtest);//85379242.96427999400000000000

	std::string ldtest="85379242.9642800000";
	char *eptr;
	long double test=std::strtold(ldtest.c_str(), &eptr);
	printf("%f\n", test);
	std::cout<<test<<std::endl;
	return 0;
}
