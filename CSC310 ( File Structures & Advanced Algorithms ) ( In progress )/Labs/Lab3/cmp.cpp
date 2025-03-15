#include<iostream>
#include<fstream>
#include<sys/stat.h>
#include<sys/types.h>
#include<cstring>
#include"cmp.h"

int main( int argc, char* argv[] ){

    ReturnInfo rInfo = processCommandLineInput( argc, argv );
    compareFiles( rInfo );

    return 0;
}

Flags processFlags( int argc, char* argv[] ){
    if( argc < 3 || argc > 6 ){
        cout << "Invalid number of arguments" << endl;
        exit(0);
    }
    Flags flags = { false, -1, 0 };
    if( strcmp(argv[1], "-c") == 0 ){
        flags.chars = true;
        flags.flagOffset = 1;
        if( strcmp(argv[2], "-i") == 0 ){
            if( argc == 3 ){
                cout << "No line number for the -i option" << endl;
                exit(0);
            }
            try{
                flags.n = atoi( argv[3] );
            }catch( const invalid_argument& e ){
                cout << argv[3] << " is not an integer" << endl;
                exit(0);
            }
            flags.flagOffset = 3;
        }
    }else if( strcmp( argv[1], "-i") == 0 ){
        try{
            flags.n = atoi( argv[2] );
        }catch( const invalid_argument& e ){
            cout << argv[2] << " is not an integer" << endl;
            exit(0);
        }
        flags.flagOffset = 2;
        if( strcmp(argv[3], "-c") == 0 ){
            flags.chars = true;
            flags.flagOffset = 3;
        }

    }
    for( int x = 0; x < argc; x++ )
        if( argv[x][0] == '-' )
            if( strcmp(argv[x], "-i") != 0  && strcmp(argv[x], "-c") != 0 ){
                cout << argv[x] << " is an illegal option. Only options allowed are -c and -i N" << endl;
                exit(0);
            }
    return flags;

}

ReturnInfo processCommandLineInput( int argc, char* argv[] ){
    Flags flags = processFlags( argc, argv );
    ReturnInfo rInfo{ flags, nullptr, nullptr };
    char* name1 = argv[ 1 + flags.flagOffset ];
    char* name2 = argv[ 2 + flags.flagOffset ];
    rInfo.name1 = name1;
    rInfo.name2 = name2;
    directoryAndExistsCheck(name1);
    directoryAndExistsCheck(name2);

    return rInfo;
}

void directoryAndExistsCheck( char* name ){
    struct stat buf;
    lstat (name, &buf);
    if (S_ISDIR(buf.st_mode)){
        cout << name << " is a directory and not a file" << endl;
        exit(0);
    }

    fstream in(name);
    if( !in ){
        cout << "file " << name << " does not exist" << endl;
        exit(0);
    }
}

void compareFiles( ReturnInfo rInfo ){
    ifstream in1(rInfo.name1, ios::in );
    ifstream in2(rInfo.name2, ios::in );
    in1.seekg(0);
    in2.seekg(0);
    char c1, c2;
    int line = 1, byte = 1;

    in1.ignore( rInfo.flags.n );
    in2.ignore( rInfo.flags.n );

    while(true){
        in1.get(c1);
        in2.get(c2);
        if( in1.eof() ){
            if( in2.eof() ){
                return;
            }else{
                cout << "cmp: EOF on " << rInfo.name1 << endl;
                return;
            }
        }else if( in2.eof() ){
            cout << "cmp: EOF on " << rInfo.name2 << endl;
            return;
        }
        if( c1 != c2 )
            break;
        if( c1 == '\n' )
            line++;
        byte++;
    }

    cout << rInfo.name1 << " " << rInfo.name2 << " differ: " << (rInfo.flags.chars ? "char " : "byte ") 
    << byte << ", line " << line;
    if( rInfo.flags.chars ){
        cout << " " << oct <<  (int) c1 << " " << c1;
        cout << " " << oct << (int) c2 << " " << c2;
    }
    cout << endl;
}
