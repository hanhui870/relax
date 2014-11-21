/**
 * 函数初始化并传递参数的情况
 *
 * 尽量少这么用，不直观，尽量拆成两个表达式。
 *
 * int *test=testPtr(test);
 * ================
 * int *test;
 * test=testPtr(test);
 *
 */
#include <stdio.h>

int* testPtr(int* test){
	printf("test address value is %d\n", test);

	*test=100;

	return test;
}

//未初始化情况下给的是指针地址
int testVal(int val){
	printf("val uninitialized value is %d\n", val);

	val=100;
	//*(int*)val=100;

	return val;
}


int main(int argc, char* argv[]){
	//在cocos2d-x中看到这种用法，很奇怪，但传递地址可行。
	int *test=testPtr(test);
	printf("test is %d\n", *test);

	//传递给函数的值是未初始化的，默认好像是指针地址。
	int val=testVal(val);
	printf("val is %d\n", val);

	int initVal;
	printf("initVal address is %d, initVal uninitialized value is %d\n", &initVal, initVal);

	return 0;
}
