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

	free(prevMovie->nextMovie);
	prevMovie->nextMovie = NULL;

	return listHead;
}

void deleteMovie() {
	Movie *listHead = getListHead();
	Movie *currPtr = listHead; Movie *prevPtr = NULL;
	char director[50]; FILE *fp;

	if(isEmpty(&listHead))
		return;

	if((fp = fopen("movie_database.bin", "wb")) == NULL) {
		printf("Error opening file\n");
		return;
	}

	printf("Enter movie director\n");
	scanf("%s", director);

	while(currPtr != NULL) {
		if(strcmp(currPtr->movieDirector, director) == 0) {

			if(currPtr == listHead) {
				listHead = listHead->nextMovie;
				free(currPtr);
				currPtr = listHead;
			} else {
				prevPtr->nextMovie = currPtr->nextMovie;
				free(currPtr);
			}

		} else {
			fwrite(currPtr, sizeof(Movie), 1, fp);
			prevPtr = currPtr;
			currPtr = currPtr->nextMovie;
		}
	}
	fclose(fp);
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
	currPtr = listHead;

	return currPtr;
}

void printList(int val) {
	Movie *movie = (val == 3) ? sortListYearDesc() : getListHead();

	while(movie != NULL) {
		printf("[\n");
		printf("ID - %lli\nTitle - %s\nDirector - %s\nDuration - %lf\nYear - %d\n", movie->id, movie->movieTitle, movie->movieDirector, movie->movieDuration, movie->releaseYear);
		printf("]\n");
		movie = movie->nextMovie;
	}
	printf("\n\n\n\n");
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

int main() {
	displayMenu();

	return 0;
}
