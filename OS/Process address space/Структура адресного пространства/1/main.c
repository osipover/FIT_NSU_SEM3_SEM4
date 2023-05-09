#include <stdio.h>

int global_init = 10;
int global_notinit;
const int global_const = 11;

void show_variables_addresses() {
    int local_init = 20;
    int local_notinit;
    static int local_static = 21;
    const int local_const = 22;

    printf("global_init\t%d\t%p\n", global_init, &global_init);
    printf("global_notinit\t%d\t%p\n", global_notinit, &global_notinit);
    printf("global_const\t%d\t%p\n", global_const, &global_const);
    printf("local_init\t%d\t%p\n", local_init, &local_init);
    printf("local_notinit\t%d\t%p\n", local_notinit, &local_notinit);
    printf("local_static\t%d\t%p\n", local_static, &local_static); 
    printf("local_const\t%d\t%p\n", local_const, &local_const);
}

int show_maps() {
	FILE *file;
	if ((file = fopen("/proc/self/maps", "r")) == NULL) {
		printf("Error: unable to open maps");
		return -1;
	}

	char buffer;
	while(!feof(file)){
		fread(&buffer, 1, 1, file);
		printf("%c", buffer);
	}
	printf("\n\n");
	fclose(file);
	return 0;
}


int main(int argc, char** argv) {
    show_maps();
    show_variables_addresses();
}
