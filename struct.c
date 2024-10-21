#include<stdio.h>

struct test {
	int a;
	struct test *p;
};

int main(int argc, char **argv){
	struct test t;	
	printf("size of struct a : %zu\n", sizeof(t));
	return 0;
}


