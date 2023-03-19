#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

#define GET_BIT(X, Y) ((X >> Y) & 1)
#define GET_PFN(DATA) (DATA & (((uint64_t)1 << 54) - 1))

int outputfile(char *path) {
	FILE *file;
	if ((file = fopen(path, "r")) == NULL) {
		printf("Error: unable to open %s\n", path);
		return 2;
	}

	char buffer;
	while(!feof(file)){
		fread(&buffer, 1, 1, file);
		printf("%c", buffer);
	}
	printf("\n\n");

	return 0;
}

void OutputMaps(char *pid) {
	char path[256];
  
	if (!strcmp(pid, "self")) {
		sprintf(path, "/proc/self/maps");
	} else {
		sprintf(path, "/proc/%s/maps", pid);
	}

	if(outputfile(path) != 0) {
		printf("Warrning: unable to output \"/proc/%s/maps\"\n", pid);
	}
}

unsigned long GetVirtualAddress() {
	char virtAdd[256];
	printf("Enter virtual address:\n0x");
	assert(scanf("%s", virtAdd) == 1);

	return strtol(virtAdd, 0, 16);
}

void OutputPagemapInfo(char *pid, uint64_t virtAdd) {
	char path[256];
  
        if (!strcmp(pid, "self")) {
                sprintf(path, "/proc/self/pagemap");
        } else {
                sprintf(path, "/proc/%s/pagemap", pid);
        }

	FILE *pagemap;
	if ((pagemap = fopen(path, "rb")) == NULL) {
		printf("Error: unable to open \"%s\"\n", path);
		return;
	}
  
	uint64_t offset = virtAdd / getpagesize() * 8;
  
	uint64_t bufferData = 0;

	fseek(pagemap, offset, SEEK_SET);
 	fread(&bufferData, 8, 1, pagemap);

	printf("Data: 0x%llx\n", (unsigned long long)bufferData);
	printf("PFN: 0x%llx\n", (unsigned long long)GET_PFN(bufferData));
}

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Error: incorrect number of arguments\n");
		return 1;
	}

	char *pid = argv[1];  
	OutputMaps(pid);
	uint64_t virtAdd = GetVirtualAddress();
	OutputPagemapInfo(pid, virtAdd);
}

