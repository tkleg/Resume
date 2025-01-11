using namespace std;
#include "time.h"

int main(){

	Time myTime( 9, 30, 0 );
	myTime.Write();
	myTime.WriteAmPm();
	myTime.Set( 8, 0, 0 );
	myTime.WriteAmPm();
	myTime.Mealtime();
	Time Schedules[10];
	for( int index = 0; index < 10; index++ ){//enhnaced for loops not valid in c++98 :(
		Schedules[index].Set( 11, 0, 0 );
		Schedules[index].WriteAmPm();
	}

	// 14. 11 destructors were printed. 1 for "myTime" and 1 for each of the 10 Time objects in "Schedules"
}
