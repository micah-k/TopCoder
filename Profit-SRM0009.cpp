#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

#define test(x, y) cout << #x << " = " << x << "(expected " << y << ")" << endl;

/*
George owns a circus and brings his circus from town to town.  He knows how
much revenue he can take in on any day in a series of days in a town.  He also
knows the constant daily cost to run his circus.  George wants to bring his
circus to town for the series of days that results in the highest profit.

Implement a class Profit which contains a method maxProfit.  The method takes
an int and an int[] as parameters.  The int is the constant daily cost of
operating the circus.  The int[] contains elements representing the revenue the
circus will earn on given days. The 0th element of the int[] is "Day 1".  Index
1 is "Day 2", etc...  The method returns an int that is the maximum profit
George's circus can make by bringing the circus to town for a series of
sequential days that is a subset of the days in the int[].

For example, if the circus costs $20 a day to run, and the revenue per day is
{$18,$35,$6,$80,$15,$21}, George can make the most money by bringing his circus
to town from Day 2 to Day 4.  He will make (35+6+80)-(3*20) = $61.

Note:
-The series of days George brings his circus to town can be between 0 days and
the int[] size days, inclusive.
-If George brings his circus to town for 0 days, he makes 0 profit.

Here is the method signature:
int maxProfit(int perDayCost, int[] revenues);
Be sure your method is public.

perDayCost is a postive integer less than 1000.
revenues is a int[] of between 1 and 50 elements, inclusive.  Each element is a
positive integer less than 1000.

Examples:
*If perDayCost=20 and revenues={18,35,6,80,15,21}, the most money can be made
by bringing the circus to town from Day 2 to Day 4.  The method returns the
maximum profit, 61.
*If perDayCost=40 and revenues={30,20,10,38}, George will make no money by
bringing his circus to the town, so George will bring his circus to town for 0
days and make 0 profit.  The method returns 0.
*If perDayCost=10 and revenues={30,20,10,38}, George will make the most money
by bringing his circus to town for all four days.  The method returns the
profit, 58.
*/

int maxCrossing(vector<int>& revenues, int base, int mid, int left, int right)
{
	int leftsum = -60000;
	int sum = 0;
	int maxleft = -1;
	for (int i = mid; i >= left; i--)
	{
		sum = sum + revenues[i] - base;
		if (sum > leftsum)
		{
			leftsum = sum;
			maxleft = i;
		}
	}
	int rightsum = -60000;
	int maxright = -1;
	sum = 0;
	for (int i = mid+1; i <= right; i++)
	{
		sum = sum + revenues[i] - base;
		if (sum > rightsum)
		{
			rightsum = sum;
			maxright = i;
		}
	}

	return leftsum+rightsum;
}

int maxSubProfit(vector<int>& revenues, int base, int left, int right)
{
	if (left == right)
		return revenues[left] - base;

	int mid = (left + right) / 2;

	int maxleft = maxSubProfit(revenues, base, left, mid);
	int maxright = maxSubProfit(revenues, base, mid+1, right);
	int maxcross = maxCrossing(revenues, base, mid, left, right);
	return max(maxleft, max(maxright, maxcross));
}

int maxProfit(int perDayCost, vector<int>& revenues)
{
	int val = maxSubProfit(revenues, perDayCost, 0, revenues.size()-1);
	return (val > 0) ? val : 0;
}

int main()
{
	vector<int> revenues;

	int set1[] = {100, 100, 10, 10, 10};
	revenues.assign(set1, end(set1));
	test(maxProfit(30, revenues), 140);

	int set2[] = {100};
	revenues.assign(set2, end(set2));
	test(maxProfit(20, revenues), 80);

	int set3[] = {509, 59};
	revenues.assign(set3, end(set3));
	test(maxProfit(20, revenues), 528);

	int set4[] = {10, 10, 10, 100, 100};
	revenues.assign(set4, end(set4));
	test(maxProfit(30, revenues), 140);

	int set5[] = {20};
	revenues.assign(set5, end(set5));
	test(maxProfit(5, revenues), 15);

	int set6[] = {6, 10, 11, 11, 10, 8};
	revenues.assign(set6, end(set6));
	test(maxProfit(12, revenues), 0);

	int set7[] = {101, 101, 102, 300, 350, 100, 103};
	revenues.assign(set7, end(set7));
	test(maxProfit(100, revenues), 457);

	int set8[] = {80, 50, 90, 100, 30, 10, 5, 1, 1};
	revenues.assign(set8, end(set8));
	test(maxProfit(70, revenues), 50);

	int set9[] = {65, 60, 70, 10, 10, 10, 10, 70, 70, 70};
	revenues.assign(set9, end(set9));
	test(maxProfit(60, revenues), 30);

	int set10[] = {1, 1, 1, 999, 1, 1, 999, 1};
	revenues.assign(set10, end(set10));
	test(maxProfit(12, revenues), 1952);

	int set11[] = {100};
	revenues.assign(set11, end(set11));
	test(maxProfit(10, revenues), 90);

	int set12[] = {30};
	revenues.assign(set12, end(set12));
	test(maxProfit(10, revenues), 20);

	int set13[] = {40, 10, 10};
	revenues.assign(set13, end(set13));
	test(maxProfit(20, revenues), 20);

	int set14[] = {2};
	revenues.assign(set14, end(set14));
	test(maxProfit(1, revenues), 1);

	int set15[] = {50};
	revenues.assign(set15, end(set15));
	test(maxProfit(20, revenues), 30);

	int set16[] = {20, 9, 20};
	revenues.assign(set16, end(set16));
	test(maxProfit(10, revenues), 19);

	int set17[] = {50};
	revenues.assign(set17, end(set17));
	test(maxProfit(10, revenues), 40);

	int set18[] = {2, 10, 10, 11};
	revenues.assign(set18, end(set18));
	test(maxProfit(5, revenues), 16);
}
