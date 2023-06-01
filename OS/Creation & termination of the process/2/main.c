#include "zombie.h"
#include <string.h>
#include <stdio.h>

char* get_programme_name();

int main(int argc, char** argv) {
    char* programme_name = get_programme_name();

    if (!strcmp(programme_name, "create-zombie\n")) {
        return create_zombie();
    }
    if (!strcmp(programme_name, "parent-zombie\n")) {
        return make_parent_zombie();
    }
    return -1;
}

char* get_programme_name() {
	FILE *curproc = fopen("/proc/self/status", "r");
	char *name = NULL;
	size_t length = 0;
	getline(&name, &length, curproc);
	name += 6;
	fclose(curproc);
	return name;
}

/*
*   To watch a list of processes and check that child process is zombie (<defunct>):
*   $ps -a
*   $ps -eF
*/
