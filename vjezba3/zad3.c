#include <stdio.h>
#include <stdlib.h>

// trazim visekratnik broja 3 
// logika je da tezim broju koji ce napraviti najveci skok, a to je n / 3
// pr. 9/3 = 3, dakle 9 -> 3 -> 1, pr. 10 % 3 = 1; 10 - 1 = 9; 9 % 3 = 0; 10 -> 9 -> 3 -> 1

int skolica_shortest(int n){	
	int brojac_skokova = 0;
	int mod = 0;

	while (n > 1) {
		mod = n % 3;

		switch (mod) {
			// ako je djeljiv skacem na broj n / 3:
		case 0: n /= 3; brojac_skokova++; break;
			// ako je % == 1 pomicem se jedan korak unazad do broja djeljivog sa 3:
		case 1: brojac_skokova++; n--; break;	
			// ako je % == 2 pomicem se 2 koraka unazad do broja djeljivog sa 3:
		case 2: brojac_skokova++; n -= 2;		
		}
	}
	return brojac_skokova;	
}

//ista logika kao prethodna samo pomocu dp
int skolica_shortest_dp(int* memo, int n){
	memo[0] = 0;
	memo[1] = 1;
	int mod = 0;

	for (int i = 2, m = i + 1; i < n; i++, m++) {
		mod = m % 3;

		switch (mod){
		case 0: memo[i] = memo[(m / 3) - 1] + 1; continue;		
		case 1: memo[i] = memo[i - 1] + 1; continue;	
		case 2: memo[i] = memo[i - 2] + 1; 
		}		
	}
	return memo[n - 1];
}

int main() {
	int n = 3167;
	int* memo = calloc(n, n* sizeof(int)); //niz za memoizaciju

	printf_s("bez dp: %d\n", skolica_shortest(n));
	printf_s("sa dp: %d", skolica_shortest_dp(memo, n));
	getchar();
}
