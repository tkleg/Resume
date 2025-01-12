#include <iostream>
#include <fstream>

using namespace std;

bool kangaroo ( string s1 , string s2 );

string capitalize( string s );

int main(){
	
	ifstream infile("words.txt");
	
	int numPairs;
	infile >> numPairs;
	infile.ignore(1);

	string s1;
	string s2;

	for( int x = 0 ; x < numPairs; x++ ){
		getline( infile , s1 );
		s1 = capitalize( s1 );
		getline( infile , s2 );
		s2 = capitalize( s2 );
		if( kangaroo( s1, s2 ) )
			cout << s1 << " is a kangaroo word for " << s2 << endl;			else
			cout << s1 << " is not a kangaroo word for " << s2 << endl;
			
	}
	
	
}

bool kangaroo ( string s1, string s2 ){

	int prevIndex = -2; // prevIndex being -2 represents prevIndex not being changed
	int index = -2;
	for( int x = 0; x < s2.length(); x++ ){
		index = s1.find( s2[x] );
		if( index == -1 )
			return false;
		else if ( prevIndex >= index )
			return false;
		else
			prevIndex = index;
	}
	return true;
}

string capitalize( string s ){
	for( int x = 0 ; x < s.length(); x++ )
		s[x] = toupper( s[x] );
	return s;
}

