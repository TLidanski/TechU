#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
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

typedef struct BenchmarkArgs {
	char *sourceFile;
	unsigned long arrSize;
	char *sortName;
	int size;

	void (*sortFunc)(void *args);

} BenchmarkArgs;

void loadArrayFromFile(char *fileName, unsigned long arrSize, int *destination);
BenchmarkResult sort(char *fileName, unsigned long arrSize, char *sortName, void (*sortFunc)(void *args));
void writeSortedArrToFile(int *sourceArr, unsigned long arrSize, BenchmarkResult result);
void *startBenchmark(void *args);
ArrayArgs *newArrayArgs(int *arr, int size);

int main() {
	// BenchmarkArgs qSortArgs, bSortArgs, sSortArgs, mSortArgs;
	// BenchmarkResult qSortResult, bSortResult, sSortResult, mSortResult;

	BenchmarkResult r1 = sort(DATA_SOURCE, MIN_SIZE, QUICK_SORT, quickSortWrapper);
	BenchmarkResult r2 = sort(DATA_SOURCE, MIN_SIZE, BUBBLE_SORT, bubbleSortWrapper);
	BenchmarkResult r3 = sort(DATA_SOURCE, MIN_SIZE, SHELL_SORT, shellSortWrapper);
	BenchmarkResult r4 = sort(DATA_SOURCE, MIN_SIZE, MERGE_SORT, mergeSortWrapper);

	printf("Sort Type - %s\nTime - %f\n", r1.sortType, r1.timeToComplete);
	printf("Sort Type - %s\nTime - %f\n", r2.sortType, r2.timeToComplete);
	printf("Sort Type - %s\nTime - %f\n", r3.sortType, r3.timeToComplete);
	printf("Sort Type - %s\nTime - %f\n", r4.sortType, r4.timeToComplete);
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

BenchmarkResult sort(char *fileName, unsigned long arrSize, char *sortName, void (*sortFunc)(void *args)) {
	BenchmarkResult result;

	int *arr = (int*)calloc(arrSize, sizeof(int));
	loadArrayFromFile(fileName, arrSize, arr);

	ArrayArgs *args = newArrayArgs(arr, arrSize);	

	// pthread_create(&quickSortThread, NULL, quickSortWrapper, (void*)args);
	// pthread_join(quickSortThread, NULL);

	clock_t startOfSort = clock();

	(*sortFunc)((void*)args);

	clock_t endOfSort = clock();

	strcpy(result.sortType, sortName);
	result.timeToComplete = (float)(endOfSort - startOfSort) / CLOCKS_PER_SEC;

	writeSortedArrToFile(args->arr, arrSize, result);

	free(arr);
	free(args);

	return result;
}

void writeSortedArrToFile(int *sourceArr, unsigned long arrSize, BenchmarkResult result) {
	FILE *fp;
	unsigned long i;
	char buff[24];
	char *name;
	strcpy(name, result.sortType);
	strcat(name, itoa(arrSize, buff, 10));

	if ((fp = fopen(strcat(name, "_result.txt"), "w")) == NULL) {
		printf("Error opening file\n");
		return;
	}

	fprintf(fp, "Sort Type - %s\nTime to Complete - %f seconds\n\n\n", result.sortType, result.timeToComplete);
	for (i = 0; i < arrSize; ++i) {
		fprintf(fp, "[%lu] - %d\n", i, sourceArr[i]);
	}
}

void *startBenchmark(void *args) {
	pthread_t quickSortThread, bubbleSortThread, shellSortThread, mergeSortThread;
}

ArrayArgs *newArrayArgs(int *arr, int size) {
	ArrayArgs *args = (ArrayArgs*)malloc(sizeof(ArrayArgs));

	args->arr = arr;
	args->firstEle = 0;
	args->lastEle = size - 1;
	args->size = size;

	return args;
}