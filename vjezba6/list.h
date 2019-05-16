#ifndef LIST_H_INCLUDED

#define LIST_H_INCLUDED

typedef char* list_element_t;
typedef struct list_tag *list_t;
typedef struct list_iterator_tag *list_iterator_t;

list_t list_new();										/* stvara novu (praznu) listu */
void list_delete(list_t list);							/* unistava listu */
int list_is_empty(list_t list);							/* vraca 1 ako je lista prazna, a 0 inace */
int list_size(list_t list);								/* vraca broj elemenata u listi */
void list_add(list_t list, list_element_t elem);			/* dodaje element na kraj liste */
list_iterator_t list_iterator(list_t list);				/* vraca prvu poziciju u listi */
list_iterator_t list_reverse_iterator(list_t list);		/* vraca zadnju poziciju u listi */

list_element_t list_get(list_iterator_t iter);			/* vraca element na danoj poziciji u listi */
void list_insert(list_iterator_t iter, list_element_t elem);	/* dodaje novi element na danu poziciju u listi */
void list_replace(list_iterator_t iter, list_element_t elem);/* zamjenjuje element na danoj poziciji u listi novom vrijednoscu */
void list_remove(list_iterator_t iter);					/* uklanja element sa dane pozicije u listi */
void list_iterator_next(list_iterator_t iter);			/* postavlja iterator na sljedecu poziciju u listi */
void list_iterator_previous(list_iterator_t iter);		/* postavlja iterator na prethodnu poziciju u listi */
void list_iterator_seek(list_iterator_t iter, int n);	/* postavlja iterator na n-tu poziciju u listi */
int list_iterator_is_valid(list_iterator_t iter);			/* vraca 1 ukoliko iterator pokazuje na ispravnu poziciju u listi, a 0 inace */
int list_iterator_is_equal(list_iterator_t iter1, list_iterator_t iter2);/* vraca 1 ukoliko oba iteratora pokazuju na istu poziciju u listi, a 0 inace */
void list_iterator_set(list_iterator_t iter1, list_iterator_t iter2);	/* postavlja iterator iter1 na istu poziciju kao i iter2 */
void list_iterator_delete(list_iterator_t iter);			/* unistava iterator */

#endif /* LIST_H_INCLUDED */
