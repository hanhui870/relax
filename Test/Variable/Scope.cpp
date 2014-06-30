#include <iostream>
using namespace std;

/**
 * 语言坑测试
 *
 * Javascript是这样：
 * var foo='hello'; function fxn(){alert(foo);var foo="bye";}fxn(); alert(foo);
 * 第一个是undefined，第二个是hello。我第一个错了。因为在函数作用域内已经声明了该变量。哪怕是在末尾的。
 */
string foo="hello";
void fxn(){
	cout<<"string:"<<foo<<endl;

	string foo="bye";

	cout<<"after assign foo:"<<foo<<endl;
}

int main(int argc, char **argv){
	fxn();

	cout<<"string:"<<foo<<endl;
	return 0;
}
