//******************************************************************
// IMPLEMENTATION FILE (date.cpp)
//******************************************************************
#include <cstring>   // For strcpy() and strlen()
#include <iostream>
#include "date.h"

using namespace std;

//******************************************************************

Date::Date( int         initMo,
            int         initDay,
            int         initYr,
	    int		initHrs,
	    int		initMins,
	    int		initSecs,
            const char* msgStr  ) : otherTime( initHrs, initMins, initSecs )

// Constructor

{
    mo = initMo;
    day = initDay;
    yr = initYr;
    msg = new char[strlen(msgStr) + 1];
    strcpy(msg, msgStr);
}


//******************************************************************

Date::~Date()
{
    delete [] msg;
}

//******************************************************************

Date::Date(const Date& otherDate)
{
    mo = otherDate.mo;
    day = otherDate.day;
    yr = otherDate.yr;
    msg = new char[strlen(otherDate.msg) + 1];
    strcpy(msg, otherDate.msg);
    otherTime.CopyFrom(otherDate.otherTime);
}

//******************************************************************

void Date::operator=(const Date& otherDate)
{
    mo = otherDate.mo;
    day = otherDate.day;
    yr = otherDate.yr;
    delete [] msg;                               // Deallocate the
                                                 //   original array
    msg = new char[strlen(otherDate.msg) + 1];   // Allocate a new
                                                 //   array
    strcpy(msg, otherDate.msg);                  // Copy the chars
    otherTime.CopyFrom(otherDate.otherTime);
}

//******************************************************************

void Date::Print() const
{
    static char monthString[12][10] =
    {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November",
        "December"
    };

    cout << monthString[mo-1] << "  " << day << ",  " << yr
         << "  " << msg << "  ";
    otherTime.WriteAmPm();
}

//******************************************************************

bool Date:: operator <  (const Date& otherDate) const
{
	if (yr < otherDate.yr)
		return true;
	else if ( (yr == otherDate.yr) && (mo < otherDate.mo) )
		return true;
	else if ( (yr == otherDate.yr) && (mo == otherDate.mo) 
			&& (day < otherDate.day) )
		return true;
	else if ( (yr == otherDate.yr) && (mo == otherDate.mo) 
			&& (day == otherDate.day) &&
			otherTime.LessThan(otherDate.otherTime) )
		return true;
	else
		return false;
}

//******************************************************************

bool Date:: operator ==  ( const Date& otherDate ) const
{
	if ( (yr == otherDate.yr) && (mo == otherDate.mo) 
		&& (day == otherDate.day) && otherTime.Equal(otherDate.otherTime) )
		return true;
	else
		return false;
}

//******************************************************************
