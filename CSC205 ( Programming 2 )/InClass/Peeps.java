public class Peeps{
	public static void main( String[] args ){
		peeps( Integer.parseInt( args[0] ) );
	}
	private static void peeps( int n ){
		if( n < 1 ){
			System.out.println("n must be an integer 1 or greater");
			System.exit(1);
		}
		System.out.println( n + " Peeps");
		if( n == 1 )
			return;
		else
			peeps( n-1 );
		System.out.println( n + " Peeps");
	}
}
