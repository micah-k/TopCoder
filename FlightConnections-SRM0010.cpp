#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

#define test(x, y) cout << #x << " = " << x << "(expected " << y << ")" << endl;

/*
Implement a class FlightConnections, which contains a method getMinimum.
getMinimum takes a String[] representing a list of available flights, a String
representing the departure city, and a String representing the intended
destination.  It returns the minimum number of flights needed to arrive from
the departure city to the destination city.

Note:
*If the departure city and the intended destination are the same, no flights
are needed, so return 0.
*If there is no possible connection from the departure city to the destination
city, return 0.
*If either the departure or arrival city is not mentioned in the String[],
return 0.
*City names are case sensitive.
*Departure and arrival times don't play any roll.
*Flights are directional.  That is if there is a flight from city A to city B
there isn't necessarily a flight in the reverse direction.
*Duplications in the String[] are ignored.
String[] elements are of the form:
"FROM, TO" (There is a comma followed by exactly one space between FROM and TO).
representing a flight from FROM to TO.  FROM and TO contain letters and dashes
('-').

Here is the method signature:
int getMinimum(String[] flights, String strDeparture, String strDestination);
Be sure your method is public.

* flights will be a String[] of the form above.  It has between 1 and 20
elements. Each element is at most 50 characters long.
* strDeparture and strDestination will be Strings consisting only of characters
from the set A-Z, a-z, and "-" (dash).

* TopCoder will check the validity of the inputs.
Examples(quotes are for clarity, but not included in the Strings):
   Flights: ["T, B", "O, F", "D, Y", "F, K", "K, C", "V, N", "B, O"]
   Departure From: T
   Destination: C
   Minimum flights: 5 (T to B; B to O; O to F; F to K; K to C)

   Flights: ["Y, C", "O, F", "Y, O", "M, O", "C, K", "O, K", "K, S", "K, M"]
   Departure From: Y
   Destination: Y
Minimum flights: 0 (the intended destination is the same as the departure
city)

   Flights: ["Here, Ba", "Ba, Ya", "Fa, Qa"]
   Departure From: Here
   Destination: Qa
   Minimum flights: 0 (no possible way to get from Here to Qa)
*/

int RouteMinimum(map<string, map<string, int>>& connections, string from, string to, int depth)
{
  if (from == to)
    return 0;

  if (depth < 0)
    return 500;

  if (connections.count(from) == 0)
    return 500;

  int result = 500;
  for(auto i = connections[from].begin(); i != connections[from].end(); i++)
    result = min(result, 1+RouteMinimum(connections, i->first, to, depth-1));

  return result;
}


int getMinimum(vector<string>& flights, string strDeparture, string strDestination)
{
  map<string, map<string, int>> connections;

  for (int i = 0; i < flights.size(); i++)
  {
    string str = flights[i];
    str.assign(str.begin(), remove(str.begin(), str.end(), ' '));
    auto result = find(str.begin(), str.end(), ',');
    string from = string(str.begin(), result++);
    string to = string(result, str.end());
    connections[from][to] = 1;
  }

  int result = RouteMinimum(connections, strDeparture, strDestination, flights.size()+1);
  return result > 250 ? 0 : result;
}


int main()
{
  vector<string> flights;

  char* set1[] = {"A, B", "K, A", "X, B", "R, G", "S, K", "Z, R", "K, I", "G, H", "B, Z", "U, O", "S, M"};
  flights.assign(set1, end(set1));
  test(getMinimum(flights, "S", "S"),	0);

  char* set2[] = {"C, K", "A, X", "V, T", "N, L", "B, N", "B, P", "F, Z", "V, H", "L, B", "A, V", "Z, Q", "F, G"};
  flights.assign(set2, end(set2));
  test(getMinimum(flights, "L", "X"),	0);


  char* set3[] = {"T, Y", "M, W", "Y, W", "C, Q", "S, A", "H, B", "V, Y", "Q, J", "T, B", "W, T", "V, C", "Y, G", "L, V"};
  flights.assign(set3, end(set3));
  test(getMinimum(flights, "T", "Y"),	1);

  char* set4[] = {"Y, H", "Q, M", "I, Z", "O, X", "D, Q", "S, A"};
  flights.assign(set4, end(set4));
  test(getMinimum(flights, "I", "U"), 0);


  char* set5[] = {"Hartford, New-York", "New-York, Atlanta", "New-York, Miami", "Miami, Seattle", "Hartford, New-York", "Seattle, Juan", "Atlanta, Juan"};
  flights.assign(set5, end(set5));
  test(getMinimum(flights, "Hartford", "Juan"), 3);

  char* set6[] = {"a, b", "c, d", "e, f", "g, h", "i, j", "k, l", "m, n", "o, p", "q, r", "s, t", "u, v", "w, x", "y, z", "aa, bb", "cc, dd", "ee, ff", "gg, hh", "ii, jj", "kk, ll", "mm, nn"};
  flights.assign(set6, end(set6));
  test(getMinimum(flights, "a", "s"), 0);

  char* set7[] = {"A, B", "B, C", "C, D", "E, F", "A, C"};
  flights.assign(set7, end(set7));
  test(getMinimum(flights, "A", "F"), 0);

  char* set8[] = {"A, B"};
  flights.assign(set8, end(set8));
  test(getMinimum(flights, "A", "B"), 1);

  char* set9[] = {"G, A", "C, F", "G, J", "J, L", "L, A", "G, L"};
  flights.assign(set9, end(set9));
  test(getMinimum(flights, "G", "A"), 1);

  char* set10[] = {"a, f", "a, g"};
  flights.assign(set10, end(set10));
  test(getMinimum(flights, "a", "e"), 0);

  char* set11[] = {"A, B", "B, C", "A, C"};
  flights.assign(set11, end(set11));
  test(getMinimum(flights, "A", "C"), 1);
}
