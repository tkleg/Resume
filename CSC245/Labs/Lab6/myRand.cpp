
#include "Random.h"
#include "Sort.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int main( int argc, char* argv[] )
{
	Random R( time(0) );
	for( int i = 0; i <= atoi(argv[1]); i++ )
		cout << R.randomInt() % 101 << endl;
	
	return 0;
}
