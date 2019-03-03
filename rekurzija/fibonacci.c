#include <stdio.h>
#include <stdlib.h>

int fibonacci(int n){

	if (n == 0)
		return 0;
	if (n == 1)
		return 1;

	return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {

	int n = 0;
	printf("prvih n brojeva fibonaccijevog niza:");
	scanf_s("%d", &n);
	 
	for (int i = 0; i < n; i++)
		printf_s("%d\n", fibonacci(i));
	   
	getchar();
	getchar();

}
