#include <iostream>

using namespace std;

#define test(x, y) cout << #x << " = " << x << "(expected " << y << ")" << endl;

/*
Implement a class Finances, which contains a function timeLeft.  timeLeft is
passed three int values.  The initial value of the bank account is
initialValue.  Interest is compounded monthly at a rate of interest percent.
Every month monthly dollars is taken out from the account (immediately after
the Interest has been added).  timeLeft must return an int that is the number
of months the account can support the full monthly withdrawal.  If the account
will last longer than 1200 months, the function should return 1200.

The method signature is:
int timeLeft(int initialValue, int interest, int monthly).

NOTE: initialValue and monthly are greater than or equal to 0 and less than or
equal to 100,000.  interest is greater than or equal to 0 and less than or
equal to 1000.

Examples:
(100, 0, 100) -> 1
(200, 1, 300) -> 0
(3453, 8, 200) -> 1200
*/
int timeLeft(int initialValue, int interest, int monthly)
{
  if (monthly == 0) return 1200;
  if (initialValue < monthly) return 0;

  int months = 0;
  double balance = initialValue;

  while (months < 1200)
  {
    if (interest > 0)
    {
      double earnedInterest = balance * (interest / 100.0);
      balance += earnedInterest;
    }
    balance -= monthly;
    if (balance < 0) return months;
      months += 1;
  }
  return months;
}

int main()
{
  test(timeLeft(100, 20, 100), 1);
  test(timeLeft(50, 10, 10), 7);
  test(timeLeft(2000, 10, 2300), 0);
  test(timeLeft(100, 14, 1), 1200);
  test(timeLeft(1, 50, 1), 1);
}
