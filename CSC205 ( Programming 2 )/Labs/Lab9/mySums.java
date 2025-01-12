public class mySums{
	public static void main( String[] args ){
		System.out.println( iterativeSum( 5 ) );
		System.out.println( recursiveSum( 5 ) );
	}

	public static int iterativeSum( int n ){
		int sum = 0;
		for( int x = 1; x <= n; x++ )
			sum += 1 + (int)Math.pow( 2, x );
		return sum;
	}

	public static int recursiveSum( int n ){
		int sum = 0;
		if( n == 1 )
			return (int)Math.pow( 2, n ) + 1;
		return recursiveSum( n-1 ) + (int)Math.pow( 2, n ) + 1;
	}
}
