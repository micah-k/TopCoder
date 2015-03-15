#include <string>
#include <iostream>

using namespace std;

#define test(x, y) cout << #x << " = " << x << "(expected " << y << ")" << endl;

/*
Class Name: CommonChar
Method Name: compare
parameters:  String, String
returns: int

Create a class CommonChar containing the method compare. This method will take
two Strings as inputs and return the number of characters in the second String
that are contained in the first string, in a one-to-one relationship.  That is,
if a character is repeated in the second string, it must be repeated in the
first string to count more than once.

Here is the method signature:
public int compare(String input1, String input2);

BOth Strings will have fewer than 100 characters.

Note:
-The method is case sensitive.  A is a different character than a.

Examples:
("java", "abava") -> 3  (two of the (a)s and the (v))
("TopCoder", "code guru") -> 4
("foobar", "sing") -> 0
*/

int compare(string input1, string input2)
{
  int result = 0;
  for(string::size_type i = 0; i < input1.size(); i++)
  {
    string::iterator j = find(input2.begin(), input2.end(), input1[i]);
    if (j != input2.end())
    {
      input2.erase(j);
      result++;
    }
  }
  return result;
}

int main()
{
  test(compare("", ""), 0);
  test(compare("aAa", "aAaA"), 3);
  test(compare("Hi1 how are you", "I am 1good"), 6);
  test(compare(".,~~abcABC", "~~~efgaaABB"), 5);
  test(compare("abc3", "abc3"), 4);
}
