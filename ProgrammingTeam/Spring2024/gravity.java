import java.util.Scanner;

public class gravity{
public static void main( String [] args ){
	Scanner scan = new Scanner( System.in );
	char[][] field = new char[ scan.nextInt() ][ scan.nextInt() ];
	//System.out.print( field.length +", "+field[0].length );
	scan.useDelimiter("");
	for( int x = 0; x < field.length; x++ ){
		scan.next();
		for( int y = 0; y < field[x].length; y++ )
			field[x][y] = scan.next().charAt(0);
	}
	//for( int x = 0; x < field.length; x++ )
	//	for( int y = 0; y < field[x].length; y++ )
	//		System.out.print( field[x][y] + " " );

	for( int x = 0; x < field[0].length; x++ ){
		boolean anotherRunNeeded = true;
		while( anotherRunNeeded ){
			anotherRunNeeded = false;
			for( int colIter = 0; colIter < (field.length-1); colIter++ ){
				if( field[colIter][x] == 'o' && field[colIter+1][x] == '.' ){
					field[colIter][x] = '.';
					field[colIter+1][x] = 'o';
					anotherRunNeeded = true;
				}
			}
		}
	}
	System.out.println("\n\n");
	for( char[] arr : field ){
		for( char c : arr )
			System.out.print( c );
		System.out.println();
	}

}
}	
