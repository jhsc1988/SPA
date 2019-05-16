/* Implementacija sucelja ATP skupa hash tablicom. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

#define INITIAL_CAPACITY		16
#define LOAD_FACTOR			0.75

struct node {
	set_element_t value;
	struct node *next;
};

struct set_tag {
	struct node **hashtable;
	int size;
	int capacity;
	int (*compare)(const set_element_t, const set_element_t);
	size_t (*hash)(const set_element_t);
};

struct set_iterator_tag {
	set_t set;
	int index;
	struct node *node;
};

static int compare_simple(const set_element_t elem1, const set_element_t elem2);
static size_t hash_simple(set_element_t elem);
static void set_add_all(set_t set, set_t elements_set);
static void grow(set_t set);
static int add_to_hashtable(struct node **hashtable, int capacity, int (*compare)(const set_element_t, const set_element_t), size_t (*hash)(const set_element_t), set_element_t elem);
static void free_hashtable(struct node **hashtable, int capacity);

/* public: ATP interface */

/* O(1) */
set_t set_new() {
	return set_new_advanced(compare_simple, hash_simple);
}

/* O(1) */
set_t set_new_advanced(int (*compare)(const set_element_t, const set_element_t), size_t (*hash)(const set_element_t)) {
	set_t set = malloc(sizeof(struct set_tag));
	set->hashtable = calloc(INITIAL_CAPACITY, sizeof(struct node **));
	set->capacity = INITIAL_CAPACITY;
	set->size = 0;
	set->compare = compare;
	set->hash = hash;
	return set;
}

/* O(1) - O(n), ovisno o kvaliteti hash funkcije */
void set_delete(set_t set) {
	free_hashtable(set->hashtable, set->capacity);
	free(set);
}

/* O(1) */
int set_is_empty(set_t set) {
	return set->size == 0;
}

/* O(1) */
int set_size(set_t set) {
	return set->size;
}

/* O(1) - O(n), ovisno o kvaliteti hash funkcije */
void set_add(set_t set, set_element_t elem) {
	grow(set);
	set->size += add_to_hashtable(set->hashtable, set->capacity, set->compare, set->hash, elem);
}

/* O(1) - O(n), ovisno o kvaliteti hash funkcije */
void set_remove(set_t set, set_element_t elem) {
	struct node **pnode, *temp_node;
	pnode = &set->hashtable[set->hash(elem) % set->capacity];
	while (*pnode && set->compare((*pnode)->value, elem))
		pnode = &(*pnode)->next;
	if (*pnode == NULL)
		return;	/* elem not found in set, bail out */
	temp_node = (*pnode)->next;
	free(*pnode);
	*pnode = temp_node;
	set->size--;
}

/* O(1) */
set_element_t set_iget(set_iterator_t iter) {
	return iter->node->value;
}

/* O(1) - O(n), ovisno o kvaliteti hash funkcije */
void set_iremove(set_iterator_t iter) {
	set_element_t elem = iter->node->value;
	set_iterator_next(iter);
	set_remove(iter->set, elem);
}

/* O(1) - O(n), ovisno o kvaliteti hash funkcije */
int set_is_member(set_t set, set_element_t elem) {
	struct node *node = set->hashtable[set->hash(elem) % set->capacity];
	while (node)
		if (set->compare(node->value, elem) == 0)
			return 1;
		else
			node = node->next;
	return 0;
}

/* O(n) - O(n^2), ovisno o kvaliteti hash funkcije */
int set_is_subset(set_t set1, set_t set2) {
	set_iterator_t iter = set_iterator(set1);
	while (set_iterator_is_valid(iter)) {
		if (!set_is_member(set2, set_iget(iter)))
			return 0;
		else
			set_iterator_next(iter);
	}
	set_iterator_delete(iter);
	return 1;
}

/* O(n) - O(n^2), ovisno o kvaliteti hash funkcije */
set_t set_union(set_t set1, set_t set2) {
	set_t union_set = set_new();
	set_add_all(union_set, set1);
	set_add_all(union_set, set2);
	return union_set;
}

/* O(n) - O(n^2), ovisno o kvaliteti hash funkcije */
set_t set_intersection(set_t set1, set_t set2) {
	set_t intersection_set;
	set_iterator_t iter;
	intersection_set = set_new();
	iter = set_iterator(set1);
	while (set_iterator_is_valid(iter)) {
		set_element_t elem = set_iget(iter);
		if (set_is_member(set2, elem))
			set_add(intersection_set, elem);
		set_iterator_next(iter);
	}
	set_iterator_delete(iter);
	return intersection_set;
}

/* O(n) - O(n^2), ovisno o kvaliteti hash funkcije */
set_t set_difference(set_t set1, set_t set2) {
	set_t difference_set;
	set_iterator_t iter;
	difference_set = set_new();
	iter = set_iterator(set1);
	while (set_iterator_is_valid(iter)) {
		set_element_t elem = set_iget(iter);
		if (!set_is_member(set2, elem))
			set_add(difference_set, elem);
		set_iterator_next(iter);
	}
	set_iterator_delete(iter);
	return difference_set;
}

/* O(1) - O(n), ovisno o kvaliteti hash funkcije */
set_iterator_t set_iterator(set_t set) {
	set_iterator_t iter = malloc(sizeof(struct set_iterator_tag));
	iter->set = set;
	iter->index = -1;
	iter->node = NULL;
	set_iterator_next(iter);
	return iter;
}

/* O(1) */
void set_iterator_delete(set_iterator_t iter) {
	free(iter);
}

/* O(1) - O(n), ovisno o kvaliteti hash funkcije */
void set_iterator_next(set_iterator_t iter) {
	do {
		if (iter->node == NULL) {
			iter->index++;
			if (iter->index < iter->set->capacity)
				iter->node = iter->set->hashtable[iter->index];
		} else {
			iter->node = iter->node->next;
		}
	} while (iter->index < iter->set->capacity && iter->node == NULL);
}

/* O(1) */
void set_iterator_set(set_iterator_t iter1, set_iterator_t iter2) {
	iter1->index = iter2->index;
	iter1->node = iter2->node;
}

/* O(1) */
int set_iterator_is_valid(set_iterator_t iter) {
	return iter->index < iter->set->capacity && iter->node;
}

/* O(1) */
int set_iterator_is_equal(set_iterator_t iter1, set_iterator_t iter2) {
	return iter1->node == iter2->node;
}

void set_debug_print_stats(set_t set) {
	int i;
	printf("HASH SET STATS\n");
	printf("--------------\n");
	printf("Size: %d\n", set_size(set));
	printf("Hashtable usage:\n");
	for (i = 0; i < set->capacity; ++i) {
		struct node *node = set->hashtable[i];
		int count = 0;
		while (node) {
			++count;
			node = node->next;
		}
		printf("[%d]: %d\n", i, count);
	}
}

/* private: internals */

static int compare_simple(const set_element_t elem1, const set_element_t elem2) {
	if (elem1 > elem2)
		return 1;
	else if (elem1 < elem2)
		return -1;
	else
		return 0;
}

static size_t hash_simple(set_element_t elem) {
	return (size_t) elem;
}

static void set_add_all(set_t set, set_t elements_set) {
	set_iterator_t iter = set_iterator(elements_set);
	while (set_iterator_is_valid(iter)) {
		set_add(set, set_iget(iter));
		set_iterator_next(iter);
	}
	set_iterator_delete(iter);
}

static void grow(set_t set) {

	int new_capacity;
	struct node **new_hashtable;
	set_iterator_t iter;

	if (set->size < set->capacity * LOAD_FACTOR)
		return;

	new_capacity = set->capacity * 2;
	new_hashtable = calloc(new_capacity, sizeof(struct node **));
	if (!new_hashtable)
		exit(-1);

	iter = set_iterator(set);
	while (set_iterator_is_valid(iter)) {
		add_to_hashtable(new_hashtable, new_capacity, set->compare, set->hash, set_iget(iter));
		set_iterator_next(iter);
	}
	set_iterator_delete(iter);

	free_hashtable(set->hashtable, set->capacity);

	set->hashtable = new_hashtable;
	set->capacity  = new_capacity;

}

/* returns 1 if new element was inserted, 0 if element existed */
static int add_to_hashtable(struct node **hashtable, int capacity, int (*compare)(const set_element_t, const set_element_t), size_t (*hash)(const set_element_t), set_element_t elem) {
	struct node **pnode = &hashtable[hash(elem) % capacity];
	while (*pnode)
		if (compare((*pnode)->value, elem) == 0)
			return 0;	/* already contained in this set, bail out */
		else
			pnode = &(*pnode)->next;
	*pnode = malloc(sizeof(struct node));
	(*pnode)->value = elem;
	(*pnode)->next = NULL;
	return 1;
}

static void free_hashtable(struct node **hashtable, int capacity) {
	int i;
	for (i = 0; i < capacity; ++i) {
		struct node *node = hashtable[i];
		while (node) {
			struct node *temp = node;
			node = node->next;
			free(temp);
		}
	}
	free(hashtable);
}

