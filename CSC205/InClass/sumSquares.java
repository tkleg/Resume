public class sumSquares{

	public static void main(String[] args){
		int num = Integer.parseInt( args[0] );
		System.out.print( sumS( num ) == (num*(num+1)*(2*num+1))/6);
	}

	private static int sumS( int n ){
		if( n==1 )
			return 1;
		return n*n + sumS( n-1 );
	}

}
