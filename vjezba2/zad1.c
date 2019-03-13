#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//random f-ja -> punim niz 
float * random(float niz[], int n) {

	while (n--) {

		//dijelim sa 100 da bi dobio float u 2 decimale
		niz[n] = (float)(rand() % 100) / 100;
		printf("%f\n", niz[n]);
	}

	return niz;
}

//trazim 3 najveca -> O(n)
int max_3(float niz[], int n) {

	float prvi = 0;
	float drugi = 0;
	float treci = 0;

	for (int i = 0; i < n; i++) {
		if (niz[i] > prvi)
			prvi = niz[i];
	}

	for (int i = 0; i < n; i++) {
		if (niz[i] == prvi)
			continue;
		if (niz[i] > drugi)
			drugi = niz[i];
	}

	for (int i = 0; i < n; i++) {
		if (niz[i] == prvi)
			continue;
		if (niz[i] == drugi)
			continue;
		if (niz[i] > treci)
			treci = niz[i];
	}

	return prvi*drugi*treci;
}

int main() {

	srand((int)time(0));

	int n = 0;
	
	do {
		scanf_s("%d", &n);
		if (2 <= n && n < 100) 
			break;
		else
			printf("mora biti 2 <= N < 100\n");
	} while (1);

	float *niz = (float *)malloc(n * sizeof(int));
	niz = random(niz, n);

	printf("%d",max_3(niz,n));
	getchar();
	getchar();

	return 0;
}

