#include <vector>
#include <iostream>

using namespace std;

#define test(x, y) cout << #x << " = " << x << "(expected " << y << ")" << endl;

/*
Willy the Worm is crawling through a 5x5 grid.  The squares in the grid are
numbered 0 through 24, from left to right, top to bottom:

 0  1  2  3  4
 5  6  7  8  9
10 11 12 13 14
15 16 17 18 19
20 21 22 23 24

Some of the squares contain obstacles.

What is the maximum number of squares Willy can visit before he gets stuck?

Willy travels through the grid as follows:

-He always starts on square 0, going either down or right.
-He can move in four directions: up, down, left, right.
-He cannot travel through:
  (a) an obstacle
  (b) a square he has previously visited
-He moves in a straight line until he reaches a square he can not travel
through or the edge.
-When he cannot move straight, he turns either left or right.
-When he cannot move left, right, or straight, he stops.

Implement a class Obstacle, which contains a method getLongestPath.
getLongestPath is passed an int[] of elements that are the squares which have
obstacles in them, and returns an int that is the maximum number of squares
Willy can visit before he stops.

Examples:
-If the obstacles int[] is {4,12,15,23}, the longest path Willy can travel is:
 0->5->10->11->16->21->22->17->18->19->14->9->8->7->6->1->2->3
 In this path, Willy travels through 18 squares, so the method should return 18.
-If obstacles is {4,10,11,12,14}, the method should return 14

The method signature is:
public int getLongestPath(int[] obstacles);

obstacles is an int[] of elements between 1 and 24, inclusive (0 can not
contain an obstacle).

Note:
-Your algorithm must run in under 6 seconds.
-If Willy cannot move anywhere to start (obstacles on squares 1 and 5), he has
still visited square 0 and the method should return 1.
*/

inline int mod(int a, int b) { return (a + b) % b; }
inline int max(int a, int b) { return (a > b) ? a : b; }
inline int getx(int pos) { return mod(pos, 5); }
inline int gety(int pos) { return pos / 5; }
inline int getpos(int x, int y) { if (x < 0 || x > 4) return -1; if (y < 0 || y > 4) return -1; return y * 5 + x; }

inline int GetNeighbor(int pos, int direction)
{
	direction = mod(direction, 4);
	switch(direction)
	{
	case 0: return getpos(getx(pos), gety(pos) - 1);
	case 1: return getpos(getx(pos) + 1, gety(pos));
	case 2: return getpos(getx(pos), gety(pos) + 1);
	default: return getpos(getx(pos) - 1, gety(pos));
	}
}

inline bool IsBlocked(int pos, unsigned long map)
{
	return (pos == -1) ? true : ((map & (0x1 << pos)) == (0x1 << pos));
}

inline void Block(int pos, unsigned long& map) { map |= (0x1 << pos); }

int longestPath(int pos, int direction, unsigned long map)
{
	if (IsBlocked(GetNeighbor(pos, direction), map)) return 1;

	int length = 0;
	int newpos = pos;
	while (IsBlocked(GetNeighbor(newpos, direction), map) == false)
	{
		Block(newpos, map);
		newpos = GetNeighbor(newpos, direction);
		length++;
	}

	return length + max(longestPath(newpos, direction-1, map), longestPath(newpos, direction+1, map));
}

int getLongestPath(vector<int> obstacles)
{
	unsigned long map = 0;

	for(vector<int>::size_type i = 0; i < obstacles.size(); i++)
		map |= (0x1 << obstacles[i]);

	return max(longestPath(0, 1, map), longestPath(0, 2, map));
}

int main()
{
	vector<int> obstacles;

	int set1[] = {4, 10, 11, 14};
	obstacles.assign(set1, end(set1));
	test(getLongestPath(obstacles), 18);

	int set2[] = {5, 1, 7, 8};
	obstacles.assign(set2, end(set2));
	test(getLongestPath(obstacles), 1);

	obstacles.clear();
	test(getLongestPath(obstacles), 25);

	int set4[] = {11, 22, 4, 7};
	obstacles.assign(set4, end(set4));
	test(getLongestPath(obstacles), 17);

	int set5[] = {21, 9, 12, 6};
	obstacles.assign(set5, end(set5));
	test(getLongestPath(obstacles), 5);
}
