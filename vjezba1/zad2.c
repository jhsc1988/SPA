#include <stdio.h>
#include <stdlib.h>

//void * pointer moze biti bilo sto, ne moze biti dereferencirano
//za dereferenciranje mora se castati sa (int*) 

int cmpfunc(const void * a, const void * b) {
	return (*(int*)a - *(int*)b); //type cast jer je void pointer
}

void pomocu_bsearch(int *broj, int *razlika, int *brojac, int *broj_brojeva_u_listi,int *lista_brojeva) {
	qsort(lista_brojeva, *broj_brojeva_u_listi, sizeof(int), cmpfunc);

	// 5 2
	// 1 2 3 5 7
	// razlika = 2
	// trazimo razliku + lista_brojeva[i] u cijeloj listi brojeva

	for (int i = 0; i < *broj_brojeva_u_listi; i++) {
		*broj = lista_brojeva[i] + *razlika;
		if (bsearch(broj, lista_brojeva, *broj_brojeva_u_listi, sizeof(int), cmpfunc) > 0)
			++*brojac;
	}

}

void moj_search_sort(int *broj, int *razlika, int *brojac, int *broj_brojeva_u_listi, int *lista_brojeva) {

	//bubble sort
	int swap = 0;
	for (int i = 0; i < *broj_brojeva_u_listi; i++) {
		for (int j = i; j < *broj_brojeva_u_listi; j++)
			if (lista_brojeva[j] < lista_brojeva[i]) {
				swap = lista_brojeva[i];
				lista_brojeva[i] = lista_brojeva[j];
				lista_brojeva[j] = swap;
			}
	}
	
	//for (int i = 0; i < *broj_brojeva_u_listi; i++)
	//	printf("%d ", lista_brojeva[i]);
	//putchar('\n');
	
	//search
	for (int i = 0; i < *broj_brojeva_u_listi; i++) {
		*broj = lista_brojeva[i] + *razlika;
			for (int j = 1; j < *broj_brojeva_u_listi; j++)
				if (lista_brojeva[j] == *broj)
					++*brojac;
	}

}


int main() {

	int broj_brojeva_u_listi = 0;
	int razlika = 0;
	int brojac = 0;
	int broj = 0;

	scanf_s("%d %d", &broj_brojeva_u_listi, &razlika);

	int *lista_brojeva = malloc(broj_brojeva_u_listi * sizeof(int));

	for (int i = 0; i < broj_brojeva_u_listi; i++)
		scanf_s("%d", &lista_brojeva[i]);

	//pomocu_bsearch(&broj, &razlika, &brojac, &broj_brojeva_u_listi, lista_brojeva);

	moj_search_sort(&broj, &razlika, &brojac, &broj_brojeva_u_listi, lista_brojeva);
	
	free(lista_brojeva);
	printf("%d", brojac);
	getchar();
	getchar();

}