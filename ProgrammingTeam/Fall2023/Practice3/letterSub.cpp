#include<iostream>
#include<string>
#include<vector>

using namespace std;

void processLines( int numLines );
void processLine( string& line, string key );
void processPair( string& line, char find, char replace );


int main(){

int numLines;
cin >> numLines;
string l;
getline( cin, l );
//numLines = stoi( l );

processLines( numLines );


return 0;
}

void processLines( int numLines ){
	
	if( numLines <= 0 )
		return;
	
	vector<string> results;
	string line;
	string key;
	for( int x = 0; x < numLines; x++ ){
		getline( cin, line );
		getline( cin, key );
		processLine( line, key ) ;
		results.push_back( line );
	
	}
	int size = results.size();
	for( int x = 0; x < size; x++ )
		cout << results[x] << endl;
}


void processLine( string& line, string key ){
	if( key.length() % 2 != 0 ){
		line  = "Wut";
		return;
	}
	int length = key.length();
	for( int index = 0; index < length; index += 2 )
		processPair( line, key[ index ], key[ index + 1 ] );

}

void processPair( string& line, char find, char replace ){
	int length = line.length();
	for( int index = 0; index < length; index ++ ){
		if( tolower( line[index] ) == tolower( find ) ){//equals ignore case
			if( tolower( line[index] ) == line[index] )//already lowercase
				line[index] = tolower( replace );
			else
				line[index] = toupper( replace );
		}
	}		

}
