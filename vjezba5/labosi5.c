#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book.h"
#include "trie.h"

struct node {

	struct book book;
	struct node* left;
	struct node* right;

};

void free_all(struct node* bst) {

	if (bst == NULL) return;
	free_all(bst->left);
	free_all(bst->right);
	free(bst);

}

void bst_insert_data(struct node** bst, struct book* books) {

	(*bst) = malloc(sizeof(struct node));

	if ((*bst)) {
		(*bst)->book.id = books->id;
		strcpy((*bst)->book.name, books->name);
		strcpy((*bst)->book.author, books->author);
		(*bst)->book.price = books->price;
		(*bst)->left = NULL;
		(*bst)->right = NULL;
	}
}

void bst_add(struct node** bst, struct book* books) {

	while (1) {

		if ((*bst)->book.id > books->id) bst = &(*bst)->left;		
		else if ((*bst)->book.id < books->id) bst = &(*bst)->right;
		else return;
		if ((*bst) == NULL)	bst_insert_data(bst, books);
	}
}

void inorder_print(struct node* root) {
	
	if (!root) return;
	
	inorder_print(root->left);
	printf("id: %d name: %s author: %s price: %d\n", root->book.id, root->book.name, root->book.author, root->book.price);
	inorder_print(root->right);
}

int main() {

	trie_t root;
	struct book* books;
	unsigned num_books;
	char book_name[BOOK_NAME_MAX_LEN + 1];
	unsigned i;

	/* ucitavanje knjiga iz datoteke */
	if (load_books("knjige.csv", &books, &num_books))
		return -1;

	/* korijen triea, pocetak svih rijeci, uvijek alociran */
	root = trie_new_node();

	/* ubacivanje knjiga u trie */
	for (i = 0; i < num_books; i++)
		trie_insert_word(root, books[i].name);

	// 2. zadatak

	// binary search tree
	struct node** bst;
	bst = malloc(num_books*sizeof(struct node*));

	// dodajem knjige u bst
	bst_insert_data(bst, books); // prva knjiga (root node)
	for (i = 1; i < num_books; i++) {
		bst_add(bst, &books[i]);
	}

	// printam inorder
	if (bst) inorder_print((*bst));

	// free_all 
	if (bst) free_all((*bst));
	
	// 2. zadatak END

	/* knjige su u trieu, ne trebaju nam vise kao zaseban niz */
	//free(books);

	/* pretrazivanje knjiga */
	while (1) {
		int search_result = 0;

		printf("\nUpisi ime knjige (prazan string za izlaz iz programa): ");
		gets(book_name);

		if (!strcmp(book_name, ""))
			break;

		search_result = trie_search_word(root, book_name);
		printf("'%s' %s ispravan naziv knjige.\n", book_name, search_result ? "je" : "nije");
		if (!search_result) {
			printf("Moguci kandidati su:\n");
			trie_print_prefixed_word(root, book_name);
		}
	}

	return 0;
}
