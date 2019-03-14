#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//random f-ja -> punim niz vrhova
unsigned int * random(unsigned int *vrhovi, int n) {

	for (int i = 0; i < n; i++) {
		//rand() % (max - min + 1) + min;
		vrhovi[i] = (int)(rand() % (1000 - 1 + 1) + 1);
		printf("%d ", vrhovi[i]);
	}

	return vrhovi;
}

//O(log(n))
unsigned int binarna_pretraga(unsigned int vrhovi[], int min, int max) {

	int key = (int)(min + max) / 2;

	while (min <= max) {

		if (vrhovi[key - 1] < vrhovi[key] && vrhovi[key + 1] < vrhovi[key])
			return vrhovi[key];
		else if (vrhovi[key - 1] > vrhovi[key])
			return binarna_pretraga(vrhovi, min, key - 1);
		else
			return binarna_pretraga(vrhovi, key + 1, max);
	}
	return 0;
}


int main() {

	srand((int)time(0));
	
	int n = 0;

	do {

		scanf_s("%d", &n);

		if (2 < n && n < 10000)
			break;
		else
			printf("mora biti 1 < N < 10000\n");
	} while (1);

	unsigned int *vrhovi = (unsigned int *)malloc(n * sizeof(unsigned int));
	
	printf("%d", binarna_pretraga(random(vrhovi, n), 0, n - 1));
	getchar();
	getchar();

	free(vrhovi);
	return 0;
}
