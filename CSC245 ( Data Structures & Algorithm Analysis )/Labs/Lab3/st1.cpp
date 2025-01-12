#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>

using namespace std;

void initialize( vector<int>& v );
void Print( vector<int> v );
void Reverse( vector<int>& v );

int main(){

	stack<string> s1, s2;
	
	s1.push("Hi there");

	s1.push("this is hurting my head, lmao");
	s1.push("hola, como estas?");
	s2.push("please dont crash");
	s2.push("this probably won't crash because it probably won't compile, YAAAYYYY");

	if( s1.size() > s2.size() )
		cout << "s2 < s1" << endl;
	else if( s2.size() > s1.size() )
		cout << "s1 < s2" << endl;
	else
		cout << "s1 == s2" << endl;

	vector<int> v;
	initialize( v );
	Print( v );
	Reverse( v );
	sort( v.begin(), v.end() );
	Print( v );
}


void initialize( vector<int>& v ){
	int i;
	for( int x = 0; x < 5; x ++ ){
		cin >> i;
		v.push_back( i );
	}
}

void Print( vector<int> v ){
	for( int x = 0 ; x < v.size() ; x++ )
		cout << v[x] << " ";
	cout << endl;
}

void Reverse( vector<int>& v ){
	int size = v.size();
	for ( int x = 0 ; x < size/2 ;  x++ ){
		int temp = v[x];
		v[x] = v[ size - x - 1 ];
		v[ size - x - 1 ] = temp;
	}
}
