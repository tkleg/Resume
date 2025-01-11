import java.util.*;

public class nthLargest{

	public static void main( String[] args ){
		Scanner scan = new Scanner( System.in );
		int numTests = Integer.parseInt(scan.nextLine());
		int[] results = new int[numTests];
		for( int x = 0; x < numTests; x++ ){
			int[] nums = new int[10];
			String[] sNums = scan.nextLine().split(" ");
			for( int y = 0; y < 10; y++ )
				nums[y] = Integer.parseInt( sNums[y] );
			Arrays.sort( nums );
			results[x] = nums[7];
		}
		for( int x = 0; x < numTests; x++ )
			System.out.println( (x+1) + " " + results[x] );
	}
}
