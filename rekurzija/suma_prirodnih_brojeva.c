#include<stdio.h>
#include<stdlib.h>

int suma_prirodnih (int n){

	if (n == 1)
		return 1;
	return n + suma_prirodnih(n - 1);
}

int main() {

	int n = 0;
	int suma = 0;
	printf_s("suma prvih n prirodnih brojeva:");
	
	scanf_s("%d", &n);
	
	suma = suma_prirodnih(n);
	printf_s("%d", suma);
	
	getchar();
	getchar();

}