#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <deque>
#include <stack>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <climits>
#include <set>
#include <map>
#include <numeric>
#include <ctime>
#include <functional>
#include <queue>
#include <iterator>
#include <locale>

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

template<class S,class T> ostream& operator << (ostream &os ,const pair<S,T>& a)
{
 os << "(" << a.first << ", " << a.second << ")";
 return os;
}

template <class T> T gcd(T a, T b)
{
	if (a < 0 && b < 0) return gcd(-a,-b);
	if (a == 0) return b;
	if (b == 0) return a;
	if (a > b) return gcd(b, a);
	if (b % a == 0) return a;
	return gcd(a, b % a);
}

/*
PASTE PROBLEM STATEMENT HERE
*/

// put solution here

int main()
{
  // put tests here
  test(foo(1, 2, 3, 4), "blahblah");
}
