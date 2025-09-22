#include "commandLineProcessor.h"

void printCommandLineOutput( commandLineOutput output ){
    cout << "option: ";
    switch(output.option){
        case pack: cout << "pack"; break;
        case unpack: cout << "unpack"; break;
        case list: cout << "list"; break;
        case help: cout << "help"; break;
        default: cout << "error";
    }
    cout << endl << "numArgs = " << output.numArgs << endl << "input: ";
    for( int x = 0; x < output.numArgs; x++ )
        cout << output.args[x] << ", ";
    cout << endl;
}

commandLineOutput processCommandLine(int argc, char* argv[]){
    if( argc < 2 ){
        cout << "jtar: You must specify one of the options\nTry `jtar --help' for more information." << endl;
        exit(0);
    }
    commandLineOutput output = { pack, argc-2, new char*[argc-2] };
    output.option = pickOption( argc, argv[1] );
    if( output.option == help )
	return output;
    for( int x = 2; x < argc; x++ ){
        output.args[x-2] = new char[strlen(argv[x]) + 1];
        if( output.option != pack || x != 2 )
            existsCheck( argv[x] );
        int argLen = strlen( argv[x] );
        if( argv[x][ argLen - 1 ] == '/' )
            argv[x][ argLen - 1 ] = '\0';
        strcpy(output.args[x-2], argv[x]);
    }
    return output;
}

tarOption pickOption(int argc, char* optionArg){
    string invalidFormat = "jtar: Invalid format\nTry 'jtar --help' for more information.";

    if( strcmp("-cf", optionArg) == 0 ){
        if( argc < 4 ){
            cout << invalidFormat << endl;
            exit(0);
        }
        return pack;
    }else if( strcmp("-tf", optionArg) == 0 ){
        if( argc != 3 ){
            cout << invalidFormat << endl;
            exit(0);
        }
        return list;
    }else if( strcmp("-xf", optionArg) == 0 ){
        if( argc != 3 ){
            cout << invalidFormat << endl;
            exit(0);
        }
        return unpack;
    }else if( strcmp("--help", optionArg) == 0 )
        return help;
    else if( optionArg[0] == '-' ){
        cout << "jtar: Invalid option (" << optionArg << ")\nTry 'jtar --help' for more information." << endl;
        exit(0);
    }else{
        cout << "jtar: You must specify one of the options\nTry `jtar --help' for more information." << endl;
        exit(0);
    }
}

void existsCheck( char* name ){

    struct stat buf;
    lstat (name, &buf);
    if (S_ISDIR(buf.st_mode))
        return;

    fstream in(name);
    if( !in ){
        cout << "jtar: \"" << name << "\" does not exist." << endl;
        exit(0);
    }
    in.close();
}
