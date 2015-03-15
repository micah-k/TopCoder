#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

#define test(x, y) cout << #x << " = " << x << "(expected " << y << ")" << endl;

/*
Implement a class ModEncoder, which contains a method encoder.  encoder accepts
a String to encode and outputs the String encoded using the algorithm described
below.

The encoding algorithm:
First, append the minimum number of spaces required to the input string so the
string's length is a multiple of 5. Replace all spaces with tildes(~). Write
out the message in rows of 5 characters, putting each successive row below the
previous row. The encoded message starts with the message read one column at a
time, moving top to bottom down the columns and left to right across the
columns.  Finally, append a dollar sign to the encoded message to indicate the
end of the message.

For example, suppose the message is "THIS CODED MESSAGE".  It is 18 characters
long so two spaces are added at the end to make the message 20 characters long.
The rows of five characters are:
T H I S ~
C O D E D
~ M E S S
A G E ~ ~
The characters are sent one column at a time from left to right as shown below,
and a dollar sign is appended.
The encoded message is: TC~AHOMGIDEESES~~DS~$

The method signature is:
public String encoder(String input);

input will contain only letters, numbers, and spaces and will be at least 1
character and at most 100 characters.

Note:
-The encoding should remember the case.

Examples:
-The message "TopCoder is cool" is encoded to "Tdsloe~~prc~C~o~oio~$".
*/

string encoder(string input)
{
	string result;
	while(input.size() % 5 != 0)
	input.push_back(' ');

	replace(input.begin(), input.end(), ' ', '~');

	for(string::size_type i=0; i < 5; i += 1)
	{
		for(string::size_type j = 0; j < input.size(); j += 5)
		{
			char ch = input[i+j];
			result.push_back(ch);
		}
	}

	result.push_back('$');
	return result;
}

int main()
{
	test(encoder("HoW1 aRe You"), "HaooRuWe~1~~~Y~$");
	test(encoder("12345"), "12345$");
	test(encoder("Exact2rows"), "E2xraocwts$");
	test(encoder("Let us try a extraordinarily long message0123456789"), "Ls~tdioee49e~arilns05~tt~anygs16~~reoa~~a27~uyxrrlmg38~$");
	test(encoder("1"), "1~~~~$");
}
