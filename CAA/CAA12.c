#include <stdio.h>
#include <stdlib.h>

#define DEQUE_SIZE 9

typedef struct StaticDeque {
	int size;
	int frontLength;
	int backLength;

	int *elements;
} StaticDeque;

void allocateStaticDequeMem(StaticDeque **deque);
void pushStaticFront(StaticDeque **deque, int val);
void pushStaticBack(StaticDeque **deque, int val);
void printStatic(StaticDeque **deque);
void popFrontStatic(StaticDeque **deque);
void popBackStatic(StaticDeque **deque);

int main() {
	int i;
	StaticDeque *staticDeque;

	allocateStaticDequeMem(&staticDeque);

	pushStaticFront(&staticDeque, 2);
	pushStaticFront(&staticDeque, 1);

	pushStaticBack(&staticDeque, 10);
	pushStaticBack(&staticDeque, 11);

	for (i = 0; i < 10; ++i) {
		pushStaticBack(&staticDeque, i+12);
	}
	pushStaticFront(&staticDeque, 100);

	printStatic(&staticDeque);
	
	popFrontStatic(&staticDeque);
	
	popBackStatic(&staticDeque);
	popBackStatic(&staticDeque);

	printStatic(&staticDeque);

	return 0;
}

void allocateStaticDequeMem(StaticDeque **deque) {
	*deque = (StaticDeque*)malloc(sizeof(StaticDeque));

	(*deque)->size = DEQUE_SIZE;
	(*deque)->frontLength = 0;
	(*deque)->backLength = 0;

	(*deque)->elements = (int*)calloc((*deque)->size, sizeof(int));
}

void pushStaticFront(StaticDeque **deque, int val) {
	int i;
	if(((*deque)->frontLength + (*deque)->backLength) < DEQUE_SIZE) {

		for (i = (DEQUE_SIZE - (*deque)->backLength) - 1; i >= 0 ; i--)
	    	(*deque)->elements[i+1] = (*deque)->elements[i];

	    (*deque)->elements[0] = val;
	    (*deque)->frontLength++;
	} else {
		printf("Deque is full!\n");
	}
}

void pushStaticBack(StaticDeque **deque, int val) {
	int i;
	if((*deque)->frontLength + (*deque)->backLength < DEQUE_SIZE) {

		for (i = (*deque)->frontLength + 1; i < DEQUE_SIZE; i++)
	    	(*deque)->elements[i-1] = (*deque)->elements[i];

	    (*deque)->elements[DEQUE_SIZE - 1] = val;
	    (*deque)->backLength++;
	} else {
		printf("Deque is full!\n");
	}
}

void printStatic(StaticDeque **deque) {
	int i;
	for (i = 0; i < DEQUE_SIZE; ++i) {
		printf("Value at index [%d] equals:  %d\n", i+1, (*deque)->elements[i]);
	}
}

void popFrontStatic(StaticDeque **deque) {
	int i;
	if(((*deque)->frontLength + (*deque)->backLength) != 0) {

		for(i = 0; i < (*deque)->frontLength - 2; i++)
			(*deque)->elements[i] = (*deque)->elements[i+1];

		(*deque)->elements[(*deque)->frontLength - 1] = 0;
		(*deque)->frontLength--;
	} else {
		printf("Deque is empty!\n");
	}
}

void popBackStatic(StaticDeque **deque) {
	int i;
	if(((*deque)->frontLength + (*deque)->backLength) != 0) {

		for(i = DEQUE_SIZE - 1; i > DEQUE_SIZE - (*deque)->backLength + 1; i--)
			(*deque)->elements[i] = (*deque)->elements[i-1];
		
		(*deque)->elements[DEQUE_SIZE - (*deque)->backLength] = 0;
		(*deque)->backLength--;
	} else {
		printf("Deque is empty!\n");
	}
}