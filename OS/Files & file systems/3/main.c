#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

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
	fclose(file);
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
	printf("Enter virtual address:\n");
	assert(scanf("%s", virtAdd) == 1);
	return strtol(virtAdd, 0, 16);
}

void OutputPagemapInfo(char *pid, uint64_t startVirtAdd, uint64_t endVirtAdd) {
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

	uint64_t offsetStart = startVirtAdd / getpagesize() * 8;
	uint64_t offsetEnd = endVirtAdd / getpagesize() * 8;
	uint64_t numPages = offsetEnd - offsetStart;

	uint64_t bufferData = 0;
	fseek(pagemap, offsetStart, SEEK_SET);
	for (int i = 0; i < numPages; ++i) {
		fread(&bufferData, 8, 1, pagemap);
		printf("PFN: 0x%llx\n", (unsigned long long)GET_PFN(bufferData));
	}

	fclose(pagemap);
}

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Error: incorrect number of arguments\n");
		return 1;
	}

	char *pid = argv[1];
	
	OutputMaps(pid);

	uint64_t startVirtAdd = GetVirtualAddress();
	uint64_t endVirtAdd = GetVirtualAddress();

	OutputPagemapInfo(pid, startVirtAdd, endVirtAdd);
}

