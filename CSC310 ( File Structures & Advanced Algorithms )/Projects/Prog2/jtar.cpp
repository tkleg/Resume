#include "includes.h"
#include "file.cpp"
#include "commandLineProcessor.cpp"
#include "jtar.h"

int main(int argc, char* argv[]){
    commandLineOutput output = processCommandLine( argc, argv );
    processCommand( output );
    return 0;
}

void runTf( char* tarName  ){
    fstream tarIn( tarName, ios::in | ios::binary );
    tarIn.seekg(0);
    int numFiles;
    tarIn.read( (char *) &numFiles, sizeof(int) );
    File f;
    for( int x = 0; x < numFiles; x++ ){
        tarIn.read( (char *) &f, sizeof(f) );
        cout << f.getName() << endl;
        if( ! f.isADir() )//prevents file contents from being read in as metadata
            tarIn.ignore( atoi(f.getSize().c_str()) );
    }
}

void writeTar( char* tarName, vector<File> files ){
    fstream tarOut(tarName, ios::out | ios::binary);
    int size = files.size(), filesize;
    tarOut.write( (char *) &size, sizeof(int) );
    File f;
    for( int x = 0; x < size; x++ ){
        f = File( files[x] );
        tarOut.write( (char *) &f, sizeof(f) );
        if( f.isADir() )//prevents data from being written out for directories with the exception of their respective headers
            continue;
        fstream fileIn(f.getName(), ios::in | ios::binary );
        filesize = atoi(f.getSize().c_str());
        char * fileData = new char[ filesize ];
        fileIn.read( fileData, filesize );
        tarOut.write( fileData, filesize );
    }
    tarOut.close();
}

void runXf( char* tarName ){
    int numFiles;
    fstream tarIn(tarName, ios::in | ios::binary);
    tarIn.read( (char *) &numFiles, sizeof(int) );
    File files[numFiles];
    char ch;
    File f;
    for( int x = 0; x < numFiles; x++ ){
        tarIn.read( (char *) &f, sizeof(f) );
        files[ numFiles - x - 1 ] = File(f);
        if( f.isADir() ){
            if( ! dirExists(f.getName().c_str()) ){//prevents directories that exist from being recreated
                string command = "mkdir " + f.getName();
                system( command.c_str() );
            }
        }else{
            int filesize = atoi(f.getSize().c_str());
            fstream fileOut(f.getName(), ios::out );
            filesize = atoi(f.getSize().c_str());
            char * fileData = new char[ filesize ];
            tarIn.read( fileData, filesize );
            fileOut.write(fileData, filesize );
            fileOut.close();
        }
    }
    tarIn.close();
    //this has to be a seperate loop because after a directory is created its files are created, altering the directory's modify time
    //by going entering the files backwards into the array we are ensuring that every directory has its metadata set after the meta data of its chlidren are set
    for( int x = 0; x < numFiles; x++ )
        setMetaData( files[x] );
}

void setMetaData( File f ){
    string command = "touch -mt " + f.getStamp() + " " + f.getName();
    system( command.c_str() );
    command[7] = 'a';
    system( command.c_str() );
    command = "chmod " + f.getPmode() + " " + f.getName();
    system( command.c_str() );
}

bool dirExists( const char * dirName ){
    string command = "stat " + string(dirName) + " &> dirHelp";//"&>" redirects bash's stdout and stderr to the file. '&' is necessary because '>' alone only redirects stdout.
    system(command.c_str());
    fstream dirChecker("dirHelp", ios::in );
    string in;
    dirChecker >> in;
    dirChecker.close();
    system("rm dirHelp");
    //"stat:" is everything before the first whitespace from the stat command output when stat there is an error with a stat call.
    //In a normal call that would be used in this program for a file that exists it is "File:"
    return in != "stat:";
}

string toString(const File f){
    string s = "";
    s += "name: " + f.getName() + ", ";
    s += "pmode: " + f.getPmode() + ", ";
    s += "size: " + f.getSize() + ", ";
    s += "stamp: " + f.getStamp() + ", ";
    s += "isDir: " + string((f.isADir() ? "true" : "false"));
    return s;
}

void runCf( commandLineOutput output ){
    vector<char*> paths;
    for( int x = 1; x < output.numArgs; x++ ){
       listAll(output.args[x], paths);
    }
    vector<File> files;
    int fullsize;
    for( int x = 0; x < paths.size(); x++ ){
        File f = runStat( paths[x] );
        files.push_back( f );
    }
    writeTar( output.args[0], files );
    system("rm statOutput*");//deletes statOutput and statOutputHelp
}

void listAll( string s, vector<char*>& paths ){
    const char* constc = s.c_str();
    char* cname = new char[s.length()+1];
    strcpy(cname, constc);
    paths.push_back(cname);
    if( isDir( cname ) ){
        strcat(cname, "/");
        string command = "ls " + s + " > lsHelp";
        system( command.c_str() );
        string c;
        vector<char*> children;
        fstream lsIn("lsHelp", ios::in);
        while( getline(lsIn, c) ){
            constc = c.c_str();
            cname = new char[strlen(constc)+1];
            strcpy(cname, constc);
            children.push_back(cname);
        }
        lsIn.close();
        for( int x = 0; x < children.size(); x++ )
            listAll( s + "/" + string(children[x]), paths );
    }
}

File runStat( char* path ){
    string command = "stat " + string(path) + " > statOutput";
    system( command.c_str() );
    File f( path,  getProtection(path), getSize(path), getTime(path) );
    if( isDir( path ) )
        f.flagAsDir();
    return f;
}

char* getTime( char* path ){
    string timeHelp;
    system("cat statOutput | head -n +6 | tail -n -1 | tr -s ' ' | cut -d ' ' -f2-3 | tr -s ':' '-' | tr -s ' ' '-' | cut -d '.' -f1 | tr -d '-' > statOutputHelp");
    fstream statStream( "statOutputHelp", ios::in );
    statStream.seekg(0);
    statStream >> timeHelp;
    statStream.close();
    timeHelp = timeHelp.substr(0, 12) + "." +  timeHelp.substr(12, 2);
    char* time = new char[16];
    strcpy(time, timeHelp.c_str());
    return time;
}

char* getSize( char* path ){
    char* size = new char[7];
    system("cat statOutput | head -n +2 | tail -n -1 | tr -s ' ' | cut -d ' ' -f3 > statOutputHelp");
    fstream statStream( "statOutputHelp", ios::in );
    statStream.seekg(0);
    statStream >> size;
    statStream.close();
    return size;
}

char* getProtection( char* path ){
    char* protection = new char[5];
    system("cat statOutput | head -n +4 | tail -n -1 | tr -s ' ' | cut -c 10-13 > statOutputHelp");
    fstream statStream( "statOutputHelp", ios::in );
    statStream.seekg(0);
    statStream >> protection;
    statStream.close();
    return protection;
}

bool isDir( char* path ){
    string command = "stat " + string(path) + " | head -n +2 | tail -n -1 | tr -s ' ' | tr ' ' '\n' | tail -n -1 > statOutput";
    system( command.c_str() );
    string type;
    fstream statStream( "statOutput", ios::in );
    statStream.seekg(0);
    statStream >> type;
    statStream.close();
    return type == "directory";
}

void processCommand( commandLineOutput output ){
    switch(output.option){
        case help:
            cout << "`jtar' saves many files together into a single tape or disk archive,\nand can restore individual files from the archive.\n\nUsage: tar [OPTION]... [FILE]...\n\nOption Examples:\ntar -cf archive.tar foo bar  # Create archive.tar from files foo and bar.\ntar -tf archive.tar          # List all files in archive.tar verbosely.\ntar -xf archive.tar          # Extract all files from archive.tar.\nReport bugs to <11035376@live.mercer.edu>." << endl;
            break;
        case pack:
            runCf( output );
            break;
        case unpack:
            runXf( output.args[0] );
            break;
        case list:
            runTf( output.args[0] );
    }
}
