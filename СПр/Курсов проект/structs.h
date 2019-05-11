#ifndef STRUCT_ARGS_H
#define STRUCT_ARGS_H

typedef struct BenchmarkResult {
	char sortType[20];
	float timeToComplete;	

} BenchmarkResult;

typedef struct ArrayArgs {
	int *arr;
	int firstEle;
	int lastEle;
	int size;

} ArrayArgs;

typedef struct BenchmarkArgs {
	char *fileName;
	unsigned long arrSize;
	char *sortName;

	void (*sortFunc)(void *args);

} BenchmarkArgs;

#endif