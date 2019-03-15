#include <stdio.h>

int recursiveFun1(int n){
	if (n <= 0)
		return 1;
	else
		return 1 + recursiveFun1(n - 1);
}
//The first function is being called recursively n times 
//before reaching base case so its O(n), often called linear.

int recursiveFun2(int n){
	if (n <= 0)
		return 1;
	else
		return 1 + recursiveFun2(n - 5);
}
//The second function is called n - 5 for each time, 
//so we deduct five from n before calling the function, 
//but n - 5 is also O(n). 
//(Actually called order of n / 5 times.And, O(n / 5) = O(n)).

int recursiveFun3(int n){
	if (n <= 0)
		return 1;
	else
		return 1 + recursiveFun3(n / 5);
}
//This function is log(n) base 5, for every time we divide by 5 
//before calling the function so its O(log(n))(base 5), 
//often called logarithmic and most often Big O notation 
//and complexity analysis uses base 2.

void recursiveFun4(int n, int m, int o){
	if (n <= 0){
		printf("%d, %d\n", m, o);
	}
	else {
		recursiveFun4(n - 1, m + 1, o);
		recursiveFun4(n - 1, m, o + 1);
	}
}
//In the fourth, it's O(2^n), or exponential, 
//since each function call calls itself twice unless it has been recursed n times.

int recursiveFun5(int n) {
	for (int i = 0; i < n; i += 2) {
		// do something
	}

	if (n <= 0)
		return 1;
	else
		return 1 + recursiveFun5(n - 5);
}
//As for the last function, the for loop takes n / 2 since we're increasing by 2, 
//and the recursion take n-5 and since the for loop is called recursively therefore 
//the time complexity is in (n-5) *(n/2) = (2n-10) * n = 2n^2- 10n, 
//due to Asymptotic behavior and worst case scenario considerations or 
//the upper bound that big O is striving for, we are only interested in the largest term so O(n^2).
