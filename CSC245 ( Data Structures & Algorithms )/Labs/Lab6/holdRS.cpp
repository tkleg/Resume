#include<iostream>
#include<vector>
#include<queue>
#include<string>
using namespace std;

int maxElemLength( const vector<string>& v );
vector< queue<string> > ItemsToQueues( const vector<string>& L, int k );
vector<string> QueuesToArray(vector< queue<string> >& L, int k );
void RadixSort( vector<string>& L, int numDigits );
void PrintVector( const vector<string>& L );
void prepStrings( vector<string>& L, int maxLength );
void unpadStrings( vector<string>& L );

int main(){
	string a[] = {"zebra", "apple", "orange", "can", "candy", "a", "top", "pumpkin", "today", "parade"};
	int aLen = sizeof(a)/sizeof(a[0]);//looks an awful lot like the sytnax of getting the number of elements in a word or dword array in assembly
	vector<string> L(a, a+aLen);
	int maxLength = maxElemLength( L );
	prepStrings( L, maxLength );
	RadixSort( L, maxLength );
	unpadStrings( L );
	PrintVector( L );	

	return 0;
}

void prepStrings( vector<string>& L, int maxLength ){
	for( int x= 0 ; x < L.size(); x++ )//sets all letters to lowercase
                for( int y = 0; y < L[x].length() ; y++ )
                        L[x][y] = tolower( L[x][y] );
	
	for( int x = 0; x < L.size(); x++ )//adds null characters to the end of each string until it is the maxLength
                while( L[x].length() < maxLength )
                        L[x] += '\0';	
}

void unpadStrings( vector<string>& L ){
	for( int x = 0 ; x < L.size(); x++ )
		while( L[x].length() > 0 && L[x][ L[x].length()-1 ] == '\0' )
			L[x] = L[x].substr(0, L[x].length()-1);
}

int maxElemLength(const vector<string>& v){
	int maxLength = 0;
	for( int x = 0; x < v.size(); x++ )
		if( v[x].length() > maxLength )
			maxLength = v[x].length();
	return maxLength;
}

int GetAscii( string s, int k ){
	return (int) s[ s.length()-1-k ];
}

vector< queue<string> > ItemsToQueues( const vector<string>& L, int k ){
	vector< queue<string> > v(128);
	for( int x = 0; x < L.size(); x++ )
		v[ GetAscii( L[x], k ) ].push( L[x] );
	return v;
}	

vector<string> QueuesToArray( vector< queue<string> >& QA, int numVals ){
	vector<string> v;
	for( int x = 0; x < QA.size(); x++ )
		while( ! QA[x].empty() ){
			v.push_back( QA[x].front() );
			QA[x].pop();
		}
	return v;
}

void RadixSort( vector<string>& L, int numChars ){
	vector< queue<string> > QA(128);
	for( int k = 0; k < numChars; k++ ){
		QA = ItemsToQueues( L, k );
		L = QueuesToArray( QA, L.size() );
	}
}

void PrintVector( const vector<string>& L ){
	cout << "Array = { ";
	for( int x = 0; x < L.size()-1; x++ )
		cout << L[x] << ", ";
	cout << L[ L.size()-1 ] << " }" << endl;
}
