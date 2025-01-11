#include <iostream>
#include <cstring>
#include <string>

using namespace std;

	const int BUFFER = 41;	

struct RecType{

	int age;
	float weight;
	char gender;

};

int main(){

	int num = 5;
	int *intPtr = NULL;
	intPtr = &num;
	*intPtr *= 10;
	string header1 = "intPtr points to :";
	cout << header1;
	int header1Length = header1.length();
	for( int x = 0; x < BUFFER - header1Length; x++ )
		cout << " ";
	cout << *intPtr << endl;

	
	RecType *recPtr = new RecType;
	recPtr -> age = 25;
	recPtr -> weight = 190;
	recPtr -> gender  = 'M';
	recPtr -> age += 5;
	string header2 = "Three Fields Pointed to By recPtr :";
	cout << header2;
	int header2Length = header2.length();
	for ( int x = 0; x < BUFFER - header2Length; x++ )
		cout << " ";
	cout << recPtr -> age << " " << recPtr -> weight << " " << recPtr -> gender << endl;


	char *strPtr = new char[50];
	strcpy( strPtr, "Operating Systems" );//don't understand why it isn't *strPtr and is instead strPtr
	int numLower = 0;
	int length = strlen( strPtr );//why does strPtr not need derefrencing
	string header3 = "strPtr points to :";
	cout << header3;
	int header3Length = header3.length();
	for ( int x = 0; x < BUFFER - header3Length; x++ )
		cout << " ";
	cout << strPtr << endl;
	for( int x = 0; x < length; x++ ){
		if( islower( *strPtr ) )
			numLower++;
		strPtr++;
	}
	string header4 = "LowerCase letters Pointed To By strPtr :";
	cout << header4;
	int header4Length = header4.length();
	for ( int x = 0; x < BUFFER - header4Length; x++ )
		cout << " ";
	cout << numLower << endl;


	strPtr -= length;//resets the pointer to the whole string
	strPtr += 10;
	string header5 = "Printing strPtr after adding 10 :";
	cout << header5;
	int header5Length = header5.length();
	for ( int x = 0 ; x < BUFFER - header5Length; x++ )
		cout << " ";
	cout << strPtr << endl;
	strPtr -= 10;
	delete[] strPtr;

}
