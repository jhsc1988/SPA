#include <stdio.h>
#include <stdlib.h>

int to_binary(int n) {

	if (n == 0)
		return 0;

	to_binary(n / 2);
	printf_s("%d", n % 2);
	return 0;
}

int main() {

	int b = 0;
	printf_s("dec to binary:");
	scanf_s("%d", &b);

	to_binary(b);

	getchar();
	getchar();

}
