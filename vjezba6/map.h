#ifndef MAP_H_INCLUDED

#define MAP_H_INCLUDED
#include "list.h"

typedef char* map_key_t;
typedef list_t map_value_t; //za trecu f-ju - autori_i_knjige_popis
//typedef unsigned map_value_t; // za drugu fu-ju - autori_i_knjige
typedef struct map_element_tag {
	map_key_t key;
	map_value_t value;
} map_element_t;
typedef struct map_tag *map_t;
typedef struct map_iterator_tag *map_iterator_t;

map_t map_new();									/* stvara novu (praznu) mapu, elementi se usporedjuju sa <, >, ==, hash se racuna sa % */
map_t map_new_advanced(int (*compare)(const map_key_t, const map_key_t), size_t (*hash)(const map_key_t)); /* stvara novu (praznu) mapu, elementi se usporedjuju funkcijom compare, a hash racuna funkcijom hash */
void map_delete(map_t map);							/* unistava mapu */
int map_is_empty(map_t map);							/* vraca 1 ako je mapa prazna, a 0 inace */
int map_size(map_t map);								/* vraca broj elemenata u mapi */
map_value_t map_get(map_t map, map_key_t key);		/* vraca vrijednost asociranu s kljucem key */
void map_put(map_t map, map_key_t key, map_value_t value);	/* ubacuje element sa kljucem key i vrijednoscu value */
void map_put_element(map_t map, map_element_t elem);	/* ubacuje element sa kljucem elem.key i vrijednoscu elem.value */
void map_remove(map_t map, map_key_t key);			/* uklanja element sa kljucem key */
int map_has_key(map_t map, map_key_t key);			/* vraca 1 ukoliko u mapi postoji element s kljucem key, a 0 inace */
map_iterator_t map_iterator(map_t map);				/* vraca prvu poziciju u mapi */

map_element_t map_iget(map_iterator_t iter);			/* vraca element na danoj poziciji u mapi */
void map_iput(map_iterator_t iter, map_value_t value);	/* zamjenjuje vrijednost na danoj poziciji u mapi novom vrijednoscu */
void map_iremove(map_iterator_t iter);				/* uklanja element sa dane pozicije u mapi */
void map_iterator_next(map_iterator_t iter);			/* postavlja iterator na sljedecu poziciju u mapi */
int map_iterator_is_valid(map_iterator_t iter);		/* vraca 1 ukoliko iterator pokazuje na ispravnu poziciju u mapi, a 0 inace */
int map_iterator_is_equal(map_iterator_t iter1, map_iterator_t iter2);	/* vraca 1 ukoliko oba iteratora pokazuju na istu poziciju u mapi, a 0 inace */
void map_iterator_set(map_iterator_t iter1, map_iterator_t iter2);		/* postavlja iterator iter1 na istu poziciju kao i iter2 */
void map_iterator_delete(map_iterator_t iter);		/* unistava iterator */

void map_debug_print_stats(map_t map);				/* ispisuje interne statistike konkretne implementacije */

#endif /* MAP_H_INCLUDED */
