//******************************************************************
// SPECIFICATION FILE (date.h)
//******************************************************************
#include "time.h"
using namespace std;

class Date
{

public:

    void Print() const;

    Date( int         initMo = 1,
          int         initDay = 0,
          int         initYr = 0,
	  int	      initHrs = 0,
	  int	      initMins = 0,
	  int	      initSecs = 0,
          const char* msgStr = "No Date"); 

    Date( const Date& otherDate );
        // Copy-constructor

    ~Date();
        // Destructor
	
    bool operator < (const Date& otherDate) const;

    bool operator == (const Date& otherDate) const; 

    void operator = (const Date& otherDate);

private:

    int   mo;
    int   day;
    int   yr;
    Time otherTime;
    char* msg;

friend ostream& operator << (ostream& os, const Date& date)
{
        date.Print();
        return os;
}

};
