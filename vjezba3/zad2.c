#include <stdio.h>
#include <stdlib.h>

//trazim max value pomocu dinamickog programiranja (dp)
int trazim_value(int* niz, int* dp, int N) {	
	dp[0] = niz[0];

	for (int i = 1; i < N; i++) {
		if (i <= 4) {
			if (dp[i - 1] > niz[i])
				dp[i] = dp[i - 1];
			else
				dp[i] = niz[i];
		}

		if (i > 4) {
			if ((niz[i] + dp[i - 5]) > dp[i - 1])
				dp[i] = niz[i] + dp[i - 5];
			else
				dp[i] = dp[i - 1];
		}
	}
	return dp[N - 1];
}

int main() {
	int niz[12] = { 3, 4, 4, 6, 2, 8, 6, 9, 7, 3, 1, 4 }; // 15
	int dp[12]; // pomocni niz za dp

	printf_s("%d", trazim_value(niz, dp, sizeof(niz) / sizeof(int)));
	getchar();
}
