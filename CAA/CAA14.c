#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct listElement {
	int key;
	int data;

	struct listElement *next;
	struct listElement *prev;
} listElement;

listElement *listHead = NULL;
listElement *listTail = NULL;

bool isEmpty();
listElement* getNewElement(int key, int data;);
listElement* getElement(int key);
void insertFront(int key, int data);
void insertBack(int key, int data);
void deleteFront();
void deleteBack();
void deleteElement(listElement **element);
void insertAfter(int key, int newKey, int newData);
void printList();
void printListDesc();
void freeList();

int main() {
	int i;

	for (i = 5; i > 0; --i) 
		insertFront(i, i+10);

	for (i = 6; i <= 10; i++)
		insertBack(i, i+10);

	insertAfter(10, 11, 21);
	insertAfter(20, 13, 23);

	printList();
	
	deleteFront();
	deleteBack();

	printList();

	listElement *deletionElement = getElement(8);
	deleteElement(&deletionElement);

	listElement *deletionElement2 = getElement(24);
	deleteElement(&deletionElement2);
	
	printListDesc();

	freeList();

	return 0;
}

bool isEmpty() {
	return listHead == NULL;
}

listElement* getNewElement(int key, int data) {
	listElement *newElement = (listElement*)malloc(sizeof(listElement));

	newElement->key = key;
	newElement->data = data;

	newElement->next = NULL;
	newElement->prev = NULL;

	return newElement;
}

listElement* getElement(int key) {
	listElement *currPtr;

	if(isEmpty())
		return;

	for (currPtr = listHead; currPtr != NULL; currPtr = currPtr->next)	{
		if(currPtr->key == key) 
			return currPtr;
	}

	return NULL;
}

void insertFront(int key, int data) {
	listElement *element = getNewElement(key, data);

	if(isEmpty()) {
		listHead = listTail = element;
	} else {
		listHead->prev = element;

		element->next = listHead;
		listHead = element;
	}
}

void insertBack(int key, int data) {
	listElement *element = getNewElement(key, data);

	if(isEmpty()) {
		listHead = listTail = element;
	} else {
		listTail->next = element;

		element->prev = listTail;
		listTail = element;
	}
}

void deleteFront() {
	listElement *newHead;

	if(isEmpty())
		return;

	newHead = listHead->next;
	newHead->prev = NULL;

	free(listHead);
	listHead = newHead;
}

void deleteBack() {
	listElement *newTail;

	if(isEmpty())
		return;

	newTail = listTail->prev;
	newTail->next = NULL;

	free(listTail);
	listTail = newTail;
}

void deleteElement(listElement **element) {
	if(*element != NULL) {

		if((*element)->prev == NULL) {
			listHead = (*element)->next;

			if((*element)->next != NULL)
				(*element)->next->prev = NULL;

		} else if((*element)->next == NULL) {
			listTail = (*element)->prev;

			if((*element)->prev != NULL)
				(*element)->prev->next = NULL;

		} else {
			(*element)->prev->next = (*element)->next;

			(*element)->next->prev = (*element)->prev;
		}

		free(*element);
		*element = NULL;
	}
}

void insertAfter(int key, int newKey, int newData) {
	listElement *newElement = getNewElement(newKey, newData);
	listElement *currPtr;

	if(isEmpty()) {
		listHead = listTail = newElement;
	} else {
	
		for (currPtr = listHead; currPtr != NULL; currPtr = currPtr->next)	{
			if(currPtr->key == key) {
		
				newElement->next = currPtr->next;
				newElement->prev = currPtr;

				
				if(currPtr->next != NULL) {
					
					currPtr->next->prev = newElement;
				} else {

					listTail = newElement;
				}
				currPtr->next = newElement;

				return;
			}
		}		
		insertBack(newKey, newData);
	}
}

void printList() {
	if(isEmpty()) {
		printf("List Empty\n");
	} else {
		listElement *element = listHead;

		while(element != NULL) {
			printf("KEY - %d/DATA - %d\n", element->key, element->data);

			element = element->next;
		}
		printf("\n\n");
	}
}

void printListDesc() {
	if(isEmpty()) {
		printf("List Empty\n");
	} else {
		listElement *element = listTail;

		while(element != NULL) {
			printf("KEY - %d/DATA - %d\n", element->key, element->data);

			element = element->prev;
		}
		printf("\n\n");
	}
}

void freeList() {
	listElement *currPtr = listHead;

	if(isEmpty())
		return;

	while((currPtr = listHead) != NULL) {
		listHead = listHead->next;

		//printf("FREEING KEY - %d - DATA - %d\n", currPtr->key, currPtr->data);
		free(currPtr);
		currPtr = NULL;
	}
	printf("List freed\n");
}