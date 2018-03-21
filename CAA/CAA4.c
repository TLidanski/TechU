#include <stdio.h>
#include <stdlib.h>

int main() {
	int *arr;
	int i, size, success = 1;

	printf("Enter the array size\n");
	scanf("%d", &size);

	arr = malloc(size * sizeof(int));
	
	printf("Enter %d numbers\n", size);

	for (i = 0; i < size; ++i) {
		scanf("%d", &arr[i]);		
	}

	for (i = 0; i < size - 1; ++i) {

		if(i % 2 == 0 || i == 0) {

			if(!(arr[i] < arr[i+1]))
				success = 0;
		} else {

			if(!(arr[i] > arr[i+1]))
				success = 0;
		}
	}

	success ? printf("The relation fulfills the condition\n") : printf("The relation doesn't fulfill the condition\n");;

	free(arr);
	return 0;
}