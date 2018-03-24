#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEQUE_SIZE 9

typedef struct StaticDeque {
	int size;
	int capacity;
	int start;
	int end;

	int *elements;
} StaticDeque;

typedef struct Deque {
	int data;

	struct Deque *next;
	struct Deque *prev;
} Deque;

StaticDeque *staticDeque;

Deque *head;
Deque *tail;

Deque* getNewElement(int data);
bool isDequeEmpty();
void pushFront(int val);
void pushBack(int val);
void popFront();
void popBack();
void printDeque();
void freeDeque();

void initStaticDeque();
void pushStaticFront(int val);
void pushStaticBack(int val);
void popStaticFront();
void popStaticBack();
void printStatic();
void freeStatic();

int main() {
	int i;
	pushFront(2);
	pushFront(1);
	pushBack(7); printDeque();

	for(i = 0; i < 5; i++) {
		popBack();
	}

	pushBack(10);printDeque();
	freeDeque();

	// initStaticDeque();

	// pushStaticFront(1);
	// pushStaticFront(2);

	// pushStaticBack(21);
	// pushStaticBack(33);

	// printStatic();

	// for(i = 0; i < 7; i++) 
	// 	popStaticBack();	
	
	// printStatic();

	// pushStaticBack(245);
	// pushStaticFront(300);
	// pushStaticBack(212);
	// pushStaticBack(277);
	// pushStaticFront(10);
	// pushStaticFront(-23);
 // 	printStatic();
	// popStaticFront();popStaticFront();popStaticFront();

	// printStatic();
	// pushStaticFront(10);
	// pushStaticBack(77);
	// pushStaticFront(23);
	// pushStaticBack(79);

	// popStaticBack();
	// pushStaticBack(365);

	// printStatic();

	// pushStaticBack(4000);
	// pushStaticBack(899);

	// printStatic();
	// for(i = 0; i < 9; i++) 
	// 	popStaticFront();
	// pushStaticBack(100);
	// pushStaticFront(1);
	// printStatic();

	// freeStatic();
	return 0;
}

Deque* getNewElement(int data) {
	Deque *newElement = (Deque*)malloc(sizeof(Deque));

	newElement->data = data;
	newElement->next = newElement->prev = NULL;

	return newElement;
}

bool isDequeEmpty() {
	return head == NULL;
}

void pushFront(int val) {
	Deque *newElement = getNewElement(val);

	if(isDequeEmpty()) {
		head = tail = newElement;
	} else {
		head->prev = newElement;

		newElement->next = head;
		head = newElement;
	}
}

void pushBack(int val) {
	Deque *newElement = getNewElement(val);

	if(isDequeEmpty()) {
		head = tail = newElement;
	} else {
		tail->next = newElement;

		newElement->prev = tail;
		tail = newElement;
	}
}

void popFront() {
	Deque *newHead;

	if(isDequeEmpty()) {
		printf("Deque empty!\n");
		return;
	}

	newHead = head;
	head = head->next;

	if(head != NULL) { 
		head->prev = NULL;
	} else {
		tail = NULL;
	}

	if(newHead != NULL)
		free(newHead);
}

void popBack() {
	Deque *newTail;

	if(isDequeEmpty()) {
		printf("Deque empty!\n");
		return;
	}

	newTail = tail;
	tail = tail->prev;

	if(tail != NULL) {
		tail->next = NULL;
	} else {
		head = NULL;
	}
	
	if(newTail != NULL)
		free(newTail);
}

void printDeque() {
	if(isDequeEmpty()) {
		printf("List Empty\n");
	} else {
		Deque *element = head;

		while(element != NULL) {
			printf("DATA - %d\n", element->data);

			element = element->next;
		}
		printf("\n\n");
	}
}

void freeDeque() {
	Deque *currPtr = head;

	if(isDequeEmpty())
		return;

	while((currPtr = head) != NULL) {
		head = head->next;

		//printf("FREEING KEY - %d - DATA - %d\n", currPtr->key, currPtr->data);
		free(currPtr);
		currPtr = NULL;
	}
	printf("List freed\n");
}

void initStaticDeque() {
	staticDeque = (StaticDeque*)malloc(sizeof(StaticDeque));

	staticDeque->size = 0;
	staticDeque->start = staticDeque->end = 0;
	staticDeque->capacity = DEQUE_SIZE;

	staticDeque->elements = (int*)calloc(staticDeque->capacity, sizeof(int));
}

void pushStaticFront(int val) {
	int i;
	if(staticDeque->size < staticDeque->capacity) {
		
		if(staticDeque->size > 0 && staticDeque->start == 0)
			staticDeque->end++;
		staticDeque->size++;

		if(staticDeque->start == 0) {

			for (i = staticDeque->end; i > staticDeque->start; --i) 
				staticDeque->elements[i] = staticDeque->elements[i-1];
			
		} else {
			staticDeque->start--;
		}
		
		staticDeque->elements[staticDeque->start] = val;

	} else {
		printf("Deque full!\n");
	}
}

void pushStaticBack(int val) {
	int i;
	if(staticDeque->size < staticDeque->capacity) {

		if(staticDeque->end == staticDeque->capacity - 1) {
			
			for(i = 0; i < staticDeque->capacity; i++)
				staticDeque->elements[i] = staticDeque->elements[i+1];

			staticDeque->start--;
		} else {
			if(staticDeque->size > 0)
				staticDeque->end++;
		}

		staticDeque->elements[staticDeque->end] = val;

		staticDeque->size++;
	}
}

void popStaticFront() {
	if(staticDeque->size > 0) {
		staticDeque->elements[staticDeque->start] = 0;

		staticDeque->start++;
		staticDeque->size--;

		if(staticDeque->size == 0)
			staticDeque->start = staticDeque->end = 0;

	} else {
		printf("Deque is empty!\n"); 
	}
}

void popStaticBack() {
	if(staticDeque->size > 0) {
		staticDeque->elements[staticDeque->end] = 0;

		staticDeque->end--;
		staticDeque->size--;

		if(staticDeque->size == 0)
			staticDeque->start = staticDeque->end = 0;		
	} else {
		printf("Deque is empty!\n");
	}
}

void printStatic() {
	int i;
	for (i = 0; i < DEQUE_SIZE; ++i) {
		printf("Value at index [%d] is (%d)\n", i+1, staticDeque->elements[i]);
	}
	printf("\n\n");
} 

void freeStatic() {
	free(staticDeque->elements);
	staticDeque->elements = NULL;

	free(staticDeque);
	staticDeque = NULL;
}