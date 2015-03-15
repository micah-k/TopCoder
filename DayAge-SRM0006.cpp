#include <string>
#include <iostream>
#include <sstream>

using namespace std;

#define test(x, y) cout << #x << " = " << x << "(expected " << y << ")" << endl;

/*
Implement a class DayAge which contains a method getDaysOld.  The method is
passed, as Strings, someone's birth date and a current date  and returns the
number of days old the person is, as an int.

The input Strings will be of form mm/dd/yyyy.
m, d, and y represent digits (0 through 9).
mm is between 01 and 12, inclusive.
dd is between 01 and 31, inclusive.
yyyy is between 1901 and 2001, inclusive.

Keep in mind:
Thirty days has September, April, June and November; all the rest have
thirty-one, but February twenty-eight alone except in leap year once in four
when February has one day more.
From 1901 to 2001, the leap years are 1904, 1908, ... 2000 (Every 4 years, no
exceptions).
There are 365 days in a non-leap year, 366 in a leap year.

Assume the time the person was born is noon and the time on the current day is
noon.

Here is the method signature:
public int getDaysOld(String birthdate, String currdate);

Notes:
- Both Strings are of the form given above.  TopCoder will prevent improperly
formatted input parameters from reaching your method.
- Both dates exist (no february 30ths or anything) and the birthday is not
after the current day.  TopCoder will check this too.
- If the birth date and current date are the same, the method should return 0.
- The string "Calendar" cannot occur anywhere in your code.

Examples:
If birthdate="10/10/1999" and currdate="10/10/2000", the method returns 366.
If birthdate="02/03/1940" and currdate="12/04/1999", the method returns 21854.
*/
void parseDate(string date, int& month, int& day, int& year)
{
  year = -1;
  stringstream ss;
  ss << date;
  ss >> month;
  ss.ignore(1);
  ss >> day;
  ss.ignore(1);
  ss >> year;
}

int yeardays(int year)
{
  return ((year - 1900) % 4 == 0) ? 366 : 365;
}

int monthdays(int month, int year)
{
  if (month == 2)
    return ((year - 1900) % 4 == 0) ? 29 : 28;
  else if (month == 4 || month == 6 || month == 9 || month == 11)
    return 30;
  return 31;
}

int getDaysOld(string birthdate, string currdate)
{
  int birthday, birthmonth, birthyear;
  parseDate(birthdate, birthmonth, birthday, birthyear);

  int currday, currmonth, curryear;
  parseDate(currdate, currmonth, currday, curryear);

  int result = 0;
  if (birthyear == curryear)
  {
    if (birthmonth == currmonth)
    {
      result = currday- birthday;
    }
    else
    {
      result = monthdays(birthmonth, birthyear) - birthday;

      for (int month = birthmonth + 1; month < currmonth; month++)
        result += monthdays(month, birthyear);

      result += currday;
    }
  }
  else
  {
    result = monthdays(birthmonth, birthyear) - birthday;

    for (int month = birthmonth + 1; month < 13; month++)
      result += monthdays(month, birthyear);

    for (int year = birthyear + 1; year < curryear; year++)
      result += yeardays(year);

    for(int month = 1; month < currmonth; month++)
      result += monthdays(month, curryear);

    result += currday;
  }

  return result;
}

int main()
{
  test(getDaysOld("03/02/1999", "03/04/1999"), 2);
  test(getDaysOld("10/12/1992", "10/12/1992"), 0);
  test(getDaysOld("12/31/1960", "05/03/2001"), 14733);
  test(getDaysOld("04/30/1999", "06/10/2001"), 772);
  test(getDaysOld("03/31/1910", "10/02/1977"), 24657);
}
