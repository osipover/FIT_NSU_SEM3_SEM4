#include <stdio.h>
#include <unistd.h>

void print_hello(void){
	write(1, "Hello world\n", 12);
}

int main(int argc, char **argv){
	print_hello();
	return 0;
}

