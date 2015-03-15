#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

#define test(x, y) cout << #x << " = " << x << "(expected " << y << ")" << endl;

/*
Ed is an over achieveing, over active college student.  He wants to be in as
many clubs as possible.   Each club has a meeting time, and in order to be in a
club, Ed has to attend the club's meeting, in its entirety.  Each club meets
weekly, one day a week.  Also, being the overachiever he is, Ed has invented a
teleportation system so the time it takes him to get from meeting to meeting is
negligable.  That is, if one club's meeting ends at 10:00 and another club's
meeting starts at 10:00, Ed can be in both clubs.

Implement a class Schedule which contains a method maxClubs.  maxClubs takes a
String[] as a parameter.  The String[] contains the times of clubs' meetings.
The method returns an int that is the maximum number of clubs Ed can be in.

Each element in the String[] represents one club's information and is a String
of the form:
"CLUBNAME d hh:mm LENGTH". (The quotes are for clarity and are not part of the
String).
CLUBNAME is the name of the club and consists of only letters (at least 1 and
at most 20).
d is the day of the meeting.  It is a number from 1 to 7.  1 is Sunday, 2 is
Monday ... 7 is Saturday.
hh:mm is the starting time of the club's meeting, in military time.  It
consists of two numerical digits representing the hour, a colon, and two more
numerical digits representing the minute.  The hour is between 00 and 23,
inclusive.  The minute is between 00 and 59, inclusive.
LENGTH is the length of the meeting in hours.  The length of the meeting is an
integer between 1 and 24, inclusive.

Note:
-There is exactly one space beween CLUBNAME and d, between d and hh:mm, and
between hh:mm and LENGTH.
-Club names are not necessarily unique.
-The solution must run in under 6 seconds on TopCoder's tester.
-If the String[] is empty, Ed can be in 0 clubs.

The method signature is:
public int maxClubs(String[] meetingtimes);

meetingtimes has at most 14 elements.  Each element is a String of the form
given above (TopCoder will check this).

Examples:
If meetingtimes={"MATHTEAM 2 11:00 3","CHESSCLUB 2 12:00 1","FIGURESKATING 2
13:00 2"}, Ed can maximize the number of clubs he is in by being in CHESSCLUB
and FIGURESKATING and the method returns the maximum number of clubs he can be
in: 2.
*/

struct meeting
{
	string name;

	int day;
	int hour;
	int minute;
	int duration;

	meeting(string data)
	{
		stringstream ss;
		ss << data;
		ss >> name >> day >> hour;
		ss.ignore(1);
		ss >> minute >> duration;
		day--;
	}

	int startminute() { return minute + (60 * hour) + (60 * 24 * day); }
	int endminute() { return (startminute() + (duration * 60)) % (60 * 24 * 7); }

	static bool conflicts(meeting a, meeting b)
	{
		if (b.startminute() < a.startminute()) return conflicts(b, a);
		if (a.endminute() > b.startminute()) return true;
		if (b.endminute() < b.startminute() && b.endminute() > a.startminute()) return true;
		return false;
	}
};

int calcMax(vector<meeting> schedule, vector<meeting> available)
{
	int maxClubs = 0;
	if (available.size() > 0)
	{
		meeting m = available.back(); available.pop_back();
		maxClubs = calcMax(schedule, available);

		bool fConflict = false;
		for(vector<meeting>::size_type i = 0; i < schedule.size(); i++)
			fConflict = fConflict || meeting::conflicts(m, schedule[i]);

		if (fConflict == false)
		{
			schedule.push_back(m);
			maxClubs = max(maxClubs, 1 + calcMax(schedule, available));
		}
	}
	return maxClubs;
}

int maxClubs(vector<string> meetingtimes)
{
	vector<meeting> schedule;
	vector<meeting> meetings;

	for(vector<string>::size_type i = 0; i < meetingtimes.size(); i++)
		meetings.push_back(meeting(meetingtimes[i]));

	return calcMax(schedule, meetings);
}

int main()
{
	vector<string> schedule;

	char* set1[] = {"A 7 15:00 24", "Bb 1 02:00 1"};
	schedule.assign(set1, end(set1));
	test(maxClubs(schedule), 1);

	char* set2[] = {"aaa 2 10:00 1", "bbb 2 10:30 1", "aaa 2 11:00 1", "ccc 2 11:15 1", "ddd 2 12:00 1"};
	schedule.assign(set2, end(set2));
	test(maxClubs(schedule), 3);

	schedule.clear();
	test(maxClubs(schedule), 0);

	char* set3[] = {"A 4 10:00 24", "B 5 02:00 1", "C 5 03:00 2", "D 5 02:01 1", "E 6 10:30 1"};
	schedule.assign(set3, end(set3));
	test(maxClubs(schedule), 3);

	char* set4[] = {"O 1 10:00 1", "X 2 12:00 1", "Z 3 23:00 3", "N 4 23:01 1", "ZZ 5 00:01 2"};
	schedule.assign(set4, end(set4));
	test(maxClubs(schedule), 5);
}
