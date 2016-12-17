#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFileWriteFile(); 
void readFileWriteScreen();
void readKeyboardWriteFile();
void readKeyboardWriteScreen();
char* getLongestLine(FILE *fp);
int getIdentifierCharCount(FILE *fp);
char* getFileExtension(char fileName[]);
int isDataType(char *val);

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

	char longestLine[250];
	int idCharCount;

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

	strcpy(longestLine, getLongestLine(fp));
	rewind(fp);
	idCharCount = getIdentifierCharCount(fp);

	fclose(fp);

	fp = fopen(fileToWrite, "w");
	if(fp == NULL) {
		perror("Error: ");
		exit(0);
	}

	fprintf(fp, "Longest line:\n %s\nIdentifier char count:\n %d\n", longestLine, idCharCount);

	fclose(fp);
}

void readFileWriteScreen() {
	FILE *fp;
	char fileToRead[20];  // Name of file we'll read from

	char longestLine[250];
	int idCharCount;

	printf("Enter the name of the file you want to read\n");
	scanf("%s", fileToRead);

	if(strcmp(getFileExtension(fileToRead), "c") != 0) {
		printf("Invalid extension");
		exit(0);
	}

	fp = fopen(fileToRead, "r");
	if(fp == NULL) {
		perror("Error: ");
		exit(0);
	}

	strcpy(longestLine, getLongestLine(fp));
	rewind(fp);
	idCharCount = getIdentifierCharCount(fp);

	fclose(fp);

	printf("Longest line:\n %s\nIdentifier char count:\n %d\n", longestLine, idCharCount);
}

void readKeyboardWriteFile() {}

void readKeyboardWriteScreen() {}

char* getLongestLine(FILE *fp) {
	char buffer[250];  // Contains the lines read by fgets
	char *longestLine;
	int longestLength = 0;

	while(fgets(buffer, sizeof buffer, fp) != NULL) {  // If the line contains a printf with a \n character the logic might screw up
		if(strlen(buffer) > longestLength) {  
			longestLength = strlen(buffer);
			strcpy(longestLine, buffer);
		}
	}

	return longestLine;
}

int getIdentifierCharCount(FILE *fp) {  
	char buffer[30];  // Contains the strings read by fscanf
	int identifierCharCount = 0;
	int isIdentifier = 0;
	int i;

	while(fscanf(fp, "%s", buffer) == 1) {
		if(isIdentifier) {
			for (i = 0; i < strlen(buffer); ++i) {

				if(buffer[i] >= 'a' && buffer[i] <= 'z')
					identifierCharCount++; 
					// printf("%c\n", buffer[i]);

				if(buffer[i] == '(')
					break;
			}
		} 	
		isIdentifier = 0;

		if(isDataType(buffer))
			isIdentifier = 1;
	}

	return identifierCharCount;
}

char* getFileExtension(char fileName[]) {
	char *pch;  // Char pointer, cointains the parts of the split string
	char str[20];

	strcpy(str, fileName);
	pch = strtok(str, ".");
	pch = strtok(NULL, ".");

	return pch;
}

int isDataType(char *val) {
	int i;
	char *dataTypes[] = {"int", "double", "float", "char", "void"};
	int arrSize = sizeof dataTypes/sizeof dataTypes[0];

	for (i = 0; i < arrSize; ++i) {
		if(strcmp(dataTypes[i], val) == 0)
			return 1;
	}
	return 0;
}