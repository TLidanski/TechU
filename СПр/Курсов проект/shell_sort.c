#include "shell_sort.h"
#include "structs.h"

void shellSort(int arr[], int arrSize) { 
	int i, gap;
	for (gap = arrSize/2; gap > 0; gap /= 2) { 
		  
		for (i = gap; i < arrSize; i += 1) { 
			int temp = arr[i]; 
  
			int j;             
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) { 
				arr[j] = arr[j - gap]; 
			}  
			 
			arr[j] = temp; 
		} 
	} 
	 
}

void* shellSortWrapper(void *args) {
	shellSort(((ArrayArgs*)args)->arr, ((ArrayArgs*)args)->size);
}