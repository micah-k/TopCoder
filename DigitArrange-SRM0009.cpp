#include <vector>
#include <iostream>

using namespace std;

#define test(x, y) cout << #x << " = " << x << "(expected " << y << ")" << endl;

/*
Implement a class DigitArrange which contains a method targetDiff.  The method
is passed two ints as parameters: a source and a target.  The method rearranges
the digits of the source to two distinct integers whose difference magnitude is
as close to without exceeding the target as possible.  The method returns the
magnitude of this difference.

Here is the method signature:
public int targetDiff(int source,int target);

The source is between 10 and 999999, inclusive.
The target is between 1 and 999999, inclusive.

Note:
-If it is impossible not to exceed the target, the method returns -1.
-Any 0s to the left of all non-zero digits in the source are not digits in
source.
-However, when arranging the digits of source, the first digit(s) of the
arranged value can be 0.
-One of the rearranged values may equal the source.

Examples:
-If the source is 981 and the target is 50, the two distinct values yielding
the difference's magnitude closest to the target are 918 and 891.  The
difference is 27 and the method returns 27.
-If the source is 450 and the target is 9, the two distinct values yielding the
difference's magnitude closest to the target are 045 and 054.  The method
returns the difference, 9.
-If the source is 100 and the target is 2, there is no way to arrange the
source's digits to get two distinct numbers whose difference is less than 2, so
the method returns -1.
*/

int targetDiff(int source, int target)
{
  vector<int> digits;
  while (source > 0)
  {
    digits.push_back(source % 10);
    source /= 10;
  }

  for(vector<int>::size_type i = 0; i < digits.size(); i++)
    cout << digits[i] << endl;

  return 0;
}

int main()
{
  test(targetDiff(12345, 1235), 12345);
}
