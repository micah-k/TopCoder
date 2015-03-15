#include <string>
#include <iostream>
#include <sstream>

using namespace std;

#define test(x, y) cout << #x << " = " << x << "(expected " << y << ")" << endl;

/*
Implement a class StringCompressor, which contains a method compress.  The
method takes a String as a parameter and replaces all successively duplicated
letters in the String with a number that is the number of duplications followed
by the repeated character.  The method returns this resulting String.

The method signature is (be sure your method is public):
String compress(String toCompress)

TopCoder will ensure the following:
- toCompress is a String of at most 100 letters.  Each character is a lowercase
or capital letter ('a' - 'z' or 'A' - 'Z').

Note:
-This compressor is case sensative.  'A' is a different character than 'a'.
-Single letters (its neighbors are not duplicates of itself) are left alone.

Examples:
"AAAABBBBCDDDDDD" compresses to "4A4BC6D"
"SDFJaAAAAaaaass" compresses to "SDFJa4A4a2s"
"AAAAAAAAAAAf" compresses to "11Af"
*/

string compress(string toCompress)
{
	stringstream ss;

	char cur = '\0';
	int count = 1;
	for(string::size_type i = 0; i < toCompress.size(); i++)
	{
		if (cur == toCompress[i])
		{
			count++;
		}
		else
		{
			if (count > 1)
				ss << count;
			ss << cur;

			count = 1;
			cur = toCompress[i];
		}
	}

	if (toCompress.size() > 0)
	{
		if (count > 1)
			ss << count;
		ss << cur;
	}
	return ss.str();
}

int main()
{
	test(compress(""), "");
	test(compress("abcAbC"), "abcAbC");
	test(compress("aaAAdaddd"), "2a2Ada3d");
	test(compress("abcdaacccc"), "abcd2a4c");
	test(compress("zxxxxxxxxxxxzz"), "z11x2z");
}
