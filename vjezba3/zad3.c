#include <stdio.h>
#include <stdlib.h>

// niz koristim tako na svakom clanu niza pamtim najmanji broj koraka do prvog polja
int skolica_shortest(int* memo, int n) {
	memo[0] = 0;
	for (int i = 1; i < n; i++) {

		// ako je n / 3, broju koraka na polju n / 3 pribrojavam skok na to polje
		if ((i + 1) % 3 == 0) {
			memo[i] = memo[(i + 1) / 3 - 1] + 1; 

			// ako je memo[i] za 2 veci od memo[i - 1], jeftinije je vratit se jedan korak unazad
			if (memo[i] > (memo[i - 1] + 1)) memo[i] = memo[i - 1] + 1; 
			continue;
		}

		// ako je n / 2, broju koraka na polju n / 2 pribrojavam skok na to polje
		else if ((i + 1) % 2 == 0) {
			memo[i] = memo[(i + 1) / 2 - 1] + 1;

			// ako je memo[i] za 2 veci od memo[i - 1], jeftinije je vratit se jedan korak unazad
			if (memo[i] > (memo[i - 1] + 1)) memo[i] = memo[i - 1] + 1;
			continue;
		}
		else
			memo[i] = memo[i - 1] + 1;
	}
	return memo[n - 1]; //vracam trazeni broj skokova
}

int main() {

	int n = 120;
	int* memo = calloc(n, n* sizeof(int));

	printf_s("%d", skolica_shortest(memo, n));
	getchar();
}
