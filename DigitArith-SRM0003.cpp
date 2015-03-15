#include <iostream>
#include <cmath>

using namespace std;

#define test(x, y) cout << #x << " = " << x << "(expected " << y << ")" << endl;

/*
Implement a class DigitArith, which contains a method closestToTarget.  The
method takes 2 ints as parameters: a source and a target.  The method performs
3 digit arithmetic operations (defined below) successively on the source and
returns the closest possible result to the target.

Digit Arithmetic Operations:
1. Addition - any digit in the operand can be added to the operand.  Defined
when the result is less than 10,000.
2. Subtraction - any digit in the operand can be subtracted from the operand.
Defined when the result is non-negative.
3. Multiplication - any digit in the operand can be multiplied by the operand.
Defined when the result is less than 10,000.
4. Division - any digit in the operand can divide the operand.  The floor of
the result is taken (Integer Division). Defined when the digit is non-zero.

Note:
-The operations are performed on the result of the previous operation.  ex: for
the second operation, a digit is chosen from the result of the first, not the
source.
-No intermediate results can be negative.
-The digits are always non-negative.

The method signature is:
int closestToTarget(int source, int target);

source and target are non-negative integers less than 1,000.

Example:
-If the source is 12 and the target is 85, the three operations that yeild the
result closest to the target are
 12, take the (2) digit, and multiply: 12*2=24
 24, take the (4), and multply: 24*4=96
 96, take the (9), and subtract: 96-9=87
 And the method should return 87.
-If the source is 54 and the target is 13,
 54/4=13 -> 13+1=14 -> 14-1=13.
 And the method should return 13.
*/

int doop(int source, int op, int val)
{
  switch(op)
  {
  case 0: return source + val;
  case 1: return source - val;
  case 2: return source * val;
  default: return val == 0 ? -1 : source / val;
  }
}

int closestToTarget(int source, int target, int opsremaining)
{
  if (source < 0) return -1;
  if (opsremaining == 0) return source;

  int closest = source;
  int digits = source;
  while(digits > 0)
  {
    int digit = digits % 10;
    digits /= 10;

    int add = closestToTarget(source + digit, target, opsremaining-1);
    int sub = closestToTarget(source - digit, target, opsremaining-1);
    int mul = closestToTarget(source * digit, target, opsremaining-1);
    int div = (digit > 0) ? closestToTarget(source / digit, target, opsremaining-1) : -1;

    if (add >= 0 && abs(add-target) < abs(closest - target))
      closest = add;
    if (sub >= 0 && abs(sub-target) < abs(closest - target))
      closest = sub;
    if (mul >= 0 && abs(mul-target) < abs(closest - target))
      closest = mul;
    if (div >= 0 && abs(div-target) < abs(closest - target))
      closest = div;
  }
  return closest;
}

int closestToTarget(int source, int target)
{
  return closestToTarget(source, target, 3);
}

int main()
{
  test(closestToTarget(0, 0), 0);
  test(closestToTarget(100, 0), 0);
  test(closestToTarget(4, 50), 44);
  test(closestToTarget(96, 14), 14);
  test(closestToTarget(999, 300), 252);
}
