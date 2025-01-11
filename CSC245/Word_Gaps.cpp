#include <iostream>
#include <fstream>
using namespace std;

void processLine ( string line, int lineNum );

int main(){
	
	ifstream infile("infile.in");
	int numLines;
	//string numLinesTemp;
	infile >> numLines;
	infile.ignore(1); //this line accounts for the end line character on the first line
	//numLines = stoi(numLinesTemp);
	string line;
	for( int lineNum = 1; lineNum <= numLines; lineNum++ ){
		getline( infile, line );
		processLine( line , lineNum ); 
	}
}

void processLine( string line, int lineNum ){

	int spaces = 0;
	
	for( int x = 0; x < line.size(); x++ )
		if( line[x] == ' ' )
			spaces++;

	int words = spaces + 1;
	int charsNoSpaces = line.length() - spaces;
	int gapWidth = ( 80 - charsNoSpaces ) / ( words - 1 );

	cout << "Line " << lineNum << ":  words=" << words << " chars=" << charsNoSpaces << " gap width=" << gapWidth << endl;

}
		
