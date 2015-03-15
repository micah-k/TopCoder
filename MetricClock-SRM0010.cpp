#include <string>
#include <iostream>
#include <sstream>

using namespace std;

#define test(x, y) cout << #x << " = " << x << "(expected " << y << ")" << endl;

/*
Class Name: MetricClock
Method Name: convertToMetric
Parameters: String
Returns: String

Implement a class MetricClock, which contains a method convertToMetric.
convertToMetric takes a String in the form "HH:MM:SS" (where HH is between 00
and 23, MM is between 00 and 59 and SS is between 00 and 59) representing the
current time of day according to standard clocks (in military time), and
returns a String in the form "H:MM:SS" (where H is between 0 and 9, MM is
between 00 and 99, and SS is between 00 and 99) representing the current time
of day according to the metric clock.

According to the metric clock, there are 10 metric hours in a day, 100 metric
minutes in a metric hour, and 100 metric seconds in a metric minute.  There are
86400 standard seconds in a day, thus 86400 standard seconds make up 1 metric
day (100000 metric seconds).  The metric clock day starts at 0:00:00 and ends
at 9:99:99.

When converting to the metric clock, partial seconds are always truncated, not
rounded.  (9:20:38.833... returns 9:20:38.)

Here is the method signature:
public String convertToMetric(String strStandardTime);

strStandardTime is of the form above.

Examples:
Given the String "01:45:17", the method returns "0:73:11"
Given the String "03:17:45", the method returns "1:37:32"
Given the String "08:12:22", the method returns "3:41:92"
Given the String "12:00:00", the method returns "5:00:00"
Given the String "12:15:21", the method returns "5:10:65"
Given the String "19:58:59", the method returns "8:32:62"
Given the String "23:59:59", the method returns "9:99:98"
*/

string convertToMetric(string strStandardTime)
{
	stringstream ss;
	int hours, minutes, seconds, matches = sscanf(strStandardTime.c_str(), "%d:%d:%d", &hours, &minutes, &seconds);
	if (matches == 3)
	{
		int mHrs, mMins, mSecs;
		int i = (hours * 60 * 60) + (minutes * 60) + seconds;
		mHrs = static_cast<int>((i / 86400.0) * 100000.0);
		mSecs = mHrs % 100;
		mHrs /= 100;
		mMins = mHrs % 100;
		mHrs /= 100;

		ss << mHrs << ":" << mMins << ":" << mSecs;
	}
	else
	{
		ss << "Error";
	}
	return ss.str();
}

int main()
{
  test(convertToMetric("01:45:17"), "0:73:11");
  test(convertToMetric("03:17:45"), "1:37:32");
  test(convertToMetric("08:12:22"), "3:41:92");
  test(convertToMetric("12:00:00"), "5:00:00");
  test(convertToMetric("12:15:21"), "5:10:65");
  test(convertToMetric("19:58:59"), "8:32:62");
  test(convertToMetric("23:59:59"), "9:99:98");
}
