#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>

char* GetCommandName() {
	FILE *curproc = fopen("/proc/self/status", "r");
	char *command = NULL;
	size_t length = 0;
	getline(&command, &length, curproc);
	command += 6;
	fclose(curproc);
	return command;
}

int makedir(int argc, char** argv) {
	if (argc != 2) {
		printf("Error: incorrect number of arguments\n");
		return 1;
	}

	if (mkdir(argv[1], 0777) == -1) {
    printf("Error: catched mkdir() exception\n");
		return 2;
	}

	return 0;
}



int outputdir(int argc, char** argv) {
	if (argc != 2) {
		printf("Error: incorrect number of arguments\n");
		return 1;
	}

	DIR *dp;
	if ((dp = opendir(argv[1])) == NULL){
		printf("Error: unable to open directory:\n%s\n", argv[1]);
		return 2;
	}

	struct dirent *entry;
	while ((entry = readdir(dp)) != NULL){
		printf("%s\n", entry->d_name);
	}
	closedir(dp);

	return 0;
}



int removedir(int argc, char** argv) {
	if (argc != 2) {
		printf("Error: incorrect number of arguments\n");
		return 1;
	}

	if (rmdir(argv[1]) == -1) {
		printf("Error: cathced rmdir() exception\n");
		return 2;
	}

	return 0;
}

int makefile(int argc, char** argv) {
	if (argc != 2) {
		printf("Error: incorrect number of arguments\n");
		return 1;
	}

	if (creat(argv[1], S_IWRITE | S_IREAD) == -1) {
		printf("Error: catched creat() exception\n");
		return 2;
	}

	return 0;
}

int outputfile(int argc, char** argv) {
	if (argc != 2) {
		printf("Error: incorrect number of arguments\n");
		return 1;
  }

	FILE *file;
	if ((file = fopen(argv[1], "r")) == NULL) {
		printf("Error: unable to open %s\n", argv[1]);
		return 2;
	}

	char buffer;
	while(!feof(file)){
		fread(&buffer, 1, 1, file);
		printf("%c", buffer);
	}

	return 0;
}



int removefile(int argc, char **argv) {
	if (argc != 2) {
		printf("Error: incorrect number of arguments\n");
		return 1;
	}

	if(unlink(argv[1]) == -1) {
		printf("Error: unable to remove %s\n", argv[1]);
		return 2;
	}

	return 0;
}

int makesymlink(int argc, char **argv) {
	if (argc != 3) {
		printf("Error: incorrect number of arguments\n");
		return 1;
	}

	if (symlink(argv[1], argv[2]) == -1) {
		printf("Error: unable to create symlink \"%s\" to \"%s\"\n", argv[2], argv[1]);
		return 2;
	}

	return 0;
}

int readsymlink(int argc, char **argv) {
	if (argc != 2) {
		printf("Error: incorrect number of arguments\n");
		return 1;
	}

	const int BUFFER_SIZE = 256;
	char buffer[BUFFER_SIZE];
	if (readlink(argv[1], buffer, BUFFER_SIZE) == -1) {
		printf("Error: unable to read symlink \"%s\"\n", argv[1]);
		return 2;
	 }
	printf("%s\n", buffer);

	return 0;
}


int outputsymlink(int argc, char **argv) {
	return outputfile(argc, argv);
}

int removesymlink(int argc, char **argv) {
	return removefile(argc, argv);
}

int makehardlink(int argc, char **argv) {
        if (argc != 3) {
                printf("Error: incorrect number of arguments\n");
                return 1;
         }

        if (link(argv[1], argv[2]) == -1) {
                printf("Error: unable to create hardlink \"%s\" to \"%s\"\n", argv[2], argv[1]);
                return 2;
        }
  
        return 0;
}

int removehardlink(int argc, char **argv) {
	return removefile(argc, argv);
}

int outputdata(int argc, char **argv) {
        if (argc != 2) {
                printf("Error: incorrect number of arguments\n");
                return 1;
        }

	struct stat filestat;
	if (stat(argv[1], &filestat) == -1) {
		printf("Error: unable to get status of \"%s\"\n", argv[1]);
		return 2;
	}

	printf("Permission: %d\n", filestat.st_mode & 0777);
	printf("Number of hard links: %ld\n", filestat.st_nlink);

	return 0;
}

int setmode(int argc, char **argv) {
        if (argc != 3) {
                printf("Error: incorrect number of arguments\n");
                return 1;
        }

	if (chmod(argv[1], strtol(argv[2], 0, 2)) == -1) {
		printf("Error: unable to set mode for \"%s\"\n", argv[1]);
		return 2;
	}

	return 0;
}



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
	}



}

