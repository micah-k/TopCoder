#include <string>
#include <iostream>

using namespace std;

#define test(x, y) cout << #x << " = " << x << "(expected " << y << ")" << endl;

/*
Implement a class DNA, which contains a method getComplement. getComplement
takes a String representing a strand of DNA and returns the complement of that
strand, as a String.

DNA is composed of the following four bases: adenine, guanine, thymine, and
cytosine.  Two strands of DNA are considered complements of each other if all
of the following conditions are met:
     -   they are of equal length
-   for each adenine in the first strand, a thymine is located in the
exact same position of the second strand
-   for each thymine in the first strand, an adenine is located in the
exact same position of the second strand
-   for each guanine in the first strand, a cytosine is located in the
exact same position of the second strand
-   for each cytosine in the first strand, a guanine is located in the
exact same position of the second strand

In both the input String and return String, let A stand for adenine, T for
thymine, C for cytosine and G for guanine and let each character in the String
represent a position in the DNA strand.

Here is the method signature:
String getComplement(String strStrand);
Be sure your method is public.

* strStrand has length 1 to 50, inclusive.
* strStrand contains only the characters 'A', 'T', 'C', and 'G'.

Examples:
* If the input is "GAAACT", the method should return "CTTTGA"
* If the input is "ACCAAAAGCTGCAGTATGA", the method should return
"TGGTTTTCGACGTCATACT"
* If the input is "TAGGTCTCACTTAGCTTTCGTCCCTATAGTATATAGCTCCCAACCATCCA", the
method should return "ATCCAGAGTGAATCGAAAGCAGGGATATCATATATCGAGGGTTGGTAGGT"
*/

string getComplement(string strStrand)
{
  string result;
  for(string::size_type i = 0; i < strStrand.size(); i++)
  {
    switch(strStrand[i])
    {
    case 'A': result.push_back('T'); break;
    case 'C': result.push_back('G'); break;
    case 'G': result.push_back('C'); break;
    default: result.push_back('A'); break;
    }
  }
  return result;
}

int main()
{
  test(getComplement("ATCG"), "TAGC");
  test(getComplement("TTTTTTTTA"), "AAAAAAAAT");
  test(getComplement("CCAA"), "GGTT");
  test(getComplement("TGTG"), "ACAC");
  test(getComplement("ATC"), "TAG");
  test(getComplement("AT"), "TA");
}
