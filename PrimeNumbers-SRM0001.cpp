#include <iostream>

using namespace std;

#define test(x, y) cout << #x << " = " << x << "(expected " << y << ")" << endl;

template <class T> T gcd(T a, T b)
{
	if (a < 0 && b < 0) return gcd(-a,-b);
	if (a == 0) return b;
	if (b == 0) return a;
	if (a > b) return gcd(b, a);
	if (b % a == 0) return a;
	return gcd(a, b % a);
}

/*
Implement a class PrimeNumbers that contains a method pairwisePrimes.  The
method inputs an int (num) and returns the number of ways the number can be
written as the sum of three distinct integers that are pairwise relatively
prime; that is no pair of the three integers has a common factor greater than 1.

Note:

- num is greater than 0 and less than or equal to 40.
- One of the three distinct integer can be 1; Numbers are Pairwise Relatively
Prime if they share no factor GREATER than 1.

Method Signature:

public int pairwisePrimes( int );

Examples:

For num=8:  8 can be written as 1+2+5 and 1+3+4 and the method should return 2.
For num=18, the method should return 14
*/

int pairwisePrimes(int target)
{
	int result = 0;
	for(int a = 1; a < target; a += 1)
		for(int b = a + 1; b < target; b += 1)
			for(int c = b + 1; c < target; c += 1)
				if (gcd(a, b) == 1 && gcd(a, c) == 1 && gcd(b, c) == 1 && a+b+c == target)
				{
					result++;
				}
	return result;
}

int main()
{
	test(pairwisePrimes(13),1);
	test(pairwisePrimes(38),48);
	test(pairwisePrimes(27),10);
	test(pairwisePrimes(32),34);
	test(pairwisePrimes(12),6);
}
