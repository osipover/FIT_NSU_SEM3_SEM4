enum WORK_RESULT {
	SUCCESS = 0,
	ARG_ERROR = 1,
	SYSCALL_ERROR = 2
};

char* GetCommandName(void);
int makedir(int argc, char** argv);
int outputdir(int argc, char** argv);
int removedir(int argc, char** argv);
int makefile(int argc, char** argv);
int outputfile(int argc, char** argv);
int removefile(int argc, char **argv);
int makesymlink(int argc, char **argv);
int readsymlink(int argc, char **argv);
int outputsymlink(int argc, char **argv);
int removesymlink(int argc, char **argv);
int makehardlink(int argc, char **argv);
int removehardlink(int argc, char **argv);
int outputdata(int argc, char **argv);
int setmode(int argc, char **argv);
