import java.util.Scanner;

public class breakfast{

	public static void main(String[] args ){
		Scanner scan = new Scanner(System.in);
		int numTests = scan.nextInt();
		int[] results = new int[numTests];
		for( int x = 0; x < numTests; x++ ){
			int p = scan.nextInt();
			int d = scan.nextInt();
			int total = p;
			if( d != 1 )
				for( int y = 1 ; y < d; y++ )
					total *= p-1;
			results[x] = total;
		}
		for( int total : results )
			System.out.println(total);
	}
}
