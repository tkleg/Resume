#include<string>
using namespace std;

struct Flags{
    bool chars;
    int n;
    int flagOffset;
};
//used for returning multiple oiece of information from the processFlags function

struct ReturnInfo{
    Flags flags;
    char * name1;
    char * name2;
};
//used for returning multiplce piece of information from processCommandLineInput and passing it onto compareFiles 

void compareFiles( ReturnInfo rInfo );
/*
pre-conditions: rInfo has been filled with two valid file names and a Flags struct
post-conditions: cmp is ran on the two file's who's name are in the parameter struct and the flag information
*/

ReturnInfo processCommandLineInput( int argc, char* argv[] );
/*
pre-conditions: none
post-conditions: a struct is returned containing information on the two options available as well as the two file names to be cmp'd together
*/

Flags processFlags( int argc, char* argv[] );
/*
pre-conditions: none
post-conditions: a struct is returned which contains a bool for whetehr or not the c option was selected, the number of bytes to skip,
    and the offset in the argv array to get to the filename
*/

void directoryAndExistsCheck( char* name );
/*
pre-conditions: none
post-conditions: if name is the name of a directory or a non-existent file then an appropriate message is printed before exiting the program
*/
