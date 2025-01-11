#include<vector>
#include<iostream>
#include<string>
using namespace std;

string prefixes( string word );
string suffixes( string word );
int spaceIndex( string word, string suffix );
bool endsWith( string parent, string child );

int main( int argc, char* argv[] ){
	int numLines;
	cin >> numLines;
	string words[numLines];	
	for( int x=0; x < numLines; x++ ){
		cin >> words[x];
		words[x] = prefixes( words[x] );
	}
	for( int x = 0; x < numLines; x++ )
		cout << words[x] << endl;
	return 0;
}

string prefixes( string word ){
	if( word.substr(0,4) == "anti" )
		return "against " + word.substr(4);
	if( word.substr(0,4) == "post" )
		return "after " + word.substr(4);
	if( word.substr(0,3) == "pre" )
		return "before " + word.substr(3);
	if( word.substr(0,2) == "re" )
		return word.substr(2) + " again";
	if( word.substr(0,2) == "un" )
		return "not " + word.substr(2);
	return word;	
}

string suffixes( string word ){
	string suffixes[5] = { "er", "ing", "ize", "tion", "s" };
	for( int x = 0; x < 5; x++ )
		if( word.find( suffixes[x] ) <= 100 ){
//			int spaceIndex = getSpaceIndex( word, suffixes[x] );
		}
	return "";
}

int spaceIndex( string word, string suffix ){	
	if( endsWith( word, "again" ) ){
		int wordAlone = word.susbtr(0,word.length()-6);
		
	}
		
		return -1;
	return 0;
}

bool endsWith( string parent, string child ){
	if( child.length() > parent.length() )
		return false;
	return parent.substr( parent.length()-child.length(), child.length() ) == child;
}
