#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFileWriteFile(); 
void readFileWriteScreen();
void readKeyboardWriteFile();
void readKeyboardWriteScreen();

int main() {
	printf("Select:\n1 - Read from file, write to file\n2 - Read from file, write to screen\n3 - Read from keyboard, write to file\n4 - Read from keyboard, write to screen\n");

	int select;
	scanf("%d", &select);

	switch(select) {
		case 1:
			readFileWriteFile();
		break;
		case 2:
			readFileWriteScreen();
		break;
		case 3:
			readKeyboardWriteFile();
		break;
		case 4:
			readKeyboardWriteScreen();
		break;

		default: 
			printf("Invalid value\n");
			exit(0);
	}

	return 0;
}

void readFileWriteFile() {
	FILE *fp;
	char fileToRead[20];  //Name of file we'll read from
	char fileToWrite[20];  //Name of file where we'll write

	printf("Enter the name of the file you want to read\n");
	scanf("%s", fileToRead);
	printf("Enter the name of the file where you want to write\n");
	scanf("%s", fileToWrite);

	fp = fopen(fileToRead, "r");
	if(fp == NULL) {
		perror("Error: ");
		return 1;
	}
}

void readFileWriteScreen() {

}

void readKeyboardWriteFile() {}

void readKeyboardWriteScreen() {}