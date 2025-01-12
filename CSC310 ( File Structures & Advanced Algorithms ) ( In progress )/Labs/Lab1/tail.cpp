#include<fstream>
#include<iostream>
using namespace std;

void moveToStart( fstream & inOut, int numLines );

int main(int argc, char *argv[]){
    int numLines = -1*atoi(argv[1]);
    string filename = argv[2];
    fstream inOut (filename.c_str(), ios::in | ios::out);
    moveToStart( inOut, numLines );
    string line;
    while( getline(inOut, line) ){
        cout << line;
        if( !inOut.eof() )//prevents a newline printing after the last line of the file
            cout << endl;
    }
    return 0;
}

void moveToStart( fstream & inOut, int numLines ){
    char ch;
    inOut.seekg(0, ios::end);
    for( int count = 0; count < numLines; count++ ){
        while( ch != '\n' ){
            //-2 because after each inOut.get call we are 2 chars/bytes in front of the next char/byte to check
            inOut.seekg( -2, ios::cur );
            inOut.get(ch);
            if( inOut.tellg() <= 1 ){//true if we reach the start of the file and should still pull more lines
                if( count == 0 ){//for single line files
                    //cout << "inner if" << endl;
                    inOut.clear();
                    inOut.seekg(0);
                    string line;
                    getline(inOut, line);
                    cout << line;
                    exit(0);
                }
                inOut.seekg( -1, ios::cur );
                return;
            }
        }
        //at this point we are looking one ahead of the newline char so we go 2 back to the last char of the previous line
        inOut.seekg( -2, ios::cur );
        inOut.get(ch);
    }
    //at this point we are at the new line before the line we want to start printing on so we move forwrad 1
    inOut.seekg(1, ios::cur);
}
