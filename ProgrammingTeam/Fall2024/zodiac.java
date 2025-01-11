import java.util.Scanner;

public class zodiac{

	public static void main(String[] args){
		String[] yearLabels = {"monkey","rooster","dog","pig","rat","ox","tiger","rabbit","dragon","snake","horse","sheep"};
		Scanner scan = new Scanner(System.in);
		int numLines = scan.nextInt();
		int[] years = new int[numLines];
		for( int x = 0 ; x < numLines; x++ )
			years[x] = scan.nextInt();
		for( int year : years )
			System.out.println( year + " is the year of the " + yearLabels[ year % 12 ] );
	}

}
