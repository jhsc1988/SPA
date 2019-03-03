#include<stdio.h>
#include<stdlib.h>


int factorial(int n) {

	if (n == 0)
		return 1;

	return n * factorial(n - 1);
}

int main() {

	int n = 0;
	printf_s("faktorijel od:");
	scanf_s("%d", &n);

	printf_s("%d", factorial(n));

	getchar();
	getchar();

}