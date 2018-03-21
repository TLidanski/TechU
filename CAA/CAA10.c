#include <stdio.h>
#include <stdlib.h>

void increment(int num, int n, int index, int step) {
	num += step;
	index++;

	if(index < n)
		increment(num, n, index, step);

	if(index == n)
		printf("The Nth element is: %d\n", num);
}

int main() {
	int n = 0, firstEle, index = 0, step;

	do {
		printf("Enter the index of the wanted element, must be between 0 and 20\n");
		scanf("%d", &n);
	} while(!(n > 0 && n <= 20));

	printf("Enter the step we'll use to increment\n");
	scanf("%d", &step);

	printf("Enter the first element of the sequence\n");
	scanf("%d", &firstEle);

	increment(firstEle, n, index, step);
	return 0;
}