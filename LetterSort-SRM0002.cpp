#include <string>
#include <iostream>

using namespace std;

#define test(x, y) cout << #x << " = " << x << "(expected " << y << ")" << endl;

/*
Implement a class LetterSort, which contains a method doSort.  doSort takes a
String as a parameter and sorts the characters in the string in order of their
first appearance in the string.  For example CABCACCB sorts to CCCCAABB.  The
method doSort should return the sorted String.

The method signature is:
public String doSort(String input);

input is a string of at least 1 character and at most 50 characters.  The
characters are letters or numbers.

Note:
-The sort is case sensitive.  "A" is a different character than "a".

Examples:
If input="TopCoder", the method returns "ToopCder"
If input="HiHowAreYou", the method returns "HHioowAreYu"
*/

string doSort(string input)
{
	string result;
	while(input.size() > 0)
	{
		if (input.size() > 1)
		{
			for(string::size_type i = 1; i < input.size(); i++)
				if (input[i] == input[0])
				{
					result.push_back(input[i]);
					input.erase(i, 1);
				}
		}
		result.push_back(input[0]);
		input.erase(0,1);
	}
	return result;
}

int main()
{
	test(doSort("ThisIsATest"), "TThisssIAet");
	test(doSort("abcdeABCDE"), "abcdeABCDE");
	test(doSort("SlipperySam"), "SSlipperyam");
	test(doSort("AbCdEEdCbA"), "AAbbCCddEE");
	test(doSort("nachonachoma1n21"), "nnnaaacchhoom112");
}
