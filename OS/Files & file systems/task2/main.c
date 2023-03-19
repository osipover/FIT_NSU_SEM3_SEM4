#include <string.h>
#include <stdio.h>
#include "commands.h"

int main(int argc, char** argv){
	char* command = GetCommandName();

	if (!strcmp(command, "makedir\n")) {
		return makedir(argc, argv);
	} else if (!strcmp(command, "outputdir\n")) {
		return outputdir(argc, argv);
	} else if (!strcmp(command, "removedir\n")) {
		return removedir(argc, argv);
	} else if (!strcmp(command, "makefile\n")) {
		return makefile(argc, argv);
	} else if (!strcmp(command, "outputfile\n")) {
		return outputfile(argc, argv);
	} else if (!strcmp(command, "removefile\n")) {
		return removefile(argc, argv);
	} else if (!strcmp(command, "makesymlink\n")) {
		return makesymlink(argc, argv);
	} else if (!strcmp(command, "readsymlink\n")) {
		return readsymlink(argc, argv);
	} else if (!strcmp(command, "outputsymlink\n")) {
		return outputsymlink(argc, argv);
	} else if (!strcmp(command, "removesymlink\n")) {
		return removesymlink(argc, argv);
	} else if (!strcmp(command, "makehardlink\n")) {
		return makehardlink(argc, argv);
	} else if (!strcmp(command, "removehardlink\n")) {
		return removehardlink(argc, argv);
	} else if (!strcmp(command, "outputdata\n")) {
		return outputdata(argc, argv);
	} else if (!strcmp(command, "setmode\n")) {
		return setmode(argc, argv);
	} else {
		printf("Error: unknown command\n");
		return -1;
	}
}
