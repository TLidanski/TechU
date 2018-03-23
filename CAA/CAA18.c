#include <stdio.h>
#include <stdlib.h>

typedef struct Tree {
	int data;

	struct Tree *left;
	struct Tree *right;
} Tree;

int traverseTree(Tree **root, int *sum);
void createBranch(Tree **root, int data);
void populateTree(Tree **root, int data);
void freeTree(Tree **root);

int main() {
	int i, sum = 0;
	Tree *root = NULL;

	for (i = 0; i < 25; ++i) {
		populateTree(&root, rand() % (1000 + 1 - (-1000)) + (-1000));
	}

	traverseTree(&root, &sum);
	freeTree(&root);

	printf("\n\n\n");
	printf("The sum of even numbers is: %d\n", sum);
}

int traverseTree(Tree **root, int *sum) {
	if(*root != NULL) {
		printf("Current node  (%d)\n", (*root)->data);
		
		if((*root)->data % 2 == 0)
			(*sum) += (*root)->data;

		traverseTree(&((*root)->left), &(*sum));
		traverseTree(&((*root)->right), &(*sum));
	}
}

void createBranch(Tree **root, int data) {
	(*root) = (Tree*)malloc(sizeof(Tree));

	(*root)->data = data;
	(*root)->left = (*root)->right = NULL;
}

void populateTree(Tree **root, int data) {
	if(*root == NULL) {
		
		createBranch(&(*root), data);
	} else {

		if((*root)->data < data) {
			populateTree(&((*root)->left), data);
		} else {
			populateTree(&((*root)->right), data);
		}
	}
}

void freeTree(Tree **root) {
	if(*root != NULL) {
		freeTree(&((*root)->right));
		freeTree(&((*root)->left));
		
		free(*root);
		*root = NULL;
	}
}