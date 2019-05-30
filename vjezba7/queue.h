#ifndef QUEUE_H_INCLUDED

#define QUEUE_H_INCLUDED

typedef struct point* queue_element_t;
typedef struct queue_tag *queue_t;

queue_t queue_new();									/* stvara novi (prazni) red */
void queue_delete(queue_t queue);						/* unistava red */
void queue_enqueue(queue_t queue, queue_element_t elem);	/* ubacuje element na kraj reda */
queue_element_t queue_dequeue(queue_t queue);			/* uklanja element s pocetka reda */
queue_element_t queue_front(queue_t queue);				/* vraca element na pocetku reda */
int queue_is_empty(queue_t queue);						/* vraca 1 ako je red prazan, a 0 inace */
int queue_size(queue_t queue);							/* vraca broj elemenata u redu */

#endif /* QUEUE_H_INCLUDED */
