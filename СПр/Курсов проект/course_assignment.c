#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#include "quick_sort.h"
#include "bubble_sort.h"
#include "shell_sort.h"
#include "merge_sort.h"

#include "args.h"

#define MIN_SIZE 6024
#define MEDIUM_SIZE 70200
#define LARGE_SIZE 250000

#define QUICK_SORT "quick_sort"
#define BUBBLE_SORT "bubble_sort"
#define SHELL_SORT "shell_sort"
#define MERGE_SORT "merge_sort"

#define DATA_SOURCE "data.txt"

typedef struct BenchmarkResult {
	char sortType[10];
	float timeToComplete;	

} BenchmarkResult;

void loadArrayFromFile(char *fileName, unsigned long arrSize, int *destination);
BenchmarkResult *sort(char *fileName, unsigned long arrSize, char *sortName, void (*sortFunc)(void *args));
void writeSortedArrToFile(int *sourceArr, unsigned long arrSize, BenchmarkResult *result);
void *startBenchmark(void *args);

BenchmarkArgs *newBenchmarkArgs(char *fileName, unsigned long arrSize, char *sortName, void (*sortFunc)(void *args));
ArrayArgs *newArrayArgs(int *arr, int size);

int main() {
	BenchmarkArgs *qSortArgs, *bSortArgs, *sSortArgs, *mSortArgs;
	void *qSortResult; void *bSortResult; void *sSortResult; void *mSortResult;
	pthread_t quickSortThread, bubbleSortThread, shellSortThread, mergeSortThread;

	qSortArgs = newBenchmarkArgs(DATA_SOURCE, MIN_SIZE, QUICK_SORT, quickSortWrapper);
	bSortArgs = newBenchmarkArgs(DATA_SOURCE, MIN_SIZE, BUBBLE_SORT, bubbleSortWrapper);
	sSortArgs = newBenchmarkArgs(DATA_SOURCE, MIN_SIZE, SHELL_SORT, shellSortWrapper);
	mSortArgs = newBenchmarkArgs(DATA_SOURCE, MIN_SIZE, MERGE_SORT, mergeSortWrapper);
	
	pthread_create(&quickSortThread, NULL, startBenchmark, (void*)qSortArgs);
	pthread_create(&mergeSortThread, NULL, startBenchmark, (void*)mSortArgs);
	pthread_create(&bubbleSortThread, NULL, startBenchmark, (void*)bSortArgs);
	pthread_create(&shellSortThread, NULL, startBenchmark, (void*)sSortArgs);
	
	pthread_join(quickSortThread, &qSortResult);
	pthread_join(bubbleSortThread, &bSortResult);
	pthread_join(shellSortThread, &sSortResult);
	pthread_join(mergeSortThread, &mSortResult);

	BenchmarkResult *qSort = qSortResult; BenchmarkResult *bSort = bSortResult;
	BenchmarkResult *sSort = sSortResult; BenchmarkResult *mSort = mSortResult;

	printf("Sort Type - %s\nTime - %f\n", qSort->sortType, qSort->timeToComplete);
	printf("Sort Type - %s\nTime - %f\n", bSort->sortType, bSort->timeToComplete);
	printf("Sort Type - %s\nTime - %f\n", sSort->sortType, sSort->timeToComplete);
	printf("Sort Type - %s\nTime - %f\n", mSort->sortType, mSort->timeToComplete);

	free(qSortArgs); free(bSortArgs); free(sSortArgs); free(mSortArgs);
	return 0;
}

void loadArrayFromFile(char *fileName, unsigned long arrSize, int *destination) {
	FILE *fp;
	unsigned long i;

	if ((fp = fopen(fileName, "r")) == NULL) {
		printf("Error opening file\n");
		return;
	}

	for (i = 0; i < arrSize; ++i) {
		fscanf(fp, "%d,", &destination[i]);
	}

	fclose(fp);
}

BenchmarkResult *sort(char *fileName, unsigned long arrSize, char *sortName, void (*sortFunc)(void *args)) {
	BenchmarkResult *result = (BenchmarkResult*)malloc(sizeof(BenchmarkResult));

	int *arr = (int*)calloc(arrSize, sizeof(int));
	loadArrayFromFile(fileName, arrSize, arr);

	ArrayArgs *args = newArrayArgs(arr, arrSize);	

	clock_t startOfSort = clock();
	(*sortFunc)((void*)args);
	clock_t endOfSort = clock();

	strcpy(result->sortType, sortName);
	result->timeToComplete = (float)(endOfSort - startOfSort) / CLOCKS_PER_SEC;

	writeSortedArrToFile(args->arr, arrSize, result);

	free(arr);
	free(args);

	return result;
}

void writeSortedArrToFile(int *sourceArr, unsigned long arrSize, BenchmarkResult *result) {
	FILE *fp;
	unsigned long i;
	char buff[24];
	char *name;
	strcpy(name, result->sortType);
	strcat(name, itoa(arrSize, buff, 10));

	if ((fp = fopen(strcat(name, "_result.txt"), "w")) == NULL) {
		printf("Error opening file\n");
		return;
	}

	fprintf(fp, "Sort Type - %s\nTime to Complete - %f seconds\n\n\n", result->sortType, result->timeToComplete);
	for (i = 0; i < arrSize; ++i) {
		fprintf(fp, "[%lu] - %d\n", i, sourceArr[i]);
	}
}

void *startBenchmark(void *args) {
	BenchmarkResult *result;

	result = sort(
		((BenchmarkArgs*)args)->fileName, 
		((BenchmarkArgs*)args)->arrSize, 
		((BenchmarkArgs*)args)->sortName, 
		((BenchmarkArgs*)args)->sortFunc
	);
	pthread_exit(result);
}

BenchmarkArgs *newBenchmarkArgs(char *fileName, unsigned long arrSize, char *sortName, void (*sortFunc)(void *args)) {
	
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