import java.util.Scanner;

public class Histogram{
public static void main( String [] args ){
	Scanner scan = new Scanner( System.in );
	int[] numNums = new int[ scan.nextInt() ];
	for( int x = 0; x < numNums.length; x++ )
		numNums[x] = scan.nextInt();
	for( int x : numNums ){
		for( int y = 0; y < x; y++ )
			System.out.print('=');
		System.out.println();

	}
}
}
