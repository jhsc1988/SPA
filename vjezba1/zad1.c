#include <stdio.h>
#include <stdlib.h>

void jedan_pointer(int * A, int * B, const int * n) {

	//memorija se puni slijedno -> alokacija pomocu jednog pointera (primjer je za n=2)
	//	|_|_|_|_| |_|_|_|_|	|_|_|_|_| |_|_|_|_| -> 4 * int (4 * 4 bajta)

	int *matrica = (int *)malloc(*n * *n * sizeof(int));

	//punjenje matrice - upis
	for (int i = 0; i < *n * *n; i++)
		scanf_s("%d", &matrica[i]);

	//zbrajanje dijagonala -> kod jednog pointera
	for (int i = 0; i < *n; i++) {
		*A += matrica[i * *n + i];
		*B += matrica[i * *n + (*n - i - 1)];
	}

	free(matrica);
}

void pointer_na_pointer(int * A, int * B, const int * n) {

	//alokacija pomocu pointera na pointer (primjer je za n = 2)
	// |_|_|_|_|	|_|_|_|_| 
	//
	// |_|_|_|_| 	|_|_|_|_| 

	int **matrica = (int **)malloc(*n * sizeof(int *)); //red
	for (int i = 0; i < *n; i++)
		matrica[i] = (int *)malloc(*n * sizeof(int)); //stupac

	//punjenje matrice - upis 
	for (int i = 0; i < *n; i++)
		for (int j = 0; j < *n; j++)
			scanf_s("%d", &matrica[i][j]);

	//zbrajanje dijagonala 
	for (int i = 0; i < *n; i++)
		*A += matrica[i][i];
	for (int i = 0, j = *n - 1; i < *n; i++, j--)
		*B += matrica[i][j];

	free(matrica);
}

int main() {

	int time();
	srand(time(NULL));

	int A = 0;
	int B = 0;
	int c = '0';

	int n = 0;
	scanf_s("%d", &n);

	//jedan_pointer(&A, &B, &n);
	pointer_na_pointer(&A, &B, &n);
	
	printf("%d\n", A - B);
	
	if (A - B == 0)
		printf("Matrica je najljepsa");
	else
		printf("Matrica nije najljepsa");
	getchar();
	getchar();

}
