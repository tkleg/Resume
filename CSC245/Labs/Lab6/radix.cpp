#include<iostream>
#include<vector>
#include<queue>
//#include"Random.h"
using namespace std;

int maxElemLength( const vector<int>& v );
int GetDigit( int number, int k );
vector< queue<int> > ItemsToQueues( const vector<int>& L, int k );
vector<int> QueuesToArray(vector< queue<int> >& L, int k );
void RadixSort( vector<int>& L, int numDigits );
void PrintVector( const vector<int> L, bool sortCall, int shakeNum );
void PrintQueues( vector< queue<int> > QA, int shakeNum );

int main(){
	int a[] = {380, 95, 345, 382, 260, 100, 492};
	vector<int> L( a, a+7 );
	/*vector<int> L;
	Random R( time(0) );
	for( int x = 0 ; x < 25; x++ )//fills the list with 25 random numbers between 0-9,999
		L.push_back( R.randomInt()%10000 );
	*/int maxLength = maxElemLength( L );
	RadixSort( L, maxLength );
	//PrintVector( L, false, 0 );

	return 0;
}

int maxElemLength(const vector<int>& v){
	int maxLength = 1;
	for( int x = 0; x < v.size(); x++ ){
		int length = 0;
		int num = v[x];
		do{
			num /= 10;
			length++;
		}while( num != 0 );
		if( length > maxLength )
			maxLength = length;
	}
	return maxLength;
}

int GetDigit( int number, int k ){
	for( int x = 0; x < k; x++ ){
		number /= 10;
		if( number == 0 )
			return 0;
	}
	return number % 10;
}

vector< queue<int> > ItemsToQueues( const vector<int>& L, int k ){
	vector< queue<int> > v(10);
	for( int x = 0; x < L.size(); x++ )
		v[ GetDigit( L[x], k ) ].push( L[x] );
	return v;
}	

vector<int> QueuesToArray( vector< queue<int> >& QA, int numVals ){
	vector<int> v;
	for( int x = 0; x < QA.size(); x++ )
		while( ! QA[x].empty() ){
			v.push_back( QA[x].front() );
			QA[x].pop();
		}
	return v;
}

void RadixSort( vector<int>& L, int numDigits ){
	vector< queue<int> > QA(10);
	for( int k = 0; k < numDigits; k++ ){
		QA = ItemsToQueues( L, k );
		PrintQueues( QA, k+1 );
		L = QueuesToArray( QA, L.size() );
		PrintVector( L, true, k+1 );	
	}
}

void PrintVector( const vector<int> L, bool sortCall, int shakeNum ){
//sortCall is true if called from the radixSort method. If not calling from RadixSort, any integer can be passed as shakeNum
	if( sortCall )
		cout << "Arrary After Shake #" << shakeNum << endl;
	cout << "Array = {";
	for( int x = 0; x < L.size()-1; x++ )
		cout << L[x] << ", ";
	cout << L[ L.size()-1 ]  << "}" << endl << endl;
}

void PrintQueues( vector< queue<int> > QA, int shakeNum ){
	cout << "Queue After Shake #" << shakeNum << endl;
	for( int x = 0; x < QA.size(); x++ ){
		if( QA[x].empty() )//makes sure non-empty queues are not printed
			continue;
		vector<int> L;
		while( ! QA[x].empty() ){
			L.push_back( QA[x].front() );
			QA[x].pop();
		}
		cout << "[" << x << "] = ";
		for( int x = 0; x < L.size(); x++ )
			cout << L[x] <<  " ";
		cout << endl;
	}
	cout << endl;
}
