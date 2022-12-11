#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <climits>

#define ATTEMPTS 10

enum CacheLevel {
	L1 = 8192,		//32 [Кбайт] = 32 * 1024 [байт] = 32 * 1024 / 4 [int]
	L2 = 65536,		//256 [Кбайт] = 256 * 1024 [байт] = 256 * 1024 / 4 [int]
	L3 = 3145728	//12 [Мбайт] = 12 * 1024 * 1024 [байт] = 12 * 1024 * 1024 / 4 [int]
};

int* InitArray(int size, int offset, int fragmentSize, int numFragments) {
	int* arr = new int[size] {0};

	for (int i = 0; i < fragmentSize; ++i) {
		int position = i;
		for (int j = 1; j < numFragments; ++j) {
			arr[position] = position + offset;
			position = position + offset;
		}
		arr[position] = (i + 1) % fragmentSize;
	}

	return arr;
}

uint64_t GetTSC() {
	uint64_t highPart, lowPart;
	asm volatile("rdtsc\n":"=a"(lowPart), "=d"(highPart));
	return (highPart << 32) | (lowPart);
}


uint64_t GetTestResult(int* arr, int fragmentSize, int numFragments) {
	uint64_t start, end;
	uint64_t accessTime = 0, minAccessTime = INT_MAX;

	int k = 0;
	for (int count = 0; count < ATTEMPTS; ++count) {

		start = GetTSC();
		for (int i = 0; i < fragmentSize * numFragments; ++i) k = arr[k];
		end = GetTSC();

		if (k == 12345) std::cout << "Wow!";

		accessTime = (end - start) / (fragmentSize * numFragments);
		if (accessTime < minAccessTime) minAccessTime = accessTime;
	}
	delete[] arr;
	return minAccessTime;
}

void PrintArray(int* arr, int size) {
	for (int i = 0; i < size; ++i) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

std::string GetCacheLevel(int size) {
	if (size == L1) return "L1;;\n";
	if (size == L2) return "L2;;\n";
	if (size == L3) return "L3;;\n";
}

void TestCacheLevel(int cacheSize, std::ofstream& output) {
	output << GetCacheLevel(cacheSize);

	int* arr = nullptr;

	int offset = cacheSize;

	for (int numFragments = 1; numFragments <= 32; ++numFragments) {
		output << numFragments << ";";
		int fragmentSize = cacheSize / numFragments;
		int arraySize = cacheSize * numFragments;
    
		arr = InitArray(arraySize, offset, fragmentSize, numFragments);
		output << GetTestResult(arr, fragmentSize, numFragments) << ";\n";
	}
}

int main() {
	std::ofstream output;
	output.open("results.csv");
	if (!output.is_open()) return 1;

	output << "NumFragmenst;Ticks;\n";

	TestCacheLevel(L1, output);
	TestCacheLevel(L2, output);
	TestCacheLevel(L3, output);

	output.close();
	return 0;
}
