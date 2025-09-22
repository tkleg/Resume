#include<iostream>
#include<sstream>
#include<cstring>
using namespace std;

string compress( string myInput );

string uncompress( string compressed );

void check( string myInput );

int main(){
    check("93 93 93 93 92 91 91 94 94 94 94 94 95 95 95 73 73 73 73 73 73 73");
    check("1 2 3 4 5 5 5 5 6 2 2 2 1 1 5 7 7 7 7 7 4 4 4 4");
    check("1 2 4 4 6 7");
    check("1 1 1 1 1 1 1 1");
    check("1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1");
    check("1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 h 1 1 1 1 1 1");
    check( "hello hello hello hello te 4griubf oif pie pie oirjf opnrfo pwojroj3 o o o m m m m gou4hfiu 3ojb4d");
}

void check( string myInput ){
    string output = compress(myInput);
    string uncompressed = uncompress(output);

    printf("%-13s = %s\n", "compressed", output.c_str());
    printf("%-13s = %s\n", "input", myInput.c_str());
    printf("%-13s = %s\n", "uncompressed", uncompressed.c_str());

    if( uncompressed == myInput )
        cout << "success" << endl;
    else{
        cout << ":";
        for( int x= 0 ; x < myInput.length(); x++ )
            cout << (int) myInput[x]<< ":";
        cout << endl << endl << ":";
        for( int x= 0 ; x < uncompressed.length(); x++ )
            cout << (int) uncompressed[x]<< ":";
    }
    cout << endl;
}

string compress( string myInput ){
    stringstream myStream(myInput);
    string pixel, recentPixel = "", result = "";
    int count = -1;
    while( myStream ){
        myStream >> pixel;
        if( pixel == recentPixel )
            count++;
        else{
            if( count <= 3 ){
                for( int x = 0; x < count; x++ )
                    result += recentPixel + " ";
                count = 1;
            }else{
                string countstring = count >= 10 ? to_string(count) : "0"+to_string(count);
                result += "ff " + recentPixel + " " + countstring + " ";
                count = 1;
            }
            recentPixel = pixel;
        }
    }

    count--;
    if( count == 1 )
        result += pixel;
    else{
        string countstring = count >= 10 ? to_string(count) : "0"+to_string(count);
        result += "ff " + recentPixel + " " + countstring;
    }
    return result;
}

string uncompress( string compressed ){
    stringstream myStream(compressed);
    string result, curr;
    
    while(true){
        myStream >> curr;
        if( !myStream )//prevents the last value from printing twice
            break;
        if( curr != "ff" )
            result += curr + " ";
        else{
            string value, numS;
            myStream >> value >> numS;
            int num = atoi(numS.c_str());
            for( int x = 0; x < num; x++ )
                result += value + " ";
        }
    }
    result.pop_back();
    return result;
}