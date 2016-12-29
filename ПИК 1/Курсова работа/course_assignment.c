#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 250

void readFileWriteFile(); 
void readFileWriteScreen();
void readKeyboardWriteFile();
void readKeyboardWriteScreen();
char* getLongestLine(FILE *fp);
int getIdentifierCharCount(FILE *fp);
void countIdentifiers(char *inputStream, int *idCharCount, int *isIdentifier, int *isFunc, int *isArg);
char* getFileExtension(char fileName[]);
int isDataType(char *val);
int hasSemicolon(char *val);

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

	char longestLine[MAXSIZE];
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

	char longestLine[MAXSIZE];
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

void readKeyboardWriteFile() {
	FILE *fp;
	char keyboardInput[30]; char fileToWrite[20]; 
	char longestLine[MAXSIZE]; char lines[20][MAXSIZE] = {};
	int longestLength = 0; int idCharCount = 0; int i;
	int isIdentifier = 0; int isFunc = 0; int isArg = 0;
	int lineNum = 0;

	printf("Enter the name of the file where you want to write\n");
	scanf("%s", fileToWrite);

	printf("Enter the code\n");
	while(scanf("%s", keyboardInput) == 1) {
		strcat(lines[lineNum], keyboardInput);

		if(strcmp(keyboardInput, "{") == 0 || hasSemicolon(keyboardInput))
			lineNum++;	

		countIdentifiers(keyboardInput, &idCharCount, &isIdentifier, &isFunc, &isArg);
	}

	for (i = 0; i < lineNum; ++i) {
		if(strlen(lines[i]) > longestLength) {
			longestLength = strlen(lines[i]);
			strcpy(longestLine, lines[i]);
		}
	}

	if(lineNum == 0)
		strcpy(longestLine, lines[0]);

	fp = fopen(fileToWrite, "w");
	if(fp == NULL) {
		perror("Error: ");
		exit(0);
	}

	fprintf(fp, "Longest line:\n %s\nIdentifier char count:\n %d\n", longestLine, idCharCount);	
	fclose(fp);
}

void readKeyboardWriteScreen() {
	char keyboardInput[30]; 
	char longestLine[MAXSIZE]; char lines[20][MAXSIZE] = {};
	int longestLength = 0; int idCharCount = 0; int i;
	int isIdentifier = 0; int isFunc = 0; int isArg = 0;
	int lineNum = 0;

	printf("Enter the code\n");
	while(scanf("%s", keyboardInput) == 1) {
		strcat(lines[lineNum], keyboardInput);

		if(strcmp(keyboardInput, "{") == 0 || hasSemicolon(keyboardInput))
			lineNum++;	

		countIdentifiers(keyboardInput, &idCharCount, &isIdentifier, &isFunc, &isArg);
	}

	for (i = 0; i < lineNum; ++i) {
		if(strlen(lines[i]) > longestLength) {
			longestLength = strlen(lines[i]);
			strcpy(longestLine, lines[i]);
		}
	}

	if(lineNum == 0)
		strcpy(longestLine, lines[0]);

	printf("Longest line:\n %s\nIdentifier char count:\n %d\n", longestLine, idCharCount);
}

char* getLongestLine(FILE *fp) {
	char buffer[MAXSIZE];  // Contains the lines read by fgets
	char longestLine[MAXSIZE];
	int longestLength = 0;

	while(fgets(buffer, sizeof buffer, fp) != NULL) {  
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
	int isIdentifier = 0; int isFunc = 0; int isArg = 0;

	while(fscanf(fp, "%s", buffer) == 1) {
		countIdentifiers(buffer, &identifierCharCount, &isIdentifier, &isFunc, &isArg);
	}

	return identifierCharCount;
}

void countIdentifiers(char *inputStream, int *idCharCount, int *isIdentifier, int *isFunc, int *isArg) {
	int i;

	if(*isIdentifier || *isArg) {			
		if(*isArg)
			*isArg = 0;

		for (i = 0; i < strlen(inputStream); ++i) {
			if(*isFunc && inputStream[i] == ')')
				*isFunc = 0;

			if(*isFunc && *isIdentifier && inputStream[i] != ')') {
				*isFunc = 0;
				*isArg = 1;
				break;
			}

			if((inputStream[i] >= 'a' && inputStream[i] <= 'z') || (inputStream[i] >= 'A' && inputStream[i] <= 'Z'))
				(*idCharCount)++;

			if(inputStream[i] == '(')
				*isFunc = 1;

			if(inputStream[i] == ',' && *isIdentifier)
				*isArg = 1;
		}
	} 	
	*isIdentifier = 0;

	if(isDataType(inputStream))
		*isIdentifier = 1;
}

char* getFileExtension(char fileName[]) {
	char *pch;  // Char pointer, cointains the parts of the split string
	char str[20];

	strcpy(str, fileName);
	pch = strtok(str, ".");
	pch = strtok(NULL, ".");

	if(pch == NULL)
		return fileName;
	return pch;
}

int isDataType(char *val) {
	int i;
	char *dataTypes[] = {"int", "double", "float", "char", "void", "FILE"};
	int arrSize = sizeof dataTypes/sizeof dataTypes[0];

	for (i = 0; i < arrSize; ++i) {
		if(strcmp(dataTypes[i], val) == 0)
			return 1;
	}
	return 0;
}

int hasSemicolon(char *val) {
	return  val[strlen(val) - 1] == ';' ? 1 : 0;
}