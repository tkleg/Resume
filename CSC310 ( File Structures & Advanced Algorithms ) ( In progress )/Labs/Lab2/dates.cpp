#include<iostream>
#include<map>
#include<sstream>
#include<string>
using namespace std;

int dateToCanonical(string date);
int main(){
    cout << dateToCanonical("February 14, 2025") << endl;
    cout << dateToCanonical("April 3, 1976") << endl;

}

int dateToCanonical( string date ){
    string month, day, year;
    stringstream sstream(date);

    getline(sstream, month, ' ');
    getline(sstream, day, ',');
    char ch;
    sstream.get(ch);//handles the space after the comma following the day number
    getline(sstream, year);

    map<string, string> monthToNum = {
        {"January", "1"}, {"February", "2"}, {"March", "3"},
        {"April", "4"}, {"May", "5"}, {"June", "6"}, {"July", "7"},
        {"August", "8"}, {"September", "9"}, {"October", "10"},
        {"November", "11"}, {"December", "12"}
    };
    
    return stoi(monthToNum[month]+day+year);

}