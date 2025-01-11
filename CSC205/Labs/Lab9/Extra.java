
public class Extra
{
	private static int callLevel = 0;
	public static void main(String[] args)
        {
		puzzle(9);
	}

	private static int puzzle (int n)
	{
		int ans = 0;
		for( int i = 1; i <= 4-n; i++ )
			System.out.print("\t");
		int callNum = -1;
        	if ( (n % 3) == 2 ){
			ans = 1;
		}
        	else if ( (n % 3) == 1 ){
           		callNum = n + 1;		
			System.out.println( "puzzle("+n+") = puzzle("+callNum+") + 2");
			ans = puzzle( callNum ) + 2;
		}
        	else{
           		callNum = n / 3 ;
			System.out.println("puzzle("+n+") = puzzle("+callNum+")  + 1");
			ans =  puzzle( callNum ) + 1;
		}
		for( int i = 1; i <= 4-n; i++ )
			System.out.print("\t");
		System.out.println("puzzle(" + n + ") = returns " + ans );
		return ans;	
	}

	private static void printTabs( int n ){
		for( int x = 0; x < n; x++ )
			System.out.print("\t");
	}
}
