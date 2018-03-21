#include <stdio.h>
#include <stdlib.h>

int main() {
	int *arr;
	int i, size, index, tempIndex, count = 0, maxLength = 0, length = 1;

	printf("Enter the array size\n");
	scanf("%d", &size);

	arr = (int*)malloc(size * sizeof(int));

	printf("Enter %d numbers\n", size);

	for (i = 0; i < size; ++i) {
		scanf("%d", &arr[i]);		
	}

	for (i = 1; i < size; ++i) {
		if(arr[i] < arr[i-1] && (i-1 == 0 || arr[i-2] <= arr[i-1])) {
			tempIndex = i - 1;

			count++;
		}

		if(arr[i] < arr[i-1])
			length++;

		if(length > maxLength) {
			maxLength = length;

			index = tempIndex;
		}

		if(arr[i] >= arr[i-1])
			length = 1;
	}

	printf("Number of descending sequences: %d\nLargest one's length: %d\nThe sequence itself: ", count, maxLength);
	for (i = 0; i < maxLength; ++i)	{
		printf("%d ", arr[index + i]);
	}

	free(arr);
	return 0;
}