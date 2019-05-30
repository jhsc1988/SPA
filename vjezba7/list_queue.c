/* Implementacija sucelja ATP reda dvostruko povezanom listom. */

#include <stdlib.h>
#include "queue.h"

struct node {

	queue_element_t value;
	struct node *next;
	struct node *previous;
};

struct queue_tag {
	struct node *head;
	struct node *tail;
	int size;
};

/* O(1) */
queue_t queue_new() {
	queue_t queue = malloc(sizeof(struct queue_tag));
	queue->size = 0;
	queue->head = NULL;
	queue->tail = NULL;
	return queue;
}

/* O(n) */
void queue_delete(queue_t queue) {
	while (queue->head != NULL) {
		struct node *temp = queue->head;
		queue->head = queue->head->next;
		free(temp);
	}
	free(queue);
}

/* O(1) */
void queue_enqueue(queue_t queue, queue_element_t elem) {
	struct node *node = malloc(sizeof(struct node));
	node->value = elem;
	node->next = NULL;
	node->previous = queue->tail;
	if (queue->tail != NULL)
		queue->tail->next = node;
	else
		queue->head = node;
	queue->tail = node;
	++queue->size;
}

/* O(1) */
queue_element_t queue_dequeue(queue_t queue) {
	queue_element_t elem;
	struct node *node;
	node = queue->head;
	elem = node->value;
	queue->head = node->next;
	if (queue->head != NULL)
		queue->head->previous = NULL;
	else
		queue->tail = NULL;
	free(node);
	--queue->size;
	return elem;
}

/* O(1) */
queue_element_t queue_front(queue_t queue) {
	return queue->head->value;
}

/* O(1) */
int queue_is_empty(queue_t queue) {
	return queue->head == NULL;
}

/* O(1) */
int queue_size(queue_t queue) {
	return queue->size;
}
