#include "commands.h"
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
		return ARG_ERROR;
	}

	if (mkdir(argv[1], 0777) == -1) {
    printf("Error: catched mkdir() exception\n");
		return SYSCALL_ERROR;
	}

	return SUCCESS;
}

int outputdir(int argc, char** argv) {
	if (argc != 2) {
		printf("Error: incorrect number of arguments\n");
		return ARG_ERROR;
	}
  
	DIR *dp;
	if ((dp = opendir(argv[1])) == NULL){
		printf("Error: unable to open directory:\n%s\n", argv[1]);
		return SYSCALL_ERROR;
	}

	struct dirent *entry;
	while ((entry = readdir(dp)) != NULL){
		printf("%s\n", entry->d_name);
	}

	closedir(dp);

	return SUCCESS;
}

int removedir(int argc, char** argv) {
	if (argc != 2) {
		printf("Error: incorrect number of arguments\n");
		return ARG_ERROR;
	}

	if (rmdir(argv[1]) == -1) {
		printf("Error: cathced rmdir() exception\n");
		return SYSCALL_ERROR;
	}

	return SUCCESS;
}

int makefile(int argc, char** argv) {
	if (argc != 2) {
		printf("Error: incorrect number of arguments\n");
		return ARG_ERROR;
	}

	if (creat(argv[1], S_IWRITE | S_IREAD) == -1) {
		printf("Error: catched creat() exception\n");
		return SYSCALL_ERROR;
	}

	return SUCCESS;
}

int outputfile(int argc, char** argv) {
	if (argc != 2) {
		printf("Error: incorrect number of arguments\n");
		return ARG_ERROR;
  }

	FILE *file;
	if ((file = fopen(argv[1], "r")) == NULL) {
		printf("Error: unable to open %s\n", argv[1]);
		return SYSCALL_ERROR;
	}

	char buffer;
	while(!feof(file)){
		fread(&buffer, 1, 1, file);
		printf("%c", buffer);
	}

	return SUCCESS;
}

int removefile(int argc, char **argv) {
	if (argc != 2) {
		printf("Error: incorrect number of arguments\n");
		return ARG_ERROR;
	}

	if(unlink(argv[1]) == -1) {
		printf("Error: unable to remove %s\n", argv[1]);
		return SYSCALL_ERROR;
	}

	return SUCCESS;
}

int makesymlink(int argc, char **argv) {
	if (argc != 3) {
		printf("Error: incorrect number of arguments\n");
		return ARG_ERROR;
	}

	if (symlink(argv[1], argv[2]) == -1) {
		printf("Error: unable to create symlink \"%s\" to \"%s\"\n", argv[2], argv[1]);
		return SYSCALL_ERROR;
	}

	return SUCCESS;
}

int readsymlink(int argc, char **argv) {
	if (argc != 2) {
		printf("Error: incorrect number of arguments\n");
		return ARG_ERROR;
	}

	const int BUFFER_SIZE = 256;
	char buffer[BUFFER_SIZE];
  
	if (readlink(argv[1], buffer, BUFFER_SIZE) == -1) {
		printf("Error: unable to read symlink \"%s\"\n", argv[1]);
		return SYSCALL_ERROR;
	 }

	printf("%s\n", buffer);

	return SUCCESS;
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
                return ARG_ERROR;
         }

        if (link(argv[1], argv[2]) == -1) {
                printf("Error: unable to create hardlink \"%s\" to \"%s\"\n", argv[2], argv[1]);
                return SYSCALL_ERROR;
        }
  
        return SUCCESS;
}

int removehardlink(int argc, char **argv) {
	return removefile(argc, argv);
}

int outputdata(int argc, char **argv) {
        if (argc != 2) {
                printf("Error: incorrect number of arguments\n");
                return ARG_ERROR;
        }
  
	struct stat filestat;
	if (stat(argv[1], &filestat) == -1) {
		printf("Error: unable to get status of \"%s\"\n", argv[1]);
		return SYSCALL_ERROR;
	}

	printf("Permission: %d\n", filestat.st_mode & 0777);
	printf("Number of hard links: %ld\n", filestat.st_nlink);

	return SUCCESS;
}

int setmode(int argc, char **argv) {
        if (argc != 3) {
                printf("Error: incorrect number of arguments\n");
                return ARG_ERROR;
        }

	if (chmod(argv[1], strtol(argv[2], 0, 2)) == -1) {
		printf("Error: unable to set mode for \"%s\"\n", argv[1]);
		return SYSCALL_ERROR;
	}

	return SUCCESS;
}

