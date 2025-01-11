#include<fstream>
#include<iostream>
#include<cstring>
using namespace std;

void processFlags( int argc, char *argv[], bool & cBytes, bool & wWords, bool & lLines );
void processOneFlag( bool & cBytes, bool & wWords, bool & lLines, char flag1[] );
void processTwoFlags( bool & cBytes, bool & wWords, bool & lLines, char flag1[], char flag2[] );
void processThreeFlags( bool & cBytes, bool & wWords, bool & lLines, char flag1[], char flag2[], char flag3[]  );
void processIndividualFlag( bool & cBytes, bool & wWords, bool & lLines, char flag[] );
void getNums( int & bytes, int & words, int & lines, string filename );

int main(int argc, char *argv[]){
    bool cBytes = false, wWords = false, lLines = false;
    bool oneFlag = false;
    processFlags( argc, argv, cBytes, wWords, lLines );
    string filename = argv[argc-1];
    int bytes = 0, words = 0, lines = 0;
    getNums( bytes, words, lines, filename );
    bool noFlags = !( wWords || lLines || cBytes );
    //this boolean equation looks stupid I am aware, I tested every combination of the three flags with the actual wc Linux command to determine when a space was printed and this is what I got
    cout << (!(wWords || lLines || cBytes ) || (!cBytes && lLines && wWords) || ( cBytes && lLines && !wWords ) ? " " : "");
    if( !noFlags )//the conditional operators make sure that a value is only printed if its flag is marked
        cout << 
            (lLines ? (to_string(lines)+" ") : "" )<<
            (wWords ? (to_string(words)+" ") : "" )<< 
            (cBytes ? (to_string(bytes)+" ") : "" )<<
        filename << endl;
    else
        cout << lines << " " << words << " " << bytes << " " << filename << endl;
    return 0;

}

void getNums( int & bytes, int & words, int & lines, string filename ){
    fstream inOut (filename.c_str(), ios::in | ios::out);
    inOut.seekg(0);
    if( inOut.eof() )//empty file has all 0s
        return;
    char ch;
    bool wordOnLine = false;
    bool lastCharWhiteSpace = true;
    bool emptyFile = true;
    while( inOut.get(ch) ){
        emptyFile = false;
        bytes++;
        if( ch == ' ' || ch == '\t' ){
            if( !lastCharWhiteSpace && wordOnLine )
                words++;
            lastCharWhiteSpace = true;    
        }else if( ch == '\n' ){
            lines++;
            if( wordOnLine && !lastCharWhiteSpace )//makes sure a line does not count words if no text is there
                words++;
            wordOnLine = false;
            lastCharWhiteSpace = true;
        }else{
            wordOnLine = true;
            lastCharWhiteSpace = false;
        }
    }
    if( !emptyFile )//accounts for the last word of the file, an empty file does not have this however
        words++;
}

void processFlags( int argc, char *argv[], bool & cBytes, bool & wWords, bool & lLines ){
    switch( argc ){
        case 3:
            processOneFlag( cBytes, wWords, lLines, argv[1] );
            break;
        case 4:
            processTwoFlags( cBytes, wWords, lLines, argv[1], argv[2] );
            break;
        case 5:
            processThreeFlags( cBytes, wWords, lLines, argv[1], argv[2], argv[3] );
            break;
        case 2://no flags
            break;
        default:
            cout << "Too many command line args or no file name given, max of 3 flags allowed ( -c, -w, and -l )" << endl;
            exit(0);
    }
}

void processOneFlag( bool & cBytes, bool & wWords, bool & lLines, char flag1[] ){
    processIndividualFlag( cBytes, wWords, lLines, flag1 );
}

void processTwoFlags( bool & cBytes, bool & wWords, bool & lLines, char flag1[], char flag2[] ){
    processIndividualFlag( cBytes, wWords, lLines, flag1 );
    processIndividualFlag( cBytes, wWords, lLines, flag2 );
}

void processThreeFlags( bool & cBytes, bool & wWords, bool & lLines, char flag1[], char flag2[], char flag3[] ){
    processIndividualFlag( cBytes, wWords, lLines, flag1 );
    processIndividualFlag( cBytes, wWords, lLines, flag2 );
    processIndividualFlag( cBytes, wWords, lLines, flag3 );
}

void processIndividualFlag( bool & cBytes, bool & wWords, bool & lLines, char flag[] ){
    if( strcmp( "-c", flag ) == 0 )
        cBytes = true;
    else if( strcmp( "-w", flag ) == 0 )
        wWords = true;
    else if( strcmp( "-l", flag ) == 0 )
        lLines = true;
    else{
        cout << "\"" << flag << "\" is an invalid flag, only -c, -l, and -w are allowed.";
        exit(0);
    }

}