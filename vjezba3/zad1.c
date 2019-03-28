#include <stdio.h>
#include <stdlib.h>

//trazim value pomocu dinamickog pogramiranja (dp)
int trazim_value_dp(int* niz,int* memo, int N) {
	int best_value = 0;
	memo[0] = niz[0];

	for (int i = 1; i < N; i++) {
		if (niz[i] > niz[i] + memo[i - 1])
			memo[i] = niz[i];
		else
			memo[i] = memo[i - 1] + niz[i];
		if (memo[i] > best_value)
			best_value = memo[i];
	}	
	return best_value;
}

///trazim max value bez dinamickog programiranja - pomocu 2 varijable (var)
int trazim_value_var(int* niz, int N) {
	int best_value = 0;
	int suma = 0;

	for (int i = 0; i < N; i++) {
		suma += niz[i];
		if (suma < 0) {
			suma = 0;
			continue;
		}
		if (suma > best_value)
			best_value = suma;
	}
	return best_value;
}

int main() {
	//int niz[18] = { 9, 2, 3, 5, -7, -6, 5, -8, 8, -7, 2, -3, 1, -3, -4, 1, -5, -6 };
	//int niz[12] = { 3, 4, 4, 6, 2 ,8 ,6 ,9, 7, 3, 1, 4 };
	int niz[8] = { -2, -3, 4, -1, -2, 1, 5, -3 }; //7
	int memo[8] = { 0 }; //pomocni niz za dp (memoizacija)

	//printf_s("%d", trazim_value_var(niz, sizeof(niz) / sizeof(int)));
	printf_s("%d", trazim_value_dp(niz, memo, sizeof(niz)/sizeof(int)));
	getchar();
}
