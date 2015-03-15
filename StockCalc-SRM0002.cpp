#include <vector>
#include <iostream>

using namespace std;

#define test(x, y) cout << #x << " = " << x << "(expected " << y << ")" << endl;

/*
Implement a class StockCalc, which contains a method getProfit.  This method
takes an int[] representing the stock price for a given stock on a sequence of
days, and returns, as an int, the maximum profit that can be reaped by buying
on one of those days and selling on a later day.

Here is the method signature:
public int getProfit(int[] prices);

prices is an int[].  Each Integer must be greater than 0 and less than 1000.
There must be at least 1 element in the int[] and at most 100 elements.

Note:
-If no profit can be made, return 0.

Examples:
-prices={3,5,10,20,80,70,40,1}, returns 77
-prices={80,70,40,3,2,1}, returns 0
*/
#define max(a, b) (a > b) ? a : b;
int getProfit(vector<int>& v)
{
	int result = 0;

	for(vector<int>::size_type min = 0; min < v.size() - 1; min += 1)
	{
		for(vector<int>::size_type max = min + 1; max < v.size(); max += 1)
		{
			result = max(v[max] - v[min], result);
		}
	}
	return result;
}

int main()
{
	int set1[] = {1};
	test(getProfit(vector<int>(set1, set1+1)), 0);

	int set2[] = {10, 9, 8, 7, 6};
	test(getProfit(vector<int>(set2, set2+5)), 0);

	int set3[] = {59, 40, 70, 80, 90, 200};
	test(getProfit(vector<int>(set3, set3+6)), 160);

	int set4[] = {1, 3, 8, 10, 20, 14, 12, 1, 17};
	test(getProfit(vector<int>(set4, set4+9)), 19);

	int set5[] = {2, 3, 8, 1, 99, 8};
	test(getProfit(vector<int>(set5, set5+6)), 98);
}
