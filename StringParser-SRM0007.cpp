#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

#define test(x, y) cout << #x << " = " << x << "(expected " << y << ")" << endl;

template <class T> string AsString(const T& t)
{
	stringstream s;
	s << t;
	return s.str();
}

template <class T> ostream& operator << (ostream& os, const vector<T>& t)
{
  os << "{";
  for (vector<T>::size_type i = 0; i < t.size(); i++) os << (i ? ", " : "") << t[i];
  os << "}";
  return os;
}

/*
Implement a class StringParser, which contains a method parse.  The method
takes a String as a parameter.  The first(left-most) character of the String is
the delimiting character and the String is broken at each occurrence of the
delimiter and each occurrence of the delimiter is removed.  The method returns
an ArrayList of the pieces of non-zero length in the reverse order of their
occurrence.

For example, if the String is ".period.is.the..delimiter" the method returns
the ArrayList {"delimiter","the","is","period"}.

Here is the method signature:
public ArrayList parse(String toParse);

toParse is a String with length between 1 and 50 characters, inclusive.
toParse contains letters, digits, spaces, and simple punctuation
('.',',','?','!','-'). Note the pipe is not valid.

Note:
-If there are no pieces of non-zero length after breaking the String, the
method returns an empty instance of an ArrayList.
Examples:
-If toParse="AAthisAAAisAaAAtestAAA" the method returns {"test","a","is","this"}.

If you are not familiar with java.util.ArrayList, they are used to hold
objects, such as Integers and Strings. ArrayList.add(obj) will add obj to the
end of an Array List. ArrayList.get(n) will return the nth object.
ArrayList.remove(n) will remove the nth object and shift forward all objects
behind it. ArrayList.size() returns the number of objects in the ArrayList.
*/

vector<string> parse(string toParse)
{
	vector<string> result;
	char ch = toParse.front();
	string::size_type b = 0, e;
	for(e = 0; e < toParse.size(); e++)
	{
		if (toParse[e] == ch)
		{
			if (e - b > 1)
			{
				result.emplace(result.begin(), toParse.substr(b+1,(e-b)-1));
			}
			b = e;
		}
	}
	if (e - b > 1)
		result.emplace(result.begin(), toParse.substr(b+1,(e-b)-1));

	return result;
}

int main()
{
	test(AsString(parse(".")), "{}");
	test(AsString(parse(",This,is,,,a,test,")), "{test, a, is, This}");
	test(AsString(parse("AHIAHOWAAREAYOU")), "{YOU, RE, HOW, HI}");
	test(AsString(parse("zZZzZZ")), "{ZZ, ZZ}");
	test(AsString(parse("-1 HO 2?-3-A a")), "{A a, 3, 1 HO 2?}");
}
