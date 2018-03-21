#include <stdio.h>
#include <stdlib.h>

int main() {
	int **arr;
	int i, t, colLength, rowLength, rowMin, rowMax, 
	minColMax, maxColMin, 
	rowMinIndex, rowMaxIndex, 
	hasMinExtremum = 0, hasMaxExtremum = 0, sCount = 0;

	printf("Enter how many columns you'd like\n");
	scanf("%d", &colLength);

	printf("Enter how many rows you'd like\n");
	scanf("%d", &rowLength);

	arr = malloc(colLength * sizeof(int*));
	for (i = 0; i < colLength; ++i) {
		arr[i] = malloc(rowLength * sizeof(int));
		
		printf("Enter %d numbers\n", rowLength);

		for (t = 0; t < rowLength; ++t) {
			scanf("%d", &arr[i][t]);
		}
	}


	for (i = 0; i < colLength; ++i) {
		rowMax = arr[i][0];
		rowMin = arr[i][0];

		for (t = 0; t < rowLength; ++t) {
			if(rowMax < arr[i][t]) {
				rowMax = arr[i][t];
				rowMaxIndex = t;
			}

			if(rowMin > arr[i][t]) {
				rowMin = arr[i][t];
				rowMinIndex = t;
			}
		}	


		maxColMin = arr[0][rowMaxIndex];

		minColMax = arr[0][rowMinIndex];

		for (t = 0; t < colLength; ++t) {
			if(maxColMin > arr[t][rowMaxIndex])
				maxColMin = arr[t][rowMaxIndex];

			if(minColMax < arr[t][rowMinIndex])
				minColMax = arr[t][rowMinIndex];

			if(arr[t][rowMaxIndex] == rowMax && t != 0)
				hasMaxExtremum = 1;

			if(arr[t][rowMinIndex] == rowMin && t != 0)
				hasMinExtremum = 1;
		}

		if(rowMax == maxColMin && !(hasMaxExtremum)) {
			printf("The value of the area is: %d\n", rowMax);
			sCount++;
		}

		if(rowMin == minColMax && !(hasMinExtremum)) {
			printf("The value of the area is: %d\n", rowMin);
			sCount++;
		}

		hasMinExtremum = hasMaxExtremum = 0;
	}


	for (i = 0; i < colLength; ++i) {
		free(arr[i]);
	}
	free(arr);

	printf("The number of such areas is: %d\n", sCount);

	return 0;
}