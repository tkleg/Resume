import java.util.Scanner;
import java.util.ArrayList;

public class couldWin{

	public static void main( String[] args ){

		Scanner scan = new Scanner( System.in );
		
		String input = scan.next();

		ArrayList<Integer> aliceWins = new ArrayList<>();

		int alice = 0;
		int bob = 0;
		int nextWin = 1;

		for( int k = 0; k < input.length(); k++ ){
			if( input.charAt( k ) == 'A' )
				alice++;
			else if( input.charAt( k ) == 'B' )
				bob++;
			
			if( alice == nextWin ){
				aliceWins.add( k+1 );
				nextWin++;
			}
			else if( bob == nextWin )
				nextWin++;	 
		}

		System.out.println( aliceWins.size() );
		for( int k : aliceWins )
			System.out.print( k + " " );

	}


}
