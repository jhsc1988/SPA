#include <stdio.h>
#include <stdlib.h>

//trazim max value - bottom - up
int trazim_value(int* niz, int* memo, int N) {	
	memo[0] = niz[0];
	for (int i = 1; i < N; i++) {
		if (i <= 4)
			memo[i] = memo[i - 1] > niz[i] ? memo[i - 1] : niz[i];
		else {
			memo[i] = (niz[i] + memo[i - 5]) > memo[i - 1] ? niz[i] + memo[i - 5] : memo[i - 1];
		}
	}
	return memo[N - 1];
}

int main() {
	int niz[12] = { 3, 4, 4, 6, 2, 8, 6, 9, 7, 3, 1, 4 }; // 15
	int *memo = malloc (sizeof(niz)/sizeof(int) * sizeof(int)); // pomocni niz

	printf_s("%d", trazim_value(niz, memo, sizeof(niz) / sizeof(int)));
	getchar();
}
