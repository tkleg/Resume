
#include <string>
#include <iostream>
using namespace std;

void BreakDown (string name, string& first, string& last, string& mi);
int main()
{
	string name, first, last, mi;

	cout << "Name? <Last, First MI.> ";
	getline (cin, name);
		
	BreakDown (name, first, mi, last);

	cout << "First Name Entered :  " << first << endl;
	cout << "Last Name Entered :  " << last << endl;
	cout << "Middle Initial Entered :  " << mi << endl;
	return 0;
}

void BreakDown (string name, string& first, string& mi, string& last)
{
	// pre  : name is initialized with a full name
	// post : first, mi, and last contain the individual components
        //        of that name
	int commaIndex = name.find(",");
	last = name.substr(0, commaIndex );
	int secondSpace = name.find(" ", commaIndex+2 );
	int firstStart = commaIndex + 2;
	first = name.substr( firstStart, secondSpace-firstStart );
	mi += name[ secondSpace + 1 ];
	
	return;



} 
