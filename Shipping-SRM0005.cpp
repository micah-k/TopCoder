#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

#define test(x, y) cout << #x << " = " << x << "(expected " << y << ")" << endl;

/*
Tom's Shipping Company is a marine based shipping company.  The Company has W
warehouses on shores throughout the world.  The warehouses are referred to by
number and are numbered 0 to W-1.  There are regular direct trips (call them
legs) between certain pairs of warehouses. Each leg has a distance in miles and
a cost in dollars per ton-mile.  Each leg is bidirectional (if there is a leg
from 0 to 1, there is an identical leg from 1 to 0).

Customers request to ship cargo of a specified weight from one warehouse to
another warehouse.

Tom's Shipping Company is looking to rip off its customers as severely as
possible.  It does this by finding the series of legs that results in the
highest cost.  However, the series of legs cannot result in the cargo visiting
the same warehouse more than once - this would allow the customers realize they
were being ripped off.  The cost of shipping cargo on each leg is the weight of
the cargo multiplied by the length of the leg multiplied by the cost (per
weight-distance) of shipping on the leg.  The total cost of shipping the cargo
is the sum of the cost of shipping the cargo on each leg the cargo goes on.

Tom's Shipping Company has hired you to write a program to help them rip off
their customers.

Implement a class Shipping, which contains a method mostExpensive.  This method
takes as parameters:
an int: the number of warehouses
an String[]: the leg data - contains info on the two warehouses at either end
of the leg, the distance of the leg, and the cost of shipping cargo on the leg
an int: warehouse number customer wants to ship from
an int: warehouse number customer wants to ship to
an int: weight of the cargo in tons
The method returns an int that is the highest possible price in dollars Tom's
Shipping Company can charge.

The elements in the String[] are of the form (the quotes are for clarity, but
are not included in the actual elements):
"W1 W2 LENGTH COST" where W1 and W2 are integers that are the two warehouses at
either end of the leg, LENGTH is the integer length of the leg, in miles, and
COST is the integer cost in dollars per ton-mile of shipping on that leg.  Note
there is exactly 1 space between each of the 4 integers.

If there is no possible series of legs to get the customers cargo from the
requested starting warehouse to the requested ending warehouse, the method
returns -1.
If the data is invalid, the method returns -1.  Data is invalid if:
*any String[] element is not of the exact correct form.
*the elements in the String[] refer to non-existent warehouses.  That is, the
warehouse number is greater than or equal to the number of warehouses.
*two elements in the String[] refer to the same leg.  For instance "1 0 1 1"
and "0 1 1 1" (remember legs are bidirectional).
*the length of a leg is greater than 1000 or less than or equal to 0.
*the cost is greater than 20 or less than or equal to 0.
*the customer's request refers to non-existent warehouses.

The method signature is:
public int mostExpensive(int numWarehouses,String[] legs,int shipFrom,int
shipTo,int cargoWeight);

numWarehouses is less than 20 and greater than 0.
legs has less than 100 elements in it, each element a String with length less
than 100.
shipFrom and shipTo are greater than or equal to 0 and less than 19.
cargoWeight is greater than 0 and less than 100.

Note:
-If a customer requests to ship cargo from a warehouse to itself, the method
should return 0.
-Solution must run in under 6 seconds on TopCoder's tester.
-A leg from a warehouse to itself can be ignored because the cargo would visit
the same warehouse twice.  However, data including a leg from a warehouse to
itself is not necessarily invalid.

Examples:
*If numWarehouses=4, legs={"0 1 8 2","0 2 1 1","3 0 6 3","1 2 8 3","1 3 10
10","3 2 2 4"}, shipFrom=0, shipTo=2, and weight=1, the route with the highest
cost is 0->3->1->2, and the method should return the highest cost: 1*6*3 +
1*10*10 + 1*8*3 = 142.
*/

int maxCost(int from, int to, vector<bool> visited, const vector<vector<int>>& routes)
{
	if (from == to) return 0;

	int bestCost = -1;
	for(vector<vector<int>>::size_type i = 0; i < routes.size(); i++)
	{
		if (routes[from][i] != -1 && visited[i] != true)
		{
			visited[i] = true;
			int cost = maxCost(i, to, visited, routes);
			visited[i] = false;

			if (cost > -1) bestCost = max(bestCost, routes[from][i] + cost);
		}
	}
	return bestCost;
}

int mostExpensive(int numWarehouses, vector<string>& legs, int shipFrom, int shipTo, int cargoWeight)
{
	vector<bool> visited(numWarehouses, false);
	vector<vector<int>> routes(numWarehouses, vector<int>(numWarehouses, -1));

	for(vector<string>::size_type i = 0; i < legs.size(); i++)
	{
		int W1 = -1, W2 = -1, LENGTH = -1, COST = -1;
		stringstream ss;
		ss << legs[i];
		ss >> W1 >> W2 >> LENGTH >> COST;

		if (W1 < 0 || W1 > numWarehouses - 1) return -1;
		if (W2 < 0 || W2 > numWarehouses - 1) return -1;
		if (routes[W1][W2] != -1 || routes[W2][W1] != -1) return -1;
		if (LENGTH > 1000 || LENGTH < 1) return -1;
		if (COST > 20 || COST < 1) return -1;

		routes[W1][W2] = routes[W2][W1] = LENGTH * COST;
	}

	if (shipFrom < 0 || shipTo < 0 || shipFrom > numWarehouses - 1|| shipTo > numWarehouses - 1)return -1;
	if (shipFrom == shipTo) return 0;

	visited[shipFrom] = true;
	int cost = maxCost(shipFrom, shipTo, visited, routes);
	if (cost > -1) return cargoWeight * cost;
	return -1;
}

int main()
{
	vector<string> legs;

	char* set1[] = {"1 1 10 12", "2 3 14 14"};
	legs.assign(set1, end(set1));
	test(mostExpensive(10, legs, 1, 1, 10), 0);

	char* set2[] = {"0 1 2 3", "1 2 4 6", "0 4 10 12", "4 2 3 3", "2 3 8 12", "3 4 4 5", "0 3 1 1"};
	legs.assign(set2, end(set2));
	test(mostExpensive(5, legs, 0, 3, 10), 2250);

	char* set3[] = {"1:2 3 4"};
	legs.assign(set3, end(set3));
	test(mostExpensive(10, legs, 1, 2, 1), -1);

	char* set4[] = {"0 1 1 1", "1 2 1 1", "2 3 1 1", "0 3 1 1", "3 3 1 1"};
	legs.assign(set4, end(set4));
	test(mostExpensive(4, legs, 0, 3, 1), 3);

	char* set5[] = {"1 2 3 4", "2 9 10 2"};
	legs.assign(set5, end(set5));
	test(mostExpensive(10, legs, 0, 7, 2), -1);
}
