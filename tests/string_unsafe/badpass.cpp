/**
 * 字符串安全判断测试
 *
 * g++ -o test.exe badpass.cpp
 *
 * strcmp比较的字符串长短跟两个参数的大小有关。
 * 两个字符串自左向右逐个字符相比（按ASCII值大小相比较），直到出现不同的字符或遇'\0'为止。
 *
 * fdsfdsafdsafdsafdsafdsafdsafdsa  Segmentation fault (核心已转储)
 * 输入空格，无错误
 *
 * 有缓存区溢出，未检测gets返回状态的错误。
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool IsPassOK(void){
	char password[12];

	gets(password);

	return 0== strcmp(password, "goodpass");
}

int main(void){
	bool status;

	puts("Enter pass:");
	status=IsPassOK();

	if(status==false){
		puts("Access denied.");
		exit(-1);
	}else{
		puts("Access granted.");
	}
}
