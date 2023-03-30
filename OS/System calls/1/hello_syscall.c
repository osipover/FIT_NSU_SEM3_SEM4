#include <sys/syscall.h>
#include <unistd.h>

void print_hello(int fd, const void *buf, size_t count){
	syscall(SYS_write, fd, buf, count);
}

int main(){
	print_hello(1, "Hello world\n", 12);
	return 0;
}
