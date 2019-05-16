#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "set.h"
#include "book.h"
#include "map.h"
#include "djb2.h"
#include "list.h"

void ukupan_broj_autora(struct book *knjige, unsigned broj) {

	set_t autori = set_new_advanced(strcmp,djb2);
	
	for (unsigned i = 0; i < broj; i++) {

		// add_to_hashtable -> returns 1 if new element was inserted, 0 if element existed
		// ne treba mi set_is_member za uvjet
		set_add(autori, knjige[i].author);
	}
	
	printf("U datoteci se nalazi %d knjiga, a ukupan broj autora je %d\n",broj ,set_size(autori) );
	putchar('\n');
	set_delete(autori);
}

/*
void autori_i_knjige(struct book *knjige, unsigned broj) {

	map_t autori = map_new_advanced(strcmp, djb2);

	for (unsigned i = 0; i < broj; i++) {

		if (map_has_key(autori, knjige[i].author))
			map_put(autori, knjige[i].author, map_get(autori, knjige[i].author) + 1);
		else
			map_put(autori, knjige[i].author, 1);
	}

	map_iterator_t iter = map_iterator(autori);
	map_element_t element;

	while (map_iterator_is_valid(iter)) {

		element = map_iget(iter);
		printf("%s - %u\n", element.key, element.value);
		map_iterator_next(iter);
		
	}

	map_iterator_delete(iter);
	map_delete(autori);

}
*/

void autori_i_knjige_popis(struct book *knjige, unsigned broj) {
	
	map_t autori = map_new_advanced(strcmp, djb2);
	map_iterator_t map_iter = map_iterator(autori);
	map_element_t element;
	
	list_t list;
	list_iterator_t list_iter;

	for (unsigned i = 0; i < broj; i++) {

		if (map_has_key(autori, knjige[i].author))
			list = map_get(autori, knjige[i].author);
		
		else {		
			list = list_new();
			map_put(autori, knjige[i].author, list);
		}

		list_add(list, knjige[i].name);
	}

	for(map_iter = map_iterator(autori); map_iterator_is_valid(map_iter); map_iterator_next(map_iter)){

		element = map_iget(map_iter);
		printf("%s: ", element.key);

		list = element.value;
		list_iter = list_iterator(list);
		
		while (1) {

			printf("%s", list_get(list_iter));
			list_iterator_next(list_iter);

			if (list_iterator_is_valid(list_iter))
				printf("%s", " - ");
			else
				break;
		}

		putchar('\n');
		
		list_iterator_delete(list_iter);
		list_delete(list);	
	}

	map_iterator_delete(map_iter);
	map_delete(autori);

}


int main() {

	struct book *knjige_niz = NULL;
	unsigned broj_knjiga = 0;

	if (load_books("knjige.csv", &knjige_niz, &broj_knjiga))
		return -1;

	ukupan_broj_autora(knjige_niz, broj_knjiga);

	//autori_i_knjige(knjige_niz, broj_knjiga);

	autori_i_knjige_popis (knjige_niz, broj_knjiga);

	free(knjige_niz);

	return 0;

}
