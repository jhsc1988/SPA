#include <stdio.h>
#include <stdlib.h>

int cmpfunc(const void * a, const void * b) {
	return (*(int*)a - *(int*)b); //type cast jer je void pointer
}

void bsearch_(int *broj_koji_trazim, const int *razlika, int *brojac, const int *items, int *lista_brojeva) {

	qsort(lista_brojeva, *items, sizeof(int), cmpfunc);

	for (int i = 0; i < *items; i++) {
		*broj_koji_trazim = lista_brojeva[i] + *razlika;
		if (bsearch(broj_koji_trazim, lista_brojeva, *items, sizeof(int), cmpfunc) > 0)
			++*brojac;
	}
}

void sort_search(int *broj_koji_trazim, const int *razlika, int *brojac, const int *items, int *lista_brojeva) {

	//bubble sort
	int swap = 0;
	for (int i = 0; i < *items; i++) {
		for (int j = i; j < *items; j++)
			if (lista_brojeva[j] < lista_brojeva[i]) {
				swap = lista_brojeva[i];
				lista_brojeva[i] = lista_brojeva[j];
				lista_brojeva[j] = swap;
			}
	}
	
	//for (int i = 0; i < *items; i++)
	//	printf("%d ", lista_brojeva[i]);
	//putchar('\n');
	
	//search
	for (int i = 0; i < *items; i++) {
		*broj_koji_trazim = lista_brojeva[i] + *razlika;
			for (int j = i + 1; j < *items; j++)
				if (lista_brojeva[j] == *broj_koji_trazim)
					++*brojac;
	}
}

int main() {

	int items = 0;
	int razlika = 0;
	int brojac = 0;
	int broj_koji_trazim = 0;

	scanf_s("%d %d", &items, &razlika);

	int *lista_brojeva = malloc(items * sizeof(int));

	for (int i = 0; i < items; i++)
		scanf_s("%d", &lista_brojeva[i]);

	//void(*p)(int *, int *, int *, int *, int *) = bsearch_;
	void(*p)(int *, int *, int *, int *, int *) = sort_search;

	p(&broj_koji_trazim, &razlika, &brojac, &items, lista_brojeva);
	
	free(lista_brojeva);
	printf("%d", brojac);

	getchar();
	getchar();
}
