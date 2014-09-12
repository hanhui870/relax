#include <stdio.h>

int exchange( int *xp, int y){
	int x = *xp;

	*xp=y;
	return x;
}

int main(int argc, char* argv[]){
	int x=5;

	int y=exchange(&x, 10);

	printf("hello world, x:%d  y:%d", x, y);

	return 0;
}
