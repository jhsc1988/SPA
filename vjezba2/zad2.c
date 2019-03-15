#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//random f-ja -> punim niz vrhova
unsigned int * random(unsigned int *vrhovi, int n) {
	for (int i = 0; i < n; i++) {

		//rand() % (max - min + 1) + min;
		vrhovi[i] = (int)(rand() % 1000 + 1);
		printf("%d ", vrhovi[i]);
	}
	return vrhovi;
}

//O(log(n)) -> za ovaj problem binarna pretraga nije optimalno rjesenje
unsigned int binarna_pretraga(unsigned int vrhovi[], int low, int high) {
	int mid = (low + high) / 2;

	//sprjecava prekoracenje rubnih tocki
	if (!(low <= high))
		return -1; //rub

	if (vrhovi[mid] > vrhovi[mid + 1])
		if (vrhovi[mid] > vrhovi[mid - 1])
			return vrhovi[mid];
	if (vrhovi[mid + 1] < vrhovi[mid - 1])
		return binarna_pretraga(vrhovi, low, mid - 1);
	return binarna_pretraga(vrhovi, mid + 1, high);
}

int main() {
	srand((int)time(0));

	int n = 0;

	do {
		scanf_s("%d", &n);
		if (2 < n && n < 10000) break;
		else printf("mora biti 1 < N < 10000\n");
	} while (1);

	unsigned int *vrhovi = (unsigned int *)malloc(n * sizeof(unsigned int));
	do {
		printf("\n%d\n", binarna_pretraga(random(vrhovi, n), 0, n - 1));
		getchar();
	} while (1);

	getchar();
	getchar();

	free(vrhovi);
	return 0;
}
