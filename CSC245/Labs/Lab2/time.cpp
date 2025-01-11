//******************************************************************
// IMPLEMENTATION FILE (time.cpp)
// This file implements the Time member functions
//******************************************************************
#include <iostream>
using namespace std;
#include "time.h"

// Private members of class:
//     int hrs;
//     int mins;
//     int secs;

//******************************************************************

Time::Time( /* in */ int initHrs,
                    /* in */ int initMins,
                    /* in */ int initSecs )
// Constructor

// Precondition:
//     0 <= initHrs <= 23  &&  0 <= initMins <= 59
//  && 0 <= initSecs <= 59
// Postcondition:
//     hrs == initHrs  &&  mins == initMins  &&  secs == initSecs

{
    hrs = initHrs;
    mins = initMins;
    secs = initSecs;
}

//******************************************************************

Time::Time()

// Default constructor

// Postcondition:
//     hrs == 0  &&  mins == 0  &&  secs == 0

{
    hrs = 0;
    mins = 0;
    secs = 0;
}

//******************************************************************

void Time::Set( /* in */ int hours,
                    /* in */ int minutes,
                    /* in */ int seconds )

// Precondition:
//     0 <= hours <= 23  &&  0 <= minutes <= 59
//  && 0 <= seconds <= 59
// Postcondition:
//     hrs == hours  &&  mins == minutes  &&  secs == seconds

{
    hrs = hours;
    mins = minutes;
    secs = seconds;
}

//******************************************************************

void Time::Increment()

// Postcondition:
//     Time has been advanced by one second, with
//     23:59:59 wrapping around to 0:0:0

{
    secs++;
    if (secs > 59)
    {
        secs = 0;
        mins++;
        if (mins > 59)
        {
            mins = 0;
            hrs++;
            if (hrs > 23)
                hrs = 0;
        }
    }
}

//******************************************************************

void Time::Write() const

// Postcondition:
//     Time has been output in the form HH:MM:SS

{
    if (hrs < 10)
        cout << '0';
    cout << hrs << ':';
    if (mins < 10)
        cout << '0';
    cout << mins << ':';
    if (secs < 10)
        cout << '0';
    cout << secs << endl;
}


void Time::WriteAmPm() const{

	bool am;
	int tempHrs;
	
	am = ( hrs <= 11 );
	if( hrs == 0 )
		tempHrs = 12;
	else if( hrs >= 13 )
		tempHrs = hrs - 12;
	else
		tempHrs = hrs;

	if( tempHrs < 10 )
		cout <<'0';
	cout << tempHrs << ':';
	if( mins < 10 )
		cout << '0';
	cout << mins << ':';
	if( secs < 10 )
		cout << '0';
	cout << secs;
	if ( am )
		cout << " AM";
	else
		cout << " PM";
	
	cout << endl;

}
//******************************************************************

bool Time::Equal( /* in */ Time otherTime ) const

// Postcondition:
//     Function value == TRUE, if this time equals otherTime
//                    == FALSE, otherwise

{
    return (hrs == otherTime.hrs && mins == otherTime.mins &&
            secs == otherTime.secs);
}

//******************************************************************

bool Time::LessThan( /* in */ Time otherTime ) const

// Precondition:
//     This time and otherTime represent times in the
//     same day
// Postcondition:
//     Function value == TRUE, if this time is earlier
//                             in the day than otherTime
//                    == FALSE, otherwise

{
    return (hrs < otherTime.hrs ||
            hrs == otherTime.hrs && mins < otherTime.mins ||
            hrs == otherTime.hrs && mins == otherTime.mins
                                 && secs < otherTime.secs);
}

void Time::Mealtime() const{

	if( hrs == 8 && mins == 0 && secs == 0 )
		cout << "Breakfast";
	else if( hrs == 12 && mins == 0 && secs == 0 )
		cout << "Lunch";
	else if( hrs == 19 && mins == 0 && secs == 0 )
		cout << "Dinner";
	cout << endl;

}

Time::~Time(){

	cout << "Destructor Called." << endl;

}
