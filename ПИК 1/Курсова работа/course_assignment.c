#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFileWriteFile(); 
void readFileWriteScreen();
void readKeyboardWriteFile();
void readKeyboardWriteScreen();
char* getFileExtension(char fileName[]);

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
	char fileToRead[20];  // Name of file we'll read from
	char fileToWrite[20];  // Name of file where we'll write

	char buffer[250];  // Contains the lines read by fgets
	char longestLine[250];
	int longestLength = 0;

	printf("Enter the name of the file you want to read\n");
	scanf("%s", fileToRead);

	if(strcmp(getFileExtension(fileToRead), "c") != 0) {
		printf("Invalid extension");
		exit(0);
	}

	printf("Enter the name of the file where you want to write\n");
	scanf("%s", fileToWrite);

	fp = fopen(fileToRead, "r");
	if(fp == NULL) {
		perror("Error: ");
		exit(0);
	}

	while(fgets(buffer, sizeof buffer, fp) != NULL) {
		if(strlen(buffer) > longestLength) {  // If the line contains a printf with a \n character the logic screws up or not
			longestLength = strlen(buffer);
			strcpy(longestLine, buffer);
		}
	}

	fclose(fp);

	fp = fopen(fileToWrite, "w");
	if(fp == NULL) {
		perror("Error: ");
		exit(0);
	}

	fprintf(fp, "Longest line:\n %s\nIdentifier char count:\n %d\n", longestLine, 24);

	fclose(fp);
}

void readFileWriteScreen() {}

void readKeyboardWriteFile() {}

void readKeyboardWriteScreen() {}

char* getFileExtension(char fileName[]) {
	char *pch;
	char str[20];

	strcpy(str, fileName);
	pch = strtok(str, ".");
	pch = strtok(NULL, ".");

	return pch;
}