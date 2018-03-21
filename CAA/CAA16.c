#include <stdio.h>
#include <stdlib.h>

typedef struct Tree {
	int data;

	struct Tree *left;
	struct Tree *right;
} Tree;

void printTree(Tree **root);
void createBranch(Tree **root, int data);
void populateTree(Tree **root, int data);
void freeTree(Tree **root);

int main() {
	int i;
	Tree *root = NULL;

	for (i = 0; i < 25; ++i) {
		populateTree(&root, rand() % (1000 + 1 - (-1000)) + (-1000));
	}

	printTree(&root);
	freeTree(&root);

	return 0;
}

void printTree(Tree **root) {
	if(*root != NULL) {
		if((*root)->data > 0)
			printf("POSITIVE NUMBERS:  %d\n", (*root)->data);

		printTree(&((*root)->left));
		printTree(&((*root)->right));

		if((*root)->data < 0)
			printf("negative numbers:  %d\n", (*root)->data);
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