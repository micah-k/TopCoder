#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

#define test(x, y) cout << #x << " = " << x << "(expected " << y << ")" << endl;

/*
Implement a class PegJump, which contains a method maxJump.  maxJump is passed
an int[] of peg locations (Integers) on a peg jumping game board and returns an
int that is the maximum possible number of successive jumps.

The peg jumping game board is a triangle with 10 holes, numbered 0 through 9:
      0
     / \
    1 - 2
   / \ / \
  3 - 4 - 5
 / \ / \ / \
6 - 7 - 8 - 9
Peg Jumping Game Rules:
1. A peg can only move by jumping another peg.
2. A peg can jump another peg (call the pegs "jumper peg" and "jumpee peg",
respectively) if there is a single line connecting the jumper and jumpee peg
locations and there is a single line of identical direction connecting the
jumpee peg location to an empty location.
3. The jumper peg is removed from its original location, and the original
location is left empty.
4. The jumper peg ends up in the empty location immediately beyond the jumpee
peg along the line of identical direction as the line connecting the original
jumper hole to jumpee hole.
5. The jumpee peg is removed and its location is left empty.
6. The game ends when no more pegs can be jumped.

For example, if there is a peg in 0, a peg in 1 and no peg in 3, the 0 peg can
jump the 1 peg.  The peg in 1 is removed, the peg in 0 ends up in 3, and 0 and
1 are left empty.  However, if there are pegs in 0, 1, & 3, and no peg in 4,
the 0 peg cannot jump the 1 peg and end up in 4, because the line from 1 to 4
is not of the same direction as the line from 0 to 1.

The method simulates the game and performs jumps in an order that results in
the maximum possible number of jumps before the game is over, and returns this
maximum number of jumps.

The method signature is:
public int maxJump(int[] pegLoc);

pegLoc is an int[] of size at most 10.  It contains Integers (between 0 and 9,
inclusive) representing initial locations of pegs.  Duplicates are ignored.
For example, if there are initially pegs in locations 1, 2, 3, and 7, pegLoc
may equal {7,2,3,1}.

Note: Any correct solution must execute in fewer than 6 seconds on our tester.
Examples:
-If the initial peg locations are {0,2,4,7}, the sequence that results in the
maximum number of jumps is:
  0 jumps 2, ends in 5.
  7 jumps 4, ends up in 2.
  5 jumps 2, ends up in 0.
  There are three jumps, and the method should return 3.
-if pegLoc={0,2,3,4,5,8}, the method should return 4.
*/

struct jump
{
	int jump1;
	int jump2;
	int land1;
	int land2;
};

static jump s_jumptable[] = {
	{ 1, 2, 3, 5},
	{ 3, 4, 6, 8},
	{ 4, 5, 7, 9},
	{ 1, 4, 0, 5},
	{-1,-1,-1,-1},
	{ 2, 4, 0, 3},
	{ 3, 7, 1, 8},
	{ 4, 8, 2, 9},
	{ 7, 4, 6, 1},
	{ 8, 5, 7, 2}
};

int maxJump(vector<bool>& pegLoc)
{
	int best = 0;
	for (int i = 0; i < 10; i++)
	{
		if (pegLoc[i] == true)
		{
			if (s_jumptable[i].jump1 > 0 && pegLoc[s_jumptable[i].jump1] == true && pegLoc[s_jumptable[i].land1] == false)
			{
				pegLoc[i] = false;
				pegLoc[s_jumptable[i].jump1] = false;
				pegLoc[s_jumptable[i].land1] = true;
				best = max(best, 1 + maxJump(pegLoc));
				pegLoc[i] = true;
				pegLoc[s_jumptable[i].jump1] = true;
				pegLoc[s_jumptable[i].land1] = false;
			}
			if (s_jumptable[i].jump2 > 0 && pegLoc[s_jumptable[i].jump2] == true && pegLoc[s_jumptable[i].land2] == false)
			{
				pegLoc[i] = false;
				pegLoc[s_jumptable[i].jump2] = false;
				pegLoc[s_jumptable[i].land2] = true;
				best = max(best, 1 + maxJump(pegLoc));
				pegLoc[i] = true;
				pegLoc[s_jumptable[i].jump2] = true;
				pegLoc[s_jumptable[i].land2] = false;
			}
		}
	}
	return best;
}

int main()
{
	vector<bool> pegs;

	pegs.assign(10, false);
	test(maxJump(pegs), 0);

	pegs.assign(10, false);
	pegs[1] = pegs[4] = pegs[9] = pegs[5] = pegs[9] = pegs[0] = true;
	test(maxJump(pegs), 4);

	pegs.assign(10, false);
	pegs[2] = pegs[4] = pegs[5] = pegs[6] = pegs[7] = true;
	test(maxJump(pegs), 4);

	pegs.assign(10, false);
	pegs[0] = pegs[1] = pegs[2] = pegs[3] = pegs[4] = pegs[5] = pegs[6] = pegs[7] = true;
	test(maxJump(pegs), 7);

	pegs.assign(10, false);
	pegs[0] = pegs[1] = pegs[2] = pegs[3] = pegs[5] = pegs[6] = pegs[7] = pegs[9] = true;
	test(maxJump(pegs), 6);
}
