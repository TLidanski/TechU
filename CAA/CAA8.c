#include <stdio.h>
#include <stdlib.h>

void printDescending(int index, int **arr) {
	if(--index >= 0) {
		printf("%d\n", *(*arr+index));
	
		printDescending(index, &(*arr));
	}
}

int main() {
	int *arr;
	int i, size;

	printf("Enter the array size\n");
	scanf("%d", &size);

	arr = (int*)malloc(size * sizeof(int));

	printf("Enter %d numbers\n", size);

	for (i = 0; i < size; ++i) {
		scanf("%d", &arr[i]);		
	}

	printDescending(size, &arr);

	return 0;
}