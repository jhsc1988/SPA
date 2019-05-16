#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

#define MAX_LINE_SIZE 1024

void print_book(struct book* book) {

	if (book) {
		printf("id: %u, name: %s, author:%s, price:%u\n",
			book->id, book->name, book->author, book->price);
	}
}

int load_books(const char *file_name, struct book **books, unsigned *num_books) {

	FILE *file_stream;
	char line[MAX_LINE_SIZE];
	struct book *pbook;

	/* otvaranje datoteke */
	file_stream = fopen(file_name, "r");
	if (file_stream == NULL) {
		printf("Nije moguce otvoriti datoteku %s!\n", file_name);
		return -1;
	}

	/* brojanje knjiga, tj. redaka u datoteci */
	*num_books = 0;
	while (fgets(line, MAX_LINE_SIZE, file_stream))
		++*num_books;

	/* vracanje kursora na pocetak datoteke */
	if (fseek(file_stream, 0, SEEK_SET))
		return -2;

	/* alociranje memorije */
	if ((*books = malloc(*num_books * sizeof(struct book))) == NULL) {
		printf("Nije moguce alocirati memoriju za %u knjiga!\n", *num_books);
		return -3;
	}

	/* ucitavanje podataka */
	pbook = *books;
	while (fgets(line, MAX_LINE_SIZE, file_stream)) {
		pbook->id = (unsigned)atoi(strtok(line, ";"));
		strcpy(pbook->name, strtok(NULL, ";"));
		strcpy(pbook->author, strtok(NULL, ";"));
		pbook->price = (unsigned)atoi(strtok(NULL, ";"));
		++pbook;
	}

	/* zatvaranje datoteke */
	fclose(file_stream);

	return 0;
}
