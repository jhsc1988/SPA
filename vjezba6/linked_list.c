/* Implementacija sucelja ATP liste dvostruko povezanom listom. */

#include <stdlib.h>
#include "list.h"

struct node {
	list_element_t value;
	struct node *next;
	struct node *previous;
};

struct list_tag {
	struct node *head;
	struct node *tail;
	int size;
};

struct list_iterator_tag {
	list_t list;
	struct node *current;
};

static struct node *list_add_internal(list_t list, struct node *pos, list_element_t elem);

/* public: ATP interface */

/* O(1) */
list_t list_new() {
	list_t list = malloc(sizeof(struct list_tag));
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return list;
}

/* O(n) */
void list_delete(list_t list) {
	while (list->head != NULL) {
		struct node *temp = list->head;
		list->head = list->head->next;
		free(temp);
	}
	free(list);
}

/* O(1) */
int list_is_empty(list_t list) {
	return list->size == 0;
}

/* O(1) */
int list_size(list_t list) {
	return list->size;
}

/* O(1) */
void list_add(list_t list, list_element_t elem) {
	list_add_internal(list, NULL, elem);
}

/* O(1) */
list_iterator_t list_iterator(list_t list) {
	list_iterator_t iter = malloc(sizeof(struct list_iterator_tag));
	iter->list = list;
	iter->current = list->head;
	return iter;
}

/* O(1) */
list_iterator_t list_reverse_iterator(list_t list) {
	list_iterator_t iter = malloc(sizeof(struct list_iterator_tag));
	iter->list = list;
	iter->current = list->tail;
	return iter;
}

/* O(1) */
list_element_t list_get(list_iterator_t iter) {
	return iter->current->value;
}

/* O(1) */
void list_insert(list_iterator_t iter, list_element_t elem) {
	iter->current = list_add_internal(iter->list, iter->current, elem);
}

/* O(1) */
void list_replace(list_iterator_t iter, list_element_t elem) {
	iter->current->value = elem;
}

/* O(1) */
void list_remove(list_iterator_t iter) {
	struct node *temp;
	if (iter->current == iter->list->head) {
		iter->list->head = iter->current->next;
		if (iter->current->next != NULL)
			iter->current->next->previous = NULL;
	} else
		iter->current->previous->next = iter->current->next;
	if (iter->current == iter->list->tail) {
		iter->list->tail = iter->current->previous;
		if (iter->current->previous != NULL)
			iter->current->previous->next = NULL;
	} else
		iter->current->next->previous = iter->current->previous;
	temp = iter->current;
	list_iterator_next(iter);
	free(temp);
	iter->list->size--;
}

/* O(1) */
void list_iterator_next(list_iterator_t iter) {
	iter->current = iter->current->next;
}

/* O(1) */
void list_iterator_previous(list_iterator_t iter) {
	iter->current = iter->current->previous;
}

/* O(n) */
void list_iterator_seek(list_iterator_t iter, int n) {
	iter->current = iter->list->head;
	while (--n >= 0)
		list_iterator_next(iter);
}

/* O(1) */
void list_iterator_set(list_iterator_t iter1, list_iterator_t iter2) {
	iter1->current = iter2->current;
}

/* O(1) */
int list_iterator_is_valid(list_iterator_t iter) {
	return iter->current != NULL;
}

/* O(1) */
int list_iterator_is_equal(list_iterator_t iter1, list_iterator_t iter2) {
	return iter1->current == iter2->current;
}

/* O(1) */
void list_iterator_delete(list_iterator_t iter) {
	free(iter);
}

/* private: internals */

/* O(1) */
static struct node *list_add_internal(list_t list, struct node *pos, list_element_t elem) {
	struct node *node = malloc(sizeof(struct node));
	node->value = elem;
	if (pos == NULL) {
		node->previous = list->tail;
		node->next = NULL;
		if (list->tail == NULL)
			/* list was empty */
			list->head = node;
		else
			list->tail->next = node;
		list->tail = node;
	} else {
		node->previous = pos->previous;
		node->next = pos;
		if (pos->previous == NULL)
			list->head = node;
		else
			pos->previous->next = node;
		pos->previous = node;
	}
	++list->size;
	return node;
}
