//#include <string>

using namespace std;

#include "dlist.h"
#include <iostream>
#include <string>
#include <sstream>

const int INVALID_ARG = -1;
const int VALID_ARG = 0;

const char INVALID_CHAR = '?';

void AccessItem( DList<int>& list );
void FindAndMove( DList<int>& list, int num );
void Delete( DList<int>& list );
void PrintList( const DList<int>& list );
void PrintLength( const DList<int>& list );
void HeadInsert( DList<int>& list );
void TailInsert( DList<int>& list );
char getOption();
int TryIntInput( int& num );
void PrintMenu();

int main(){

	DList<int> list;
	char sel;
		
	do
	{
		PrintMenu();
		sel = getOption();
		switch( toupper(sel) )
		{
			case 'H' : HeadInsert(list); break;
			case 'T' : TailInsert(list); break;
			case 'A' : AccessItem(list); break;
			case 'D' : Delete(list); break;
			case 'P' : PrintList(list); break;
			case 'L' : PrintLength(list); break;
			case 'Q' : cout << "\tExiting Program...\n"; break;
			default : cout << "\n\tError. Try Again. Please only enter one character. This includes no leading or following spaces" << endl;
		}
	}while ( toupper(sel) != 'Q' );




	return 0;
}


char getOption(){
	string line;
	getline( cin, line );
	if( line.length() != 1 )
		return INVALID_CHAR;
	else
		return line[0];
}

int TryIntInput( int& num ){
//this method was my first true attempt at c++ exception handling,
//obviously I chose the route that involved no actual exceptions
	string line = "";
	getline( cin , line );
	int length = line.length();
	string fixedLine = "";
	for( int x = 0; x < length; x++ ){
		if( isdigit( line[x] ) )
			fixedLine += line[x];
		else{
			cout << "\nPlease only enter an integer.\n";
			return INVALID_ARG;
		}
	}
	
	stringstream YayNoStoiIn98( fixedLine );
	if( YayNoStoiIn98 >> num )
		return VALID_ARG;
	else{
		cout << "\nPlease only enter an integer.\n";
		return INVALID_ARG;
	}

	return VALID_ARG;
}

void AccessItem( DList<int>& list ){
	if( list.isEmpty() ){
		cout << "\nThe list is empty.\n";
		return;
	}	
	cout << "\nPlease enter the integer you want to access: ";
	int num;
	if( TryIntInput( num ) == INVALID_ARG )
		return;
	FindAndMove( list , num );
}

void FindAndMove( DList<int>& list, int num ){
	if( list.inList( num ) ){
		list.deleteItem( num );
		list.insertHead( num );
	}else
		cout << endl << num << " is not in the list.\n";
}

void HeadInsert( DList<int>& list ){

	cout << "\nPlease enter the number you wish to insert at the front of the list.\n";
	int num;
	if( TryIntInput( num ) == INVALID_ARG )
		return;
	if( list.inList( num ) ){
		cout << num << " is already in the list.\n";
		return;
	}
	list.insertHead( num );
}

void TailInsert( DList<int>& list ){

        cout << "\nPlease enter the number you wish to insert at the back of the list.\n";
        int num;
        if( TryIntInput( num ) == INVALID_ARG )
		return;
	if( list.inList( num ) ){
                cout << num << " is already in the list.\n";
                return;
        }
        list.appendTail( num );
}


void Delete( DList<int>& list ){
	if( list.isEmpty() ){
		cout << "\nThe list is already empty.\n";
		return;
	}
	cout << "\nPlease enter the number you wish to remove from the list.\n";
        int num;
        if( TryIntInput( num ) == INVALID_ARG )
		return;
        if( list.inList( num ) )
		list.deleteItem( num );
	else
		cout << "\nThe integer " << num << " is not in the list.\n";

}

void PrintList( const DList<int>& list ){
	if( list.isEmpty() ){
                cout << "\nThe list is already empty.\n";
                return;
        }
	list.print();
}

void PrintLength( const DList<int>& list ){
	cout << "\nList length: " << list.lengthIs() << endl;
}

void PrintMenu(){
	string header = "\nEnter a letter corresponding to the command you want completed.";
	for( int x = 0 ; x < header.length(); x++ )
		cout << '-';
	cout << endl << header << "\n\n";
	cout << "H :\t Insert an integer at the start of the list.\n";
	cout << "T :\t Insert an integer at the back of the list.\n";
	cout << "A :\t Move a specific integer to the front of the list.\n";
	cout << "D :\t Delete an integer from the list.\n";
	cout << "P :\t Print out the list.\n";
	cout << "L :\t Print the list's length.\n";
	cout << "Q :\t Quit the program.\n";
	for( int x = 0 ; x < header.length(); x++ )
                cout << '-';
	cout << endl;

}
