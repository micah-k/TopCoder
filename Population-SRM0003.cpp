#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

#define test(x, y) cout << #x << " = " << x << "(expected " << y << ")" << endl;

/*
Implement a class Population, which contains a method getPop.  getPop simulates
the building and abandoning of living quarters in a city.  It takes as
parameters an int that is the number of years to run the simulation and a
String[] of coordinates representing the initial locations of living quarters
within the city.  getPop returns the number of living quarters in the city
after the specified number of years.

The city is a 10x10 grid.  Each square in the grid can contain 0 or 1 living
quarters.  The squares are referred to by coordinates of the form (int,int)
where the first int ranges from 0 to 9 and represents the North/South position
and the second int ranges from 0 to 9 and represents the East/West position.
Each square can have up to 8 neighbors (i.e. north, south, east, west,
north-west, north-east, south-west, and south-east).

The program should simulate the building and abandoning of the living quarters
based on the following rules:
1.   Each living quarter that starts a year with two or three neighboring
quarters lasts the year.
2.   Each living quarter that starts a year with four or more neighbors is
abandoned (disappears) due to over-population during the year.
3.   Each living quarter that starts a year with one or zero neighbors is
abandoned (disappears) due to isolation during the year.
4.   Each empty location that starts a year adjacent to exactly three neighbors
will have a living quarter built on it during the year.

The method signature is:
public int getPop(int years, String[] locations);

-years ranges from 0 to 10, inclusive.
-location consists of strings of the form "int,int" where both ints range from
0 to 9, inclusive.  "3,2" is an example of a valid element.  "2.3 , 3.1" is not
valid because there are spaces and non-integers.  location has from 0 to 100
elements, inclusive.  Duplicate elements are ignored.
-Duplicates in locations should be ignored.

Note:
-If the input year is 0, the method should return the initial population.

Example (the quotes in the String[] below are for clarification, and should not
be part of your input):
-if years=3 and locations={"5,4","4,5","6,6","6,7","5,5","4,4"}
 After year 1, there are living quarters at: {"4,4","4,5","5,4","6,5","6,6"}
 After year 2: {"4,4","4,5","5,4","5,6","6,5"}
 After year 3: {"4,4","4,5","5,4","5,6","6,5"}
 And the method should return 5.
-if years=4 and locations={"0,0","1,0","0,1"}, the method should return 4.
*/

int countNeighbors(const vector<vector<bool>>& grid, int x, int y)
{
	int count = 0;
	if (x - 1 >= 0)
	{
		if (y - 1 >= 0)
			count += grid[x-1][y-1] ? 1 : 0;
		count += grid[x-1][y] ? 1 : 0;
		if (y + 1 < 10)
			count += grid[x-1][y+1] ? 1 : 0;
	}
	if (y - 1 >= 0)
		count += grid[x][y-1] ? 1 : 0;
	if (y + 1 < 10)
		count += grid[x][y+1] ? 1 : 0;
	if (x + 1 < 10)
	{
		if (y - 1 >= 0)
			count += grid[x+1][y-1] ? 1 : 0;
		count += grid[x+1][y] ? 1 : 0;
		if (y + 1 < 10)
			count += grid[x+1][y+1] ? 1 : 0;
	}
	return count;
}

int getPop(int years, vector<string> locations)
{
	int result = 0;
	vector<vector<bool>> grid(10, vector<bool>(10, false));
	for(vector<string>::size_type loc = 0; loc < locations.size(); loc++)
	{
		int x, y;
		stringstream ss(locations[loc]);
		ss >>  x;
		ss.ignore(1);
		ss >> y;

		grid[x][y] = true;
		result++;
	}

	for(int i = 0; i < years; i++)
	{
		result = 0;
		vector<vector<bool>> newgrid(10, vector<bool>(10, false));
		for(int x = 0; x < 10; x++)
		{
			for (int y = 0; y < 10; y++)
			{
				int neighbors = countNeighbors(grid, x, y);
				if (neighbors == 2)
				{
					if (grid[x][y] == true)
					{
						newgrid[x][y] = true;
						result++;
					}
				}
				else if (neighbors == 3)
				{
					newgrid[x][y] = true;
					result++;
				}
				else
				{
					newgrid[x][y] = false;
				}
			}
		}
		grid = newgrid;
	}

	return result;
}

int main()
{
	vector<string> locs;
	test(getPop(3, locs), 0);

	char* set[] = {"3,4", "3,5", "3,6", "4,3", "4,4", "4,5", "4,6", "4,7", "5,4", "5,5", "5,6", "9,9", "9,8", "8,9"};
	locs.assign(set,end(set));
	test(getPop(8, locs), 4);

	char* set2[] = {"0,0", "2,5", "3,5", "4,7", "5,7", "0,1", "2,6", "3,7", "5,5", "7,1", "1,0", "2,7", "4,5", "5,6", "7,2", "7,2", "0,1"};
	locs.assign(set2,end(set2));
	test(getPop(2, locs), 14);

	char* set3[] = {"1,1", "3,3", "5,5"};
	locs.assign(set3,end(set3));
	test(getPop(0, locs), 3);

	char* set4[] = {"3,4", "3,5", "3,6", "4,4", "4,6", "5,4", "5,5", "5,6"};
	locs.assign(set4,end(set4));
	test(getPop(10, locs), 12);
}
