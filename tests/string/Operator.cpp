#include <iostream>

int main(int argc, char **argv){
	std::string name;

	//string的+和=+操作符不一样的，前一个操作符返回一个新的对象，后一个返回原来的对象并会修改值。
	//operator + is different from =+,
	char temp[100]="fdasfdasfdsafdsa";
	std::cout<<name+temp<<std::endl;
	std::cout<<name<<std::endl;

	return 0;
}
