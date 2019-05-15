#include "quick_sort.h"
#include "swap.h"
#include "structs.h"

int partition(int arr[], int firstEle, int lastEle) {

	int pivot = arr[lastEle];    
	int i = (firstEle - 1);   

	int j;
	for (j = firstEle; j <= lastEle - 1; j++) { 
		 
		if (arr[j] <= pivot) { 
			i++;     
			swap(&arr[i], &arr[j]); 
		} 
	} 
	swap(&arr[i + 1], &arr[lastEle]); 
	return (i + 1); 
}

void quickSort(int arr[], int firstEle, int lastEle) { 
	if (firstEle < lastEle) { 
		
		int pi = partition(arr, firstEle, lastEle);
		 
		quickSort(arr, firstEle, pi - 1); 
		quickSort(arr, pi + 1, lastEle); 
	} 
}

void* quickSortWrapper(void *args) {
	quickSort(((ArrayArgs*)args)->arr, ((ArrayArgs*)args)->firstEle, ((ArrayArgs*)args)->lastEle);
}