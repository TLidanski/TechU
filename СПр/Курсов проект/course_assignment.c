#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "quick_sort.h"
#include "bubble_sort.h"
#include "shell_sort.h"
#include "merge_sort.h"

#include "structs.h"

#define MIN_SIZE 10000
#define MEDIUM_SIZE 100000
#define LARGE_SIZE 1000000

#define DATA_SOURCE "input_data.txt"

#define RD_WR 0666

int *loadArrayFromFile(char *fileName, unsigned long arrSize);

void *sort(void *args);
void writeResultsToFile(char *destinationFile, BenchmarkResult *resArr[], int numOfResults, unsigned long benchmarkSize);
void startBenchmark(char *sourceFile, unsigned long size);

BenchmarkArgs *newBenchmarkArgs(char *sortName, char *fileName, unsigned long arrSize, void (*sortFunc)(void *args));
ArrayArgs *newArrayArgs(int *arr, int size);

int main() {
	startBenchmark(DATA_SOURCE, MIN_SIZE);

	startBenchmark(DATA_SOURCE, MEDIUM_SIZE);

	return 0;
}

int *loadArrayFromFile(char *fileName, unsigned long arrSize) {
	unsigned long i = 0;

	int *arr = (int*)calloc(arrSize, sizeof(int));
	int fileDesc = open(fileName, O_RDONLY);

	if (fileDesc < 0) {
		printf("Could not open file!\n");
		exit(0);
	}
	

	char *buff = (char*)malloc(sizeof(char));
	char *intString = (char*)malloc(sizeof(char));

	while (read(fileDesc, buff, sizeof(char)) != 0) {

		if (buff[0] == '\n') {

			// intString[strlen(intString)] = '\0';
			arr[i] = atoi(intString);
			i++;

			memset(intString, 0, sizeof(intString));
			intString = (char*)realloc(intString, sizeof(char));
		} else {

			strcat(intString, buff);
			intString = (char*)realloc(intString, (strlen(intString) + sizeof(char)));
		}		

		if (i == arrSize)
			break;
	}

	close(fileDesc);
	free(buff);
	free(intString);

	return arr;
}

void *sort(void *args) {
	BenchmarkArgs *benchMarkArgs = (BenchmarkArgs*)args;
	printf("Invoked %s sorting function\n", benchMarkArgs->sortName);

	BenchmarkResult *result = (BenchmarkResult*)malloc(sizeof(BenchmarkResult));

	
	int *arr = loadArrayFromFile(benchMarkArgs->fileName, benchMarkArgs->arrSize);

	ArrayArgs *sortArgs = newArrayArgs(arr, benchMarkArgs->arrSize);

	clock_t startOfSort = clock();
	benchMarkArgs->sortFunc((void*)sortArgs);
	clock_t endOfSort = clock();

	strcpy(result->sortType, benchMarkArgs->sortName);
	result->timeToComplete = (float)(endOfSort - startOfSort) / CLOCKS_PER_SEC;

	free(arr);
	free(sortArgs);

	pthread_exit(result);
}

void writeResultsToFile(char *destinationFile, BenchmarkResult *resArr[], int numOfResults, unsigned long benchmarkSize) {
	int i, bytes; char buff[100];

	int fileDesc = open(destinationFile, O_CREAT | O_APPEND | O_RDWR , RD_WR);
	if (fileDesc < 0) {
		printf("Could not open file!\n");
		return;	
	}
printf("FD = %d", fileDesc);
	
	bytes = sprintf(buff, "Results for benchmark with %lu elements\n", benchmarkSize);
	if(write(fileDesc, buff, bytes) < 0)
		printf("ERROR while writing results!\n");

	for (i = 0; i < numOfResults; ++i) {

		bytes = sprintf(buff, "Sort Type - %s\nTime - %f\n", resArr[i]->sortType, resArr[i]->timeToComplete);

		if (write(fileDesc, buff, bytes) < 0)
			printf("ERROR while writing results!\n");
	}	

	close(fileDesc);
}

void startBenchmark(char *sourceFile, unsigned long size) {
	BenchmarkArgs *qSortArgs, *bSortArgs, *sSortArgs, *mSortArgs;
	void *qSortResult; void *bSortResult; void *sSortResult; void *mSortResult;
	pthread_t quickSortThread, bubbleSortThread, shellSortThread, mergeSortThread;

	qSortArgs = newBenchmarkArgs("Quick Sort", sourceFile, size, quickSortWrapper);
	bSortArgs = newBenchmarkArgs("Bubble Sort", sourceFile, size, bubbleSortWrapper);
	sSortArgs = newBenchmarkArgs("Shell Sort", sourceFile, size, shellSortWrapper);
	mSortArgs = newBenchmarkArgs("Merge Sort", sourceFile, size, mergeSortWrapper);
	

	pthread_create(&quickSortThread, NULL, sort, (void*)qSortArgs); pthread_create(&mergeSortThread, NULL, sort, (void*)mSortArgs); 
	pthread_create(&bubbleSortThread, NULL, sort, (void*)bSortArgs); pthread_create(&shellSortThread, NULL, sort, (void*)sSortArgs);
	
	pthread_join(quickSortThread, &qSortResult); pthread_join(bubbleSortThread, &bSortResult);
	pthread_join(shellSortThread, &sSortResult); pthread_join(mergeSortThread, &mSortResult);

	BenchmarkResult *resultArr[4] = {
		(BenchmarkResult*)qSortResult, 
		(BenchmarkResult*)mSortResult, 
		(BenchmarkResult*)bSortResult, 
		(BenchmarkResult*)sSortResult
	};
	writeResultsToFile("benchmark_results.txt", resultArr, sizeof(resultArr) / sizeof(resultArr[0]), size);


	free(qSortArgs->fileName); free(qSortArgs->sortName); free(qSortArgs);
	free(bSortArgs->fileName); free(bSortArgs->sortName); free(bSortArgs);
	free(sSortArgs->fileName); free(sSortArgs->sortName); free(sSortArgs);
	free(mSortArgs->fileName); free(mSortArgs->sortName); free(mSortArgs);
	free(qSortResult); free(bSortResult); free(sSortResult); free(mSortResult);
}

BenchmarkArgs *newBenchmarkArgs(char *sortName, char *fileName, unsigned long arrSize, void (*sortFunc)(void *args)) {
	
	BenchmarkArgs *benchMarkArgs = (BenchmarkArgs*)malloc(sizeof(BenchmarkArgs));

	benchMarkArgs->fileName = malloc(strlen(fileName));
	strcpy(benchMarkArgs->fileName, fileName);
	
	benchMarkArgs->sortName = malloc(strlen(sortName));
	strcpy(benchMarkArgs->sortName, sortName);

	benchMarkArgs->arrSize = arrSize;
	benchMarkArgs->sortFunc = sortFunc;

	return benchMarkArgs;
}

ArrayArgs *newArrayArgs(int *arr, int size) {
	ArrayArgs *args = (ArrayArgs*)malloc(sizeof(ArrayArgs));

	args->arr = arr;
	args->firstEle = 0;
	args->lastEle = size - 1;
	args->size = size;

	return args;
}