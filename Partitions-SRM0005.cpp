#include <vector>
#include <algorithm>
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
A nice order partition of positive integer n is a nonincreasing ordered
sequence of positive integers that sum to n.  For example, {6,2,1} is a nice
order partition of 9 and {10,3,3,2} is a nice order partition of 18 and {3} is
a nice order partition of 3.

Nice order partitions are ordered based on the following rule:

Partition A is before partition B if and only if there exists a positive
integer x such that
      A1 = B1 and A2 = B2 and . . . and A(x-1) = B(x-1) and Ax > Bx
where Pn is the nth integer in partition P (the i integers in the partition are
numbered 1 to i).

For example the partition {6,3,2,1} is before the partition {6,3,1,1,1} in the
ordered list of nice order partitions of 12.

Implement a class Partitions which contains a method getKthPartition.  The
method inputs two ints, n and k.  The method returns the kth unique nice order
partition of n, using the ordering rule above.  k=1 refers to the first
partition (Start counting at 1, not 0).  The partition is returned as an int[]
of the elements in the partition, where the element with index 0 of the int[]
is the first Integer in the partition, index 1 is the second, etc...

If k is larger than the number of partitions, the method should return an empty
instance of an int[] object.

The method signature is:
public int[] getKthPartition(int n, int k);

n and k satisfy:
  0 < n < 21
  0 < k < 1001

Note:
-The solution must run in under 6 seconds on TopCoder's tester.

Examples:
*If n=5 and k=2, the partitions, in order, are:
  {5}
  {4,1}
  {3,2}
  {3,1,1}
  {2,2,1}
  {2,1,1,1}
  {1,1,1,1,1}
  The 2nd one is {4,1} and the method should return {4,1} as an int[].
*If n=10 and k=7, the method should return {7,1,1,1}
*/

void addPartition(int v, int m, vector<int> prefix, vector<vector<int>>& results)
{
	if (v == 0)
	{
		results.push_back(prefix);
		return;
	}

	int ps = prefix.size();
	for (int i = min(m, v); i > 0; i--)
	{
		prefix.resize(ps);
		prefix.push_back(i);
		addPartition(v-i,i,prefix,results);
	}
}

vector<int> getKthPartition(int n, int k)
{
	vector<int> prefix;
	vector<vector<int>> results;
	addPartition(n, n, prefix, results);

	if ((vector<vector<int>>::size_type)(k-1) < results.size())
		return results[k-1];
	return prefix;
}

int main()
{
	test(AsString(getKthPartition(8,10)), "{4, 2, 2}");
	test(AsString(getKthPartition(1,1)), "{1}");
	test(AsString(getKthPartition(1,2)), "{}");
	test(AsString(getKthPartition(19,300)), "{6, 4, 3, 1, 1, 1, 1, 1, 1}");
	test(AsString(getKthPartition(15,150)), "{3, 3, 3, 3, 3}");
}
