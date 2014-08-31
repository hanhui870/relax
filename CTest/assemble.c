#include <stdio.h>

int exchange( int *xp, int y){
	int x = *xp;

	*xp=y;
	return x;
}

int main(int argc, char* argv[]){
	printf("hello world");

	return 0;
}
