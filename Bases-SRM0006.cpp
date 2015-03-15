#include <string>
#include <iostream>

using namespace std;

#define test(x, y) cout << #x << " = " << x << "(expected " << y << ")" << endl;

/*
Implement a class Bases, which contains a method adder.  The method takes two
Strings as parameters representing numbers in a certain number base and an int
that is that base.  The method returns the sum of the numbers, also in the same
base.

Adding numbers in bases other than 10 is similar to adding numbers in base 10.
Start at the least significant digit, add, and carry...  There is a carry when
the sum is greater than or equal to the number base.

The base will be at most 16.
For base 16, the digits in order are:
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F
For any base b less than 16, the digits are the first b digits in the list above.

For example, add 613.56 and 104.4 in base 7:

  11
 104.40
 613.56
-------
1021.26
(When adding the 4 and the 5 to the right of the decimal, the sum is 2 more
than the base, so there is a carry (1) and the sum minus the base (2) is
written below...)

For example. add 1D.8 and 2.A in base 16:

11
1D.8
02.A
----
20.2

When returning the sum, all leading 0s are truncated, unless the result is 0.
If the result is 0, the method returns "0".
If the fractional part is 0, the point and all 0s to its right are truncated.
If the fractional part is non-zero, all trailing 0s are truncated.

Here is the method signature (be sure your method is public):
String adder(String arg1, String arg2, int base)

TopCoder will ensure the following:
base is between 2 and 16, inclusive.
arg1 and arg2 have length at least 1 and at most 50.
arg1 and arg2 correctly represent non-negative numbers in the specified base
and contain only the characters '0' - '9' and 'A' - 'F' and '.'.

NOTES:
arg1 and arg2 may or may not have a '.', fractional part, or integer part.
The left most digit of arg1 and arg2 is the most significant digit.  The right
most digit is least significant.

Examples:
*If arg1 = 102.4, arg2 = 63.23, and base=10, the method returns 165.63
*If arg1 = 1D.EE, arg2 = D11.A12, and base=15, the method returns D30.A02
*If arg1 = .4, arg2 = .4, and base=8, the method returns 1
*/

int Value(char character)
{
  switch(character)
  {
  case 'F': return 15;
  case 'E': return 14;
  case 'D': return 13;
  case 'C': return 12;
  case 'B': return 11;
  case 'A': return 10;
  case '9': return 9;
  case '8': return 8;
  case '7': return 7;
  case '6': return 6;
  case '5': return 5;
  case '4': return 4;
  case '3': return 3;
  case '2': return 2;
  case '1': return 1;
  default: return 0;
  }
}

char Character(int value)
{
  switch(value)
  {
  case 15: return 'F';
  case 14: return 'E';
  case 13: return 'D';
  case 12: return 'C';
  case 11: return 'B';
  case 10: return 'A';
  case 9: return '9';
  case 8: return '8';
  case 7: return '7';
  case 6: return '6';
  case 5: return '5';
  case 4: return '4';
  case 3: return '3';
  case 2: return '2';
  case 1: return '1';
  default: return '0';
  }
}

string adder(string arg1, string arg2, int base)
{
  string::iterator pos1 = find(arg1.begin(), arg1.end(), '.');
  string::iterator pos2 = find(arg2.begin(), arg2.end(), '.');
  if(pos1 != arg1.end() || pos2 != arg2.end())
  {
    if (pos1 == arg1.end()) { arg1.push_back('.'); pos1 = arg1.end(); } else pos1++;
    if (pos2 == arg2.end()) { arg2.push_back('.'); pos2 = arg2.end(); } else pos2++;

    while(pos1 != arg1.end() || pos2 != arg2.end())
    {
      if (pos1 == arg1.end()) { arg1.push_back('0'); pos1 = arg1.end(); } else pos1++;
      if (pos2 == arg2.end()) { arg2.push_back('0'); pos2 = arg2.end(); } else pos2++;
    }
  }

  reverse(arg1.begin(), arg1.end());
  reverse(arg2.begin(), arg2.end());

  string result;
  pos1 = arg1.begin();
  pos2 = arg2.begin();
  int carry = 0;
  while(pos1 != arg1.end() || pos2 != arg2.end())
  {
    if (pos1 != arg1.end() && pos2 != arg2.end() && *pos1 == '.')
    {
      result.push_back('.');
      pos1++;
      pos2++;
    }
    else
    {
      int value = carry;
      if (pos1 != arg1.end()) { value += Value(*pos1); pos1++; }
      if (pos2 != arg2.end()) { value += Value(*pos2); pos2++; }

      carry = value / base;
      value = value % base;
      result.push_back(Character(value));
    }
  }
  if (carry > 0) result.push_back(Character(carry));

  reverse(result.begin(), result.end());
  return result;
}

int main()
{
  test(adder("1001.111", "11010.00011", 2), "100011.11111");
  test(adder("321.123", "1.1", 5), "322.223");
  test(adder("123456.066", "001234.166", 7), "125023.265");
  test(adder("A.92", "D.EE", 15), "19.91");
  test(adder("3", ".2", 4), "3.2");
}
