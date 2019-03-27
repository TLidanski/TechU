#include "bubble_sort.h"
#include "swap.h"

void bubbleSort(int arr[], int arrSize) { 
	int i, j; 

	for (i = 0; i < arrSize-1; i++) {

		for (j = 0; j < arrSize-i-1; j++) { 
		
			if (arr[j] > arr[j+1]) 
				swap(&arr[j], &arr[j+1]);
		}
	}
}