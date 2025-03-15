void processCommand( commandLineOutput output );
//pre-conditions: the command line output has been created
//post-conditions: the command specified by the command line is executed

File runStat( char* path );
//pre-conditions: the path is a path for a valid file or directory. The commandLineProcessor file has a function which runs before this to check that a file exists
//post-conditions: a file is returned according to the path provided

bool isDir( char* path );
//pre-conditions: the path is a path to a valid file or directory
//post-conditoins: true if the file at the path location is a directrory and false if it is not a directory

char* getProtection( char* path );
//pre-conditions: path is a path to a valid file file or directory
//post-conditions: the pmode is returned. the pointer points to a char[] of length 5

char* getSize( char* path );
//pre-conditions: path is a path to a valid file file or directory
//post-conditions: the size of the file at the path locatoin is returned. the pointer poitns to a char[] of length 7

char* getTime( char* path );
//pre-conditions: path is a path to a valid file file or directory
//post-conditions: the time is returned in the format yyyymmddhrmi.ss for easy use by the touch command

void listAll( string s, vector<char*>& paths );
//pre-conditions: s is a path that leads to a valid file or directory
//post-conditions: s is added to paths, if s is a directory a / is appended to the end of it for use in paths. If s is a directory then this is also applied recursively to the directory contents

void runCf( commandLineOutput output );
//pre-conditions: output is filled with comamnd line output containing only paths that are valid files paths to a file or directory. The file of output.option must be the enum value tarOption.pack.
//post-conditions: a tar file is created based on the tar filename and the other file names in output.args

void writeTar( char* tarName, vector<File> files );
//pre-conditions: files has been filled with the Files to be written out to the tar file and tarName is not null
//post-conditoins: a tar file with name tarName is written according to the files inside of the files vector

void runTf( char* tarName );
//pre-conditions: tarName is the name of a tarfile that exists
//post-conditions: the path of every file and directory stored in the tarfile named tarName are printed to the console

void runXf( char* tarName );
//pre-conditions: tarName is the name of a tarfile that exists
//post-conditions: all of the files in the tarfile named tarName are recreated. The access and modify times as well as the pmode are also altered to match what is saved in the tarfile

string toString( File f );
//pre-conditions: f is a File filled with data
//post-conditions: a string representation of the file is returned
//Note: this is not used in the final version of the program but I wanted to keep it since it is a useful debugging tool

bool dirExists( const char * dirName );
//pre-conditions: dirName is not null
//post-conditions: true is returned if dirName points to a directory that currently exists. false is returned otherwise

void setMetaData( File f );
//pre-conditions: f contains a file that exists in the location specified by its name
//post-conditions: the access time, modify time, and the protection mode of the file are set to the values specific in the file object