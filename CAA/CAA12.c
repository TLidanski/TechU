#include <stdio.h>
#include <stdlib.h>

#define DEQUE_SIZE 9

typedef struct StaticDeque {
	int size;
	int frontLength;
	int backLength;

	int *elements;
} StaticDeque;

typedef struct Deque {
	int size; 
	int frontLength;
	int backLength;

	int *elements;
} Deque;

Deque *deque;

void allocateStaticDequeMem(StaticDeque **deque);
void pushStaticFront(StaticDeque **deque, int val);
void pushStaticBack(StaticDeque **deque, int val);
void printStatic(StaticDeque **deque);
void popFrontStatic(StaticDeque **deque);
void popBackStatic(StaticDeque **deque);
void freeStaticDeque(StaticDeque **deque);

void initDeque();
void pushFront(int val);
void pushBack(int val);
void popFront();
void popBack();
void printDeque();
void freeDeque();

int main() {
	int i;
	StaticDeque *staticDeque;

	allocateStaticDequeMem(&staticDeque);

	pushStaticFront(&staticDeque, 2);
	pushStaticFront(&staticDeque, 1);

	pushStaticBack(&staticDeque, 10);
	pushStaticBack(&staticDeque, 11);

	for (i = 0; i < 10; ++i) {
		pushStaticBack(&staticDeque, i+30);
	}
	pushStaticFront(&staticDeque, 100);

	printStatic(&staticDeque);
	
	popFrontStatic(&staticDeque);
	
	popBackStatic(&staticDeque);
	popBackStatic(&staticDeque);


	printStatic(&staticDeque);

	freeStaticDeque(&staticDeque);

	initDeque();
	for(i = 1; i < 12; i++)
		pushFront(i);

	pushBack(70);
	pushBack(77);
	pushBack(21);

	printDeque();

	popBack();
	popFront();

	printDeque();
	freeDeque();

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

	    ((*deque)->frontLength < 0) ? (*deque)->frontLength = 1 : (*deque)->frontLength++;
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

	    ((*deque)->backLength < 0) ? (*deque)->backLength = 1 : (*deque)->backLength++;
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
	if(((*deque)->frontLength + (*deque)->backLength) != 0 && (*deque)->frontLength > 0) {

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
	if(((*deque)->frontLength + (*deque)->backLength) != 0 && (*deque)->backLength > 0) {

		for(i = DEQUE_SIZE - 1; i > DEQUE_SIZE - (*deque)->backLength; i--)
			(*deque)->elements[i] = (*deque)->elements[i-1];
		
		(*deque)->elements[DEQUE_SIZE - (*deque)->backLength] = 0;
		(*deque)->backLength--;
	} else {
		printf("Deque is empty!\n");
	}
}

void freeStaticDeque(StaticDeque **deque) {
	free((*deque)->elements);
	free(*deque);
}

void initDeque() {
	deque = (Deque*)malloc(sizeof(Deque));

	deque->size = DEQUE_SIZE;
	deque->frontLength = 0;
	deque->backLength = 0;

	deque->elements = (int*)calloc(deque->size, sizeof(int));
}

void pushFront(int val) {
	int i;

	if((deque->frontLength + deque->backLength) < DEQUE_SIZE) {

		for (i = (deque->size - deque->backLength) - 1; i >= 0 ; i--)
	    	deque->elements[i+1] = deque->elements[i];

	    deque->elements[0] = val;

	    (deque->frontLength < 0) ? deque->frontLength = 1 : deque->frontLength++;
	} else {
		deque->size++;
		deque->elements = (int*)realloc(deque->elements, deque->size * sizeof(int));

		for (i = (deque->size - deque->backLength) - 1; i >= 0 ; i--)
	    	deque->elements[i+1] = deque->elements[i];

	    deque->elements[0] = val;
	    
	    (deque->frontLength < 0) ? deque->frontLength = 1 : deque->frontLength++;
	}
}

void pushBack(int val) {
	int i;

	if((deque->frontLength + deque->backLength) < DEQUE_SIZE) {

		for (i = deque->frontLength + 1; i < deque->size; i++)
	    	deque->elements[i-1] = deque->elements[i];

	    deque->elements[deque->size - 1] = val;

	    (deque->backLength < 0) ? deque->backLength = 1 : deque->backLength++;
	} else {
		deque->size++;
		deque->elements = (int*)realloc(deque->elements, deque->size * sizeof(int));

	    deque->elements[deque->size - 1] = val;

	    (deque->backLength < 0) ? deque->backLength = 1 : deque->backLength++;
	}
}

void popFront() {
	int i;
	if(deque->size > 1) {
		int *temp = (int*)calloc(deque->size - 1, sizeof(int));

		for (i = 1; i < deque->size; ++i) 
			temp[i-1] = deque->elements[i];

		deque->frontLength--;
		deque->size--;

		free(deque->elements);
		deque->elements = temp;
	}
}

void popBack() {
	int i;
	if(deque->size > 1) {
		int *temp = (int*)calloc(deque->size - 1, sizeof(int));

		for (i = 0; i < deque->size - 1; ++i) 
			temp[i] = deque->elements[i];

		deque->backLength--;
		deque->size--;

		free(deque->elements);
		deque->elements = temp;
	}
}

void printDeque() {
	int i;
	for (i = 0; i < deque->size; ++i) {
		printf("DYNAMIC DEQUE VALUE at index [%d]  IS  (%d)\n", i+1, deque->elements[i]);
	}
	printf("\n\n\n");
}

void freeDeque() {
	free(deque->elements);
	free(deque);
}