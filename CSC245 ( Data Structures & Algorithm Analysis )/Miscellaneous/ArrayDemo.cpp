#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int main( )
{
	
	const int DIFFERENT_NUMBERS = 100;
	
	int totalNumbers;
	cout << "How many numbers to generate?: ";
	cin >> totalNumbers;

	vector<int> numbers( DIFFERENT_NUMBERS + 1 );

	for( int i = 0; i < numbers.size( ); i++ )
		numbers[ i ] = 0;

	for( int  j = 0; j < totalNumbers; j++ )
		numbers[ rand( ) % DIFFERENT_NUMBERS + 1 ]++;

	for( int  k = 1; k <= DIFFERENT_NUMBERS; k++ )
		cout << k << " occurs " << numbers[ k ]
			<< " time(s)\n";

	return 0;

}
