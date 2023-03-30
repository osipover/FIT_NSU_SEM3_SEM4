#include <stdio.h>
#include <unistd.h>

void print_hello(void){
	printf("Hello world\n");
}

int main(int argc, char **argv){
	print_hello();
	return 0;
}

