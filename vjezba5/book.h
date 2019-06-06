#ifndef BOOK_H_INCLUDED

#define BOOK_H_INCLUDED

#define BOOK_NAME_MAX_LEN 80
#define BOOK_AUTHOR_MAX_LEN	80

struct book {
	unsigned id;
	char name[BOOK_NAME_MAX_LEN + 1];
	char author[BOOK_AUTHOR_MAX_LEN + 1];
	unsigned price;
};

/* ispis knjige */
void print_book(struct book* _book);

/* ucitavanje knjiga iz datoteke */
int load_books(const char *file_name, struct book **books, unsigned *num_books);

#endif /* BOOK_H_INCLUDED */

