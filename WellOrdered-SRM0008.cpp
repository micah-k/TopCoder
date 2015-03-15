#include <iostream>

using namespace std;

#define test(x, y) cout << #x << " = " << x << "(expected " << y << ")" << endl;

/*
Implement a class WellOrdered, which contains a method numberOf.  The method
takes two ints as parameters: the number of digits, d, and the number base, b.
The method returns an int (base-10) that is the number of positive well ordered
integers with d digits in the base-b number system.

A well ordered integer is an integer in which the digits strictly increase from
left(most significant) to right(least significant).  For example 145 is a well
ordered integer.  442 and 445 are not.

In base 16, the digits from smallest to greatest are:
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F
In any base, b, less than or equal to 16, the digits are the first b of those
above.

Therefore, in base 12, 79B is a well ordered integer of three digits.  In base
16, the number 8CDE is a well ordered integer of four digits.  E6 is not a well
ordered integer in base 15 (nor in base-16 for that matter...).

The method signature is:
int numberOf(int digits, int base);
Be sure your method is public.

digit and base satisfy:
0 < digit < 5
1 < base < 17

Note:
Any 1 non-zero digit number is well ordered.
Numbers with leading zeroes are not valid.  For example, 012 is not a well
ordered number with three digits.

Examples:
-In base 5, the well ordered numbers with 3 digits are:
 123
 124
 134
 234
 So if digit=3 and base=5, the method should return 4.
*/

int numberOf(int msd, int digits, int base)
{
	if (digits == 0) return 1;

	int result = 0;
	for(int digit = msd+1; digit < base; digit++)
		result += numberOf(digit, digits-1,base);

	return result;
}

int numberOf(int digits, int base)
{
	return numberOf(0, digits, base);
}

int main()
{
	test(numberOf(3, 5), 4);
	test(numberOf(4, 16), 1365);
	test(numberOf(3, 13), 220);
	test(numberOf(4, 3), 0);
	test(numberOf(3, 15), 364);
	test(numberOf(4, 16), 1365);
	test(numberOf(1, 2), 1);
	test(numberOf(4, 16), 1365);
	test(numberOf(2, 16), 105);
	test(numberOf(1, 2), 1);
	test(numberOf(4, 10), 126);
	test(numberOf(4, 16), 1365);
	test(numberOf(1, 2), 1);
	test(numberOf(1, 2), 1);
	test(numberOf(4, 16), 1365);
	test(numberOf(1, 2), 1);
	test(numberOf(4, 9), 70);
	test(numberOf(3, 4), 1);
	test(numberOf(1, 2), 1);
	test(numberOf(4, 15), 1001);
	test(numberOf(4, 2), 0);
	test(numberOf(4, 16), 1365);
	test(numberOf(2, 3), 1);
	test(numberOf(2, 2), 0);
	test(numberOf(1, 2), 1);
	test(numberOf(1, 10), 9);
}
