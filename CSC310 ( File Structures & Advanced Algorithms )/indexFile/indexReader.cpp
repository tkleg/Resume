#include<fstream>
#include<iostream>
using namespace std;

int main( int argc, char* argv[] ){
    fstream fileIn(argv[1], ios::in );
    fileIn.seekg(0);
    int totalFrag = 0, totalSize;
    int size, location;
    char record, flag;
    fileIn >> totalSize;
    while( fileIn.peek() != '*' ){
        fileIn >> record >> location >> size >> flag;
        cout << record << " " << location << " " << size << " " << flag << endl;
        if( flag == '-' )
            totalFrag += size;
    }
    fileIn.close();
    cout << totalFrag << " unused bytes " << endl;
    printf( "%.2f%% of bytes unused\n", (totalFrag*100.0/totalSize) );
    return 0;
}