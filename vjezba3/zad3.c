#include <stdio.h>
#include <stdlib.h>

//rjesenje pomocu 2 var - trazim visekratnik broja 3 
int skolica_shortest_var(int n){	
	static brojac = 0;
	int var = 0;

	while (n > 1) {
		var = n % 3;
		if (var == 0) {
			n /= 3; brojac++;
		}
		else if (var == 1) {
			brojac++; n--;
		}
		else if (var == 2) {
			brojac++; n -= 2;
		}
	}
	return brojac;	
}

//rjesenje pomocu dp
int skolica_shortest(int* memo, int n){
	memo[0] = 0;
	for (int i = 1; i < n; i++) {
		
		if ((i + 1) % 3 == 0) {
			memo[i] = memo[((i + 1) / 3) - 1] + 1;
			if (memo[i] > (memo[i - 1] + 1))
				memo[i] = memo[i - 1] + 1;
			continue;
		}
		
		else if ((i + 1) % 2 == 0) {
			memo[i] = memo[((i + 1) / 2) - 1] + 1;
			if (memo[i] > (memo[i - 1] + 1))
				memo[i] = memo[i - 1] + 1;
			continue;
		}
		
		else
			memo[i] = memo[i - 1] + 1;
	}
	return memo[n - 1];
}

int main() {
	int n = 169;
	//int* memo = calloc(n, n* sizeof(int));

	//printf_s("%d", skolica_shortest(memo, n));
	printf_s("%d", skolica_shortest_var(n));
	getchar();
}
