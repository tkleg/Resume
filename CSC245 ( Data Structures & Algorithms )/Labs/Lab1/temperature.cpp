#include <iostream>
using namespace std;

double convert( double value );

int main(){

	cout << "Please enter a Celcius value: ";
	double celc = 0;
	cin >> celc;
	cout << celc << " degrees Celcius is " << convert( celc ) << " degrees Fahrenheit." << endl;

}

double convert( double celc ){
	return 1.8 * celc + 32;
} 
