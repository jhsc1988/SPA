#include <stdio.h>
#include <stdlib.h>

//trazim max value pomocu dinamickog programiranja (dp)
int trazim_value(int* niz, int* memo, int N) {	
	memo[0] = niz[0];

	for (int i = 1; i < N; i++) {
		if (i <= 4) {
			if (memo[i - 1] > niz[i])
				memo[i] = memo[i - 1];
			else
				memo[i] = niz[i];
		}

		if (i > 4) {
			if ((niz[i] + memo[i - 5]) > memo[i - 1])
				memo[i] = niz[i] + memo[i - 5];
			else
				memo[i] = memo[i - 1];
		}
	}
	return memo[N - 1];
}

int main() {
	int niz[12] = { 3, 4, 4, 6, 2, 8, 6, 9, 7, 3, 1, 4 }; // 15
	int memo[12]; // pomocni niz za dp (memoizacija)

	printf_s("%d", trazim_value(niz, dp, sizeof(niz) / sizeof(int)));
	getchar();
}
