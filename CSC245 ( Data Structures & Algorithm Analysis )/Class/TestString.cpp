#include <iostream>
#include <string>
using namespace std;

int main()
{

	string a = "hello";
	string b = "world";
	string c;

	c = a + " ";
	c += b;

	cout << "c is " << c << endl;
	
	cout << "c is: " << c.c_str() << endl;	
	cout << "c is: ";
	for ( int i = 0; i < c.length(); i++ )
		cout << c[i];
	cout << endl;

	return 0;

}
