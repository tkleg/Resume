import java.util.Scanner;

public class magicClock{

	public static void main(String[] args){
		Scanner scan = new Scanner(System.in);
		int numTimes = Integer.parseInt(scan.nextLine());
		Time[] times = new Time[numTimes];
		for( int x = 0; x < numTimes; x++ ){
			String line = scan.nextLine();
			String[] parts = line.split(":");
			int[] values = new int[3];
			for( int y = 0; y < 3; y++ )
				values[y] = Integer.parseInt( parts[y] );
			times[x] = new Time( values[0], values[1], values[2] );
		}
		for( Time time : times ){
			int secAway = 0;
			while( ! time.isMagic() ){
				time.increment();
				secAway++;
			}
			printResult( secAway );
		}
	}

	public static void printResult( int secAway ){
		if( secAway == 0 )
			System.out.println("Look Andy, it’s a magical time!");
		else if( secAway == 1 )
			System.out.println("The next magical time is 1 second away.");
		else
			System.out.println("The next magical time is "+secAway+" seconds away.");
	}

}

class Time{
	public int hour;
	public int minute;
	public int second;

	public Time( int hour, int minute, int second ){
		this.hour = hour;
		this.minute = minute;
		this.second = second;
	}

	public void increment(){
		second++;
		if( second == 60 ){
			second = 0;
			minute++;
			if( minute == 60 ){
				minute = 0;
				hour++;
				if( hour == 13 )
					hour = 1;
			}
		}
	}

	public int hourMinAngle(){
		int angleHour = hour*5; //changes range from 1-12 to 5-60
		if( angleHour == minute )//minute and hour hand are touching
			return 0;
		boolean hourLater = angleHour > minute;
		int hourAwayZero = numAwayZero( angleHour, hourLater );
		int minAwayZero = numAwayZero( minute, !hourLater );
		int difOverZero = hourAwayZero + minAwayZero;
		int dif = Math.abs( angleHour - minute );
		return Math.min( dif, difOverZero );

	}

	public int minSecAngle(){
		if( minute == second )
			return 0;
		boolean minuteLater = minute > second;
		int minAwayZero = numAwayZero( minute,  minuteLater );
		int secondAwayZero = numAwayZero( second, !minuteLater );
		int difOverZero = minAwayZero + secondAwayZero;
		int dif = Math.abs( minute - second );
		return Math.min( dif, difOverZero );
	}

	public static int numAwayZero( int num, boolean later ){
		if( later )
			return 60 - num;
		return num;
	}

	public boolean isMagic(){
		return minSecAngle() == hourMinAngle();
	}

	public String toString(){
		return hour+":"+minute+":"+second;
	}
}
