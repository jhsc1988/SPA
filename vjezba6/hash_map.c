/* Implementacija sucelja ATP mape hash tablicom. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"


#define INITIAL_CAPACITY		16
#define LOAD_FACTOR			0.75

struct node {
	map_element_t value;
	struct node *next;
};

struct map_tag {
	struct node **hashtable;
	int size;
	int capacity;
	int (*compare)(const map_key_t, const map_key_t);
	size_t (*hash)(const map_key_t);
};

struct map_iterator_tag {
	map_t map;
	int index;
	struct node *node;
};

static int compare_simple(const map_key_t key1, const map_key_t key2);
static size_t hash_simple(map_key_t key);
static void grow(map_t map);
static int add_to_hashtable(struct node **hashtable, int capacity, int (*compare)(const map_key_t, const map_key_t), size_t (*hash)(const map_key_t), map_element_t elem);
static void free_hashtable(struct node **hashtable, int capacity);

/* public: ATP interface */

map_t map_new() {
	return map_new_advanced(compare_simple, hash_simple);
}

map_t map_new_advanced(int (*compare)(const map_key_t, const map_key_t), size_t (*hash)(const map_key_t)) {
	map_t map = malloc(sizeof(struct map_tag));
	map->hashtable = calloc(INITIAL_CAPACITY, sizeof(struct node **));
	map->capacity = INITIAL_CAPACITY;
	map->size = 0;
	map->compare = compare;
	map->hash = hash;
	return map;
}

void map_delete(map_t map) {
	free_hashtable(map->hashtable, map->capacity);
	free(map);
}

int map_is_empty(map_t map) {
	return map->size == 0;
}

int map_size(map_t map) {
	return map->size;
}

map_value_t map_get(map_t map, map_key_t key) {
	struct node *node = map->hashtable[map->hash(key) % map->capacity];
	while (node)
		if (map->compare(node->value.key, key) == 0)
			break;
		else
			node = node->next;
	return node->value.value;
}

void map_put(map_t map, map_key_t key, map_value_t value) {
	map_element_t e;
	e.key = key;
	e.value = value;
	map_put_element(map, e);
}

void map_put_element(map_t map, map_element_t elem) {
	grow(map);
	map->size += add_to_hashtable(map->hashtable, map->capacity, map->compare, map->hash, elem);
}

void map_remove(map_t map, map_key_t key) {
	struct node **pnode, *temp_node;
	pnode = &map->hashtable[map->hash(key) % map->capacity];
	while (*pnode && map->compare((*pnode)->value.key, key))
		pnode = &(*pnode)->next;
	if (*pnode == NULL)
		return;	/* elem not found in set, bail out */
	temp_node = (*pnode)->next;
	free(*pnode);
	*pnode = temp_node;
	map->size--;
}

int map_has_key(map_t map, map_key_t key) {
	struct node *node = map->hashtable[map->hash(key) % map->capacity];
	while (node)
		if (map->compare(node->value.key, key) == 0)
			return 1;
		else
			node = node->next;
	return 0;
}

map_iterator_t map_iterator(map_t map) {
	map_iterator_t iter = malloc(sizeof(struct map_iterator_tag));
	iter->map = map;
	iter->index = -1;
	iter->node = NULL;
	map_iterator_next(iter);
	return iter;
}

map_element_t map_iget(map_iterator_t iter) {
	return iter->node->value;
}

void map_iput(map_iterator_t iter, map_value_t value) {
	iter->node->value.value = value;
}

void map_iremove(map_iterator_t iter) {
	map_element_t elem = iter->node->value;
	map_iterator_next(iter);
	map_remove(iter->map, elem.key);
}

void map_iterator_next(map_iterator_t iter) {
	do {
		if (iter->node == NULL) {
			iter->index++;
			if (iter->index < iter->map->capacity)
				iter->node = iter->map->hashtable[iter->index];
		} else {
			iter->node = iter->node->next;
		}
	} while (iter->index < iter->map->capacity && iter->node == NULL);
}

void map_iterator_set(map_iterator_t iter1, map_iterator_t iter2) {
	iter1->index = iter2->index;
	iter1->node = iter2->node;
}

int map_iterator_is_valid(map_iterator_t iter) {
	return iter->index < iter->map->capacity && iter->node;
}

int map_iterator_is_equal(map_iterator_t iter1, map_iterator_t iter2) {
	return iter1->node == iter2->node;
}

void map_iterator_delete(map_iterator_t iter) {
	free(iter);
}

void map_debug_print_stats(map_t map) {
	int i;
	printf("HASH MAP STATS\n");
	printf("--------------\n");
	printf("Size: %d\n", map_size(map));
	printf("Hashtable usage:\n");
	for (i = 0; i < map->capacity; ++i) {
		struct node *node = map->hashtable[i];
		int count = 0;
		while (node) {
			++count;
			node = node->next;
		}
		printf("[%d]: %d\n", i, count);
	}
}

/* private: internals */

static int compare_simple(const map_key_t key1, const map_key_t key2) {
	if (key1 > key2)
		return 1;
	else if (key1 < key2)
		return -1;
	else
		return 0;
}

static size_t hash_simple(map_key_t key) {
	return (size_t) key;
}

static void grow(map_t map) {

	int new_capacity;
	struct node **new_hashtable;
	map_iterator_t iter;

	if (map->size < map->capacity * LOAD_FACTOR)
		return;

	new_capacity = map->capacity * 2;
	new_hashtable = calloc(new_capacity, sizeof(struct node **));
	if (!new_hashtable)
		exit(-1);

	iter = map_iterator(map);
	while (map_iterator_is_valid(iter)) {
		add_to_hashtable(new_hashtable, new_capacity, map->compare, map->hash, map_iget(iter));
		map_iterator_next(iter);
	}
	map_iterator_delete(iter);

	free_hashtable(map->hashtable, map->capacity);

	map->hashtable = new_hashtable;
	map->capacity  = new_capacity;

}

/* returns 1 if new element was inserted, 0 if element existed */
static int add_to_hashtable(struct node **hashtable, int capacity, int (*compare)(const map_key_t, const map_key_t), size_t (*hash)(const map_key_t), map_element_t elem) {
	struct node **pnode = &hashtable[hash(elem.key) % capacity];
	while (*pnode)
		if (compare((*pnode)->value.key, elem.key) == 0) {
			(*pnode)->value.value = elem.value;
			return 0;	/* already contained in this set, bail out */
		} else {
			pnode = &(*pnode)->next;
		}
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

