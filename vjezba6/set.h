#ifndef SET_H_INCLUDED

#define SET_H_INCLUDED

typedef char* set_element_t;
typedef struct set_tag *set_t;
typedef struct set_iterator_tag *set_iterator_t;

set_t set_new();									/* stvara novi (prazni) skup, elementi se usporedjuju sa <, >, ==, hash se racuna sa % */
set_t set_new_advanced(int (*compare)(const set_element_t, const set_element_t), size_t (*hash)(const set_element_t)); /* stvara novi (prazni) skup, elementi se usporedjuju funkcijom compare, a hash racuna funkcijom hash */
void set_delete(set_t set);						/* unistava skup */
int set_is_empty(set_t set);						/* vraca 1 ako je skup prazan, a 0 inace */
int set_size(set_t set);							/* vraca broj elemenata u skupu */
void set_add(set_t set, set_element_t elem);		/* ubacuje element u skup */
void set_remove(set_t set, set_element_t elem);	/* uklanja element iz skupa */
int set_is_member(set_t set, set_element_t elem);/* vraca 1 ako skup sadrzi dani element, a 0 inace */
int set_is_subset(set_t set1, set_t set2);		/* vraca 1 ako je skup set1 podskup skupa set2, a 0 inace */
set_t set_union(set_t set1, set_t set2);			/* vraca uniju skupova set1 i set2 */
set_t set_intersection(set_t set1, set_t set2);	/* vraca presjek skupova set1 i set2 (elemente koji se nalaze i u prvom i u drugom setu) */
set_t set_difference(set_t set1, set_t set2);	/* vraca razliku skupova set1 i set2 (elemente koji se nalaze u prvom, ali ne i u drugom setu) */
set_iterator_t set_iterator(set_t set);			/* vraca iterator na prvi element skupa */

set_element_t set_iget(set_iterator_t iter);		/* vraca element na danoj poziciji u skupu */
void set_iremove(set_iterator_t iter);	/* uklanja zadani element iz skupa */
void set_iterator_next(set_iterator_t iter);		/* postavlja iterator na sljedecu poziciju u skupu */
int set_iterator_is_valid(set_iterator_t iter);	/* vraca 1 ukoliko iterator pokazuje na ispravnu poziciju u skupu, a 0 inace */
int set_iterator_is_equal(set_iterator_t iter1, set_iterator_t iter2);	/* vraca 1 ukoliko oba iteratora pokazuju na istu poziciju u skupu, a 0 inace */
void set_iterator_set(set_iterator_t iter1, set_iterator_t iter2);		/* postavlja iterator iter1 na istu poziciju kao i iter2 */
void set_iterator_delete(set_iterator_t iter);	/* unistava iterator */

void set_debug_print_stats(set_t set);			/* ispisuje interne statistike konkretne implementacije */

#endif /* SET_H_INCLUDED */
