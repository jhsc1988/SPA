#include <stdio.h>
#include <stdlib.h>

int array_(int * arr, int st, int n) {
	
	if (st == n)
		return 0;

	printf("%d ", *(arr + st));

	return array_(arr, st + 1, n);

}

int main() {

	int time();
	srand(time(NULL));
	
	int n = 0;

	printf_s("velicina niza:");
	scanf_s("%d", &n);

	int *niz = malloc(n * sizeof(int));

	//rand() % (max - min + 1) + min;
	for (int i = 0; i < n; i++) {
		niz[i] = rand() % (100 - 1 + 1) + 1;
	}

	//rekurzivni ispis clanova niza
	array_(niz, 0, n);
	
	getchar();
	getchar();

}