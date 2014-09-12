/**
 * Test
 *
 * @author Bruce
 * @since 2014/07/07
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

using namespace std;

int main(int argc, char* argv[]){
	int len=256*1024;
	char *pc=new char[len];
	char *ori=pc;
	memset(pc, 'z', len);
	cout<<*pc<<endl;

	//printf("char list:%s", pc);

	//在数组条件下可以移动，但是不能越界。
	pc++;
	cout<<*pc<<endl;

	//数组指针必须还原到最初申请来的内存地址才能正常被释放。不然报core dump，挂了。
	//delete [] --pc;
	delete [] ori;//正确形式

    return 0;
}

