import java.util.Scanner;
import java.util.ArrayList;

class health{

public static void main( String[] args ){
	System.out.println();
	Scanner scan = new Scanner(System.in);

	//d = ( (int) (d+0.005*100) ) /100.0;
	
	double num = scan.nextDouble();
	double weekTotal = 0;
	int daysInWeek = 0;
	int weeksPrinted = 0;
	double monthTotal = 0;
	int daysInMonth = 0;
	int monthsPrinted = 0;
	double yearTotal = 0;
	int daysInYear = 0;
	while( num != -3.0 ){
		if( num == -1 ){
			System.out.println( "Week #" + ++weeksPrinted + " = " + roundD( weekTotal/daysInWeek ) + " mi.");
			weekTotal = 0;
			daysInWeek = 0;
		}
		else if( num == -2 ){
			System.out.println("\nMonth #" + ++monthsPrinted + " = " + roundD( monthTotal/daysInMonth ) + " mi.\n");
			monthTotal = 0;
			daysInMonth = 0;
		}				
		else{
			weekTotal += num;
			monthTotal += num;
			yearTotal += num;

			daysInWeek++;
			daysInMonth++;
			daysInYear++;
		}
		num = scan.nextDouble();
	}

	System.out.println("\nYear to Date for " + daysInYear + " days = " + roundD( yearTotal/daysInYear ) + " mi.");

}


static double roundD( double d ){
	return  ( (int) ((d+0.005)*100) ) /100.0 ;
}



}
