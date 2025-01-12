import java.util.Scanner;

public class TestClock{

	public static void main( String[] args ){

    Scanner scan = new Scanner( System.in );
    
    Clock dvr = new Clock();
    
    System.out.println("What time would you like to set your DVR to?\n");
    System.out.print("Hours = ");
    int hours = scan.nextInt();
    System.out.print("Minutes = ");
    int minutes = scan.nextInt();
    System.out.print("Seconds = ");
    int seconds = scan.nextInt();
    
    dvr.reset( hours, minutes, seconds );
    
    System.out.println("\nThe time is now " + dvr.toString() );
    
    System.out.println("\nAdvancing the time!");
    
    dvr.advance();
    
    System.out.println("\nThe time is now " + dvr.toString() );
    
	}		
}
