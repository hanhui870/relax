/**
 * Test
 *
 * @author Bruce
 * @since 2014/07/07
 */
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[]){
	char *pc=new char();
	*pc='F';

	cout<<*pc<<endl;

	//非法指针移动位置，但这两行代码正常
	pc++;
	cout<<*pc<<endl;

	//删除错误指针造成core dump，挂了。
	delete pc;
    return 0;
}

