/**
 * Relax library
 *
 * @author 祝景法
 * @email zhujingfa@gmail.com
 *
 * @since 2014/09/17
 */
#include <iostream>
#include "Point3d.h"

using namespace std;

int main(int argc, char* argv[]){
	point3d* instance=new point3d(0.55, 0.868, 0.9668);

	cout<<instance->x()<<"  "<<instance->y()<<"  "<<instance->z()<<endl;
	delete instance;

	return 0;
}


