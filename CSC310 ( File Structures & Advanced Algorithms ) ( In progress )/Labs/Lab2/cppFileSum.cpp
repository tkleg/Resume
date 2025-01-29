#include<iostream>
#include<fstream>
using namespace std;

int intSum( istream & infile );
int readInts( istream & infile, int & curSum );

int main(int argc, char* argv[]){
    filebuf buf;
    buf.open(argv[1], ios::in);
    istream infile(&buf);
    cout << intSum( infile ) << endl;
}

int intSum( istream & infile ){
    //whileReturn = 1 (comma), 2 (end of file), 3 (invalid char)
    int curSum = 0, whileReturn = 1;
    while( true ){
        whileReturn = readInts( infile, curSum );
        if( whileReturn == 1 ){
            infile.clear();
            infile.ignore(1); //lets the read head go over the comma
        }else if( whileReturn == 2 )
            return curSum;
        else
            return -1;
    }
}

int readInts( istream & infile, int & curSum ){
    int i;
    char ch;
    
    while( infile >> i ){
        if( i < 0 )
            return 3;
        curSum += i;
        ch = infile.peek();
    }
    if( infile.eof() )
        return 2;
    else if( ch == ',' ){
        return 1;
    }
    else
        return 3;

}