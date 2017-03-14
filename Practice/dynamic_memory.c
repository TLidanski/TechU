#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int sum = 0, i = 0, j, avg;
	int lessThanAvg = 0;
	FILE *fp;
	fp = fopen("numbers.txt", "r");
	char* buffer;
	buffer = (char*)malloc(sizeof(char));

	while(fscanf(fp, "%s", buffer) == 1) {
		i++;
	}rewind(fp);

	char** numArr;
	numArr = calloc(i, i * sizeof(char));
	if(numArr == NULL)
		exit(0);
	i = 0;

	while(fscanf(fp, "%s", buffer) == 1) {
		printf("%s\n", buffer);
		numArr[i] = calloc(1, (strlen(buffer) + 1) * sizeof(char));
		strcpy(numArr[i], buffer);

		sum += atoi(buffer);
		i++;
	}
	avg = sum/i;

	int arrSize = i * sizeof(char);
	for (j = 0; j < arrSize; ++j) {
		printf("%d - %s\n", j, numArr[j]);		

		if(atoi(numArr[j]) > avg)
			printf("%d\n", atoi(numArr[j]));

		if(atoi(numArr[j]) < avg)
			lessThanAvg += atoi(numArr[j]);
		// free(numArr[j]);
	}

	printf("AVERAGE - %d\n", avg);
	printf("SUM OF LESS THAN AVG - %d\n", lessThanAvg);

	fclose(fp);
	free(buffer);
	// free(numArr);
	return 0;
}