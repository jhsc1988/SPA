#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "list_queue.c"

#define red 5
#define stupac 5

struct point {
	int x;
	int y;
	int udaljenost;
};

int shortest_path(int tlocrt[red][stupac]){
	
	// niz za sve cvorove
	struct point position[red * stupac] = {0};
	
	// index za position array ^
	int position_index = 0;

	// current position iz queue iz kojeg trazim slijedeci cvor
	queue_element_t current = position;

	queue_t path = queue_new();
	queue_enqueue(path, position);

	int step_down = 0,
		step_right = 0,
		step_left = 0,
		step_up = 0,
		step = 0;

	while (!queue_is_empty(path)) {

		current = queue_dequeue(path);

		if (current->x == stupac - 1 && current->y == red - 1)
			return current->udaljenost;

		step_down = current->y + 1;
		step_right = current->x + 1;
		step_left = current->x - 1;
		step_up = current->y - 1;
		step = current->udaljenost + 1;

		// korak dolje - gledam tlocrt, ako je tlocrt 0 position stavljam u queue
		if (step_down < red && tlocrt[step_down][current->x] == 0) {

			++position_index;

			position[position_index].x = current->x;
			position[position_index].y = step_down; // pomak pozicije dolje
			position[position_index].udaljenost = step;

			tlocrt[position[position_index].y][position[position_index].x] = 1; // oznacavam mjesto na kojem sam bio
			queue_enqueue(path, &position[position_index]); // dodajem tu poziciju u queue
		}
		
		// korak desno 
		if (step_right < stupac && tlocrt[current->y][step_right] == 0) {

			++position_index;

			position[position_index].x = step_right; // pomak pozicije desno
			position[position_index].y = current->y;
			position[position_index].udaljenost = step;

			tlocrt[position[position_index].y][position[position_index].x] = 1; // oznacavam mjesto na kojem sam bio

			queue_enqueue(path, &position[position_index]); // dodajem tu poziciju u queue
		}

		// korak lijevo
		if (step_left >= 0 && tlocrt[current->y][step_left] == 0) {

			++position_index;

			position[position_index].x = step_left; // pomak pozicije u lijevo
			position[position_index].y = current->y;
			position[position_index].udaljenost = step;

			tlocrt[position[position_index].y][position[position_index].x] = 1; // oznacavam mjesto na kojem sam bio

			queue_enqueue(path, &position[position_index]); // dodajem tu poziciju u queue
		}

		// korak gore
		if (step_up >= 0 && tlocrt[step_up][current->x] == 0) {

			++position_index;

			position[position_index].x = current->x;
			position[position_index].y = step_up; // pomak pozicije gore
			position[position_index].udaljenost = step;

			tlocrt[position[position_index].y][position[position_index].x] = 1; // oznacavam mjesto na kojem sam bio

			queue_enqueue(path, &position[position_index]); // dodajem tu poziciju u queue
		}
	}
	queue_delete(path);
	return -1;
}

int main() {

	// tlocrt hardcoded
	int tlocrt[red][stupac] = {
						{0,1,0,0,1},
						{0,1,0,1,0},
						{0,1,0,0,0},
						{0,0,0,0,1},
						{1,0,1,0,0} };

	printf_s("%d",shortest_path(tlocrt));
}
