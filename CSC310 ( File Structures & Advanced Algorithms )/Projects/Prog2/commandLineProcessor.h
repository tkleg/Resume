enum tarOption{ pack, unpack, list, help};

struct commandLineOutput{
    tarOption option;
    int numArgs;
    char** args;
};

commandLineOutput processCommandLine(int argc, char* argv[]);
//pre-conditions: none
//post-conditions: if an error occured it is printed and the program exits. Otherwise a struct is returned containing the tar option selected, the number of arguments, and the arguments passed

tarOption pickOption(int argc, char* optionArg);
//pre-conditions: the user entered at least one option in the command line
//post-conditions: a tarOption is returned if the user properly selected one. Otherwise an error is printed and the program exits

void printCommandLineOutput( commandLineOutput output );
//pre-conditions: output is filled with values
//postconditions: prints the commandLineOuput in an organized manner
//Note: this is not used but I kept it as it is useful for debugging 

void existsCheck( char * name );
//preconditions: none
//post-conditions: none if the name is a path to a file or directory that exists. An error is printed if it does not exist