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

	// visited array
	int visited[red][stupac] = {0}; visited[0][0] = 1;
	
	// za spremanje x, y i udaljenost
	struct point p; 
	
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
		p = *current;

		if (p.x == stupac - 1 && p.y == red - 1)
			return p.udaljenost;

		// optimizacija za if
		step_down = p.y + 1;
		step_right = p.x + 1;
		step_left = p.x - 1;
		step_up = p.y - 1;
		step = p.udaljenost + 1;

		// korak dolje - gledam tlocrt, ako je tlocrt 0 i visited 0 position stavljam u queue
		if (step_down < red && tlocrt[step_down][p.x] == 0 && visited[step_down][p.x] == 0) {

			++position_index;
			position[position_index].x = p.x;
			position[position_index].y = step_down;
			position[position_index].udaljenost = step;
			visited[position[position_index].y][position[position_index].x] = 1;
			queue_enqueue(path, &position[position_index]);
		}
		
		// korak desno 
		if (step_right < stupac && tlocrt[p.y][step_right] == 0 && visited[p.y][step_right] == 0) {

			++position_index;
			position[position_index].x = step_right;
			position[position_index].y = p.y;
			position[position_index].udaljenost = step;
			visited[position[position_index].y][position[position_index].x] = 1;
			queue_enqueue(path, &position[position_index]);
		}

		// korak lijevo
		if (step_left >= 0 && tlocrt[p.y][step_left] == 0 && visited[p.y][step_left] == 0) {

			++position_index;
			position[position_index].x = step_left;
			position[position_index].y = p.y;
			position[position_index].udaljenost = step;
			visited[position[position_index].y][position[position_index].x] = 1;
			queue_enqueue(path, &position[position_index]);
		}

		// korak gore
		if (step_up >= 0 && tlocrt[step_up][p.x] == 0 && visited[step_up][p.x] == 0) {

			++position_index;
			position[position_index].x = p.x;
			position[position_index].y = step_up;
			position[position_index].udaljenost = step;
			visited[position[position_index].y][position[position_index].x] = 1;
			queue_enqueue(path, &position[position_index]);
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
