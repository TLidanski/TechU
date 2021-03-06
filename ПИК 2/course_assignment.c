#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Movie {
	long long id;
	char movieTitle[50];
	char movieDirector[50];
	double movieDuration;
	int releaseYear;

	struct Movie *nextMovie;
} Movie;

bool isEmpty(Movie **listHead);
void createMovie();
Movie* getListHead();
void deleteMovie();
void switchValues(Movie **movie, Movie **nextMovie);
Movie* sortListYearDesc();
void printList(int val);
void getLongestMovie();
void freeList(Movie **listHead);
void displayMenu();

int main() {
	displayMenu();

	return 0;
}

bool isEmpty(Movie **listHead) {
	return *listHead == NULL;
}

void createMovie() {
	FILE *fp;
	Movie *newElement = (Movie*)malloc(sizeof(Movie));

	printf("Enter movie id\n");
	scanf("%d", &newElement->id);

	printf("Enter movie title\n");
	scanf("%s", newElement->movieTitle);

	printf("Enter movie director\n");
	scanf("%s", newElement->movieDirector);

	printf("Enter the movie duration\n");
	scanf("%lf", &newElement->movieDuration);

	printf("Enter the release year\n");
	scanf("%d", &newElement->releaseYear);

	if((fp = fopen("movie_database.bin", "ab")) == NULL) {
		printf("Error opening file\n");
		return;
	}
	fwrite(newElement, sizeof(Movie), 1, fp);
	fclose(fp);
}

Movie* getListHead() {
	FILE *fp;
	Movie *movie = (Movie*)malloc(sizeof(Movie));
	Movie *listHead = NULL; Movie *prevMovie = NULL;

	if((fp = fopen("movie_database.bin", "rb")) == NULL) {
		printf("Error opening file, could be non existant\n");
		return NULL;
	}

	while(fread(movie, sizeof(Movie), 1, fp) == 1) {
		if(prevMovie == NULL)
			listHead = movie;

		movie->nextMovie = (Movie*)malloc(sizeof(Movie));
		prevMovie = movie;
		
		movie = movie->nextMovie;
	}
	fclose(fp);

	if(prevMovie != NULL) {
		free(prevMovie->nextMovie);
		prevMovie->nextMovie = NULL;
	}

	return listHead;
}

void deleteMovie() {
	Movie *listHead = getListHead();
	Movie *currPtr; Movie *prevPtr = NULL;
	char director[50]; FILE *fp;

	if(isEmpty(&listHead))
		return;

	if((fp = fopen("movie_database.bin", "wb")) == NULL) {
		printf("Error opening file\n");
		return;
	}

	printf("Enter movie director\n");
	scanf("%s", director);

	for (currPtr = listHead; currPtr != NULL; prevPtr = currPtr, currPtr = currPtr->nextMovie)	{
		if(strcmp(currPtr->movieDirector, director) == 0) {

			if(prevPtr == NULL) {
				listHead = currPtr->nextMovie;
			} else {
				prevPtr->nextMovie = currPtr->nextMovie;
			}

			free(currPtr);
		} else {
			fwrite(currPtr, sizeof(Movie), 1, fp);
		}
	}

	fclose(fp);
	// freeList(&listHead);
}

void switchValues(Movie **movie, Movie **nextMovie) {
	long long tempId;
	char tempMovieTitle[50]; char tempMovieDirector[50];
	double tempMovieDuration; int tempReleaseYear;

	tempId = (*movie)->id;
	strcpy(tempMovieTitle, (*movie)->movieTitle);
	strcpy(tempMovieDirector, (*movie)->movieDirector);
	tempMovieDuration = (*movie)->movieDuration;
	tempReleaseYear = (*movie)->releaseYear;

	(*movie)->id = (*nextMovie)->id;
	strcpy((*movie)->movieTitle, (*nextMovie)->movieTitle);
	strcpy((*movie)->movieDirector, (*nextMovie)->movieDirector);
	(*movie)->movieDuration = (*nextMovie)->movieDuration;
	(*movie)->releaseYear = (*nextMovie)->releaseYear;

	(*nextMovie)->id = tempId;
	strcpy((*nextMovie)->movieTitle, tempMovieTitle);
	strcpy((*nextMovie)->movieDirector, tempMovieDirector);
	(*nextMovie)->movieDuration = tempMovieDuration;
	(*nextMovie)->releaseYear = tempReleaseYear;
}

Movie* sortListYearDesc() {
	Movie *listHead = getListHead();
	Movie *currPtr; Movie *nextPtr = NULL;

	if(isEmpty(&listHead))
		return NULL;

	for (currPtr = listHead; currPtr->nextMovie != NULL; currPtr = currPtr->nextMovie) {

		for (nextPtr = currPtr->nextMovie; nextPtr != NULL; nextPtr = nextPtr->nextMovie) {

			if(currPtr->releaseYear < nextPtr->releaseYear)
				switchValues(&currPtr, &nextPtr);
		}
	}

	return listHead;
}

void printList(int val) {
	Movie *listHead = (val == 3) ? sortListYearDesc() : getListHead();
	Movie *movie = listHead;

	if(isEmpty(&movie))
		return; 
	
	while(movie != NULL) {
		printf("[\n");
		printf("ID - %lli\nTitle - %s\nDirector - %s\nDuration - %.2lf\nYear - %d\n", movie->id, movie->movieTitle, movie->movieDirector, movie->movieDuration, movie->releaseYear);
		printf("]\n");

		movie = movie->nextMovie;
	}		
	printf("\n\n\n\n");
	freeList(&listHead);
}

void getLongestMovie() {
	Movie *listHead = getListHead();
	Movie *moviePtr = listHead;
	Movie *longestMovie;
	double duration = 0;

	if(isEmpty(&moviePtr))
		return;

	while(moviePtr != NULL) {
		if(moviePtr->movieDuration > duration) {
			duration = moviePtr->movieDuration;
			longestMovie = moviePtr;
		}
		moviePtr = moviePtr->nextMovie;
	}
	printf("Longest Movie:\nID - %lli\nTitle - %s\nDirector - %s\nDuration - %.2lf\nYear - %d\n\n", 
			longestMovie->id, longestMovie->movieTitle, longestMovie->movieDirector, longestMovie->movieDuration, longestMovie->releaseYear);

	freeList(&listHead);
}

void freeList(Movie **listHead) {
	if(isEmpty(&(*listHead)))
		return;

	while(*listHead != NULL) {
		free(*listHead);
		*listHead = (*listHead)->nextMovie;
	}
}

void displayMenu() {
	printf("Select:\n1 - Add a Movie\n2 - Delete a director's movies\n3 - Print all movies, year - desc\n4 - Get movie with longest duration\n\n5 - Print the original list\n6 - Exit\n");

	int select;
	scanf("%d", &select);

	switch(select) {
		case 1:
			createMovie();
			displayMenu();
		break;
		case 2:
			deleteMovie();
			displayMenu();
		break;
		case 3:
			printList(select);
			displayMenu();
		break;
		case 4:
			getLongestMovie();
			displayMenu();
		break;
		case 5:
			printList(select);
			displayMenu();
		break;
		case 6:
		break;

		default: 
			printf("Invalid value\n");
	}
}
