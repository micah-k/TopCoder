#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

#define test(x, y) cout << #x << " = " << x << "(expected " << y << ")" << endl;

/*
Implement a class Fraction, which contains a method getXSmallest.  The method
is passed two integers: an index and a maximum denominator. The program should
find all fractions of the form a / b where b is less than or equal to the
maximum denominator and a / b is less than 1 and then return the index-th
smallest of these fractions.  The method should return the fraction as a double
value, rounded to 3 decimal points (use the supplied formatDouble function).

Note:

- If index value is greater than the number of fractions that are less than 1,
the method should return 1.
- Fractions should not be simplified.  1/2 and 2/4 are two unique fractions,
despite their equal double values
- The class and method must be declared as public
- The index must be between 1 and 70, inclusive.  The max denominator must be
between 2 and 12, inclusive. (TopCoder will check these constraints, you need
not.)

The method signature is :

public double getXSmallest(int, int);

Example:

For example, if index = 3 and max denominator = 4, all the fractions of the
form a / b are 1/4, 1/3, 1/2, 2/4, 2/3, 3/4, and the method should return the
third smallest, as a double: 0.5.int
*/
double getXSmallest(int index, int maxDenominator)
{
  vector<double> v(70,1);
  for (int num = 1; num < maxDenominator; num += 1)
    for (int denom = maxDenominator; denom > num; denom -= 1)
      v.push_back(((double)num) / ((double)denom));

  sort(v.begin(), v.end());

  return v[index-1];
}

int main()
{
  test(getXSmallest(1, 2), 0.5);
  test(getXSmallest(63, 8), 1.0);
  test(getXSmallest(40, 12), 0.583);
  test(getXSmallest(53, 11), 0.889);
  test(getXSmallest(14, 7), 0.6);
}
