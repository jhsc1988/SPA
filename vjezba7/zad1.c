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
	
	// array index za position array ^
	int array_index = 0;

	// current position iz queue iz kojeg trazim slijedeci cvor
	queue_element_t current = position;

	queue_t path = queue_new();
	queue_enqueue(path, position);

	while (!queue_is_empty(path)) {

		current = queue_dequeue(path);
		p = *current;

		if (p.x == stupac - 1 && p.y == red - 1)
			return p.udaljenost;

		// korak dolje - gledam tlocrt, ako je tlocrt 0 i visited 0 position stavljam u queue
		if (p.y + 1 < red && tlocrt[p.y + 1][p.x] == 0 && visited[p.y + 1][p.x] == 0) {

			++array_index;
			position[array_index].x = p.x;
			position[array_index].y = p.y + 1;
			position[array_index].udaljenost = p.udaljenost + 1;
			visited[position[array_index].y][position[array_index].x] = 1;
			queue_enqueue(path, &position[array_index]);
		}
		
		// korak desno 
		if (p.x + 1 < stupac && tlocrt[p.y][p.x + 1] == 0 && visited[p.y][p.x + 1] == 0) {

			++array_index;
			position[array_index].x = p.x + 1;
			position[array_index].y = p.y;
			position[array_index].udaljenost = p.udaljenost + 1;
			visited[position[array_index].y][position[array_index].x] = 1;
			queue_enqueue(path, &position[array_index]);
		}

		// korak lijevo
		if (p.x - 1 >= 0 && tlocrt[p.y][p.x - 1] == 0 && visited[p.y][p.x - 1] == 0) {

			++array_index;
			position[array_index].x = p.x - 1;
			position[array_index].y = p.y;
			position[array_index].udaljenost = p.udaljenost + 1;
			visited[position[array_index].y][position[array_index].x] = 1;
			queue_enqueue(path, &position[array_index]);
		}

		// korak gore
		if (p.y - 1 >= 0 && tlocrt[p.y - 1][p.x] == 0 && visited[p.y - 1][p.x] == 0) {

			++array_index;
			position[array_index].x = p.x;
			position[array_index].y = p.y - 1;
			position[array_index].udaljenost = p.udaljenost + 1;
			visited[position[array_index].y][position[array_index].x] = 1;
			queue_enqueue(path, &position[array_index]);
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
						{0,0,0,1,0},
						{1,0,1,0,0} };

	printf_s("%d",shortest_path(tlocrt));
}
