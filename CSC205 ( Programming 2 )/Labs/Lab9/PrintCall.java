
public class PrintCall
{
        public static void main(String[] args)
        {
                printMe(1);
        }

        public static void printMe(int n)
        {
          if ( ( n != 1 ) && ( n !=  5 ) )
          {
             for (int i = 1;  i <= n;  i++)
                 System.out.print(' ');
             System.out.println("This was written by call number " + n + ".");
          }
	if(  n < 5  ){
		printMe( n + 1 );
		for( int x = 0; x <= n; x++ )	
			System.out.print(' ');
		System.out.println("This ALSO was written by call number " + n +".");
 	}       
  	//  Add an if stmt here with a recursive stmt in its body
          //  along with a for loop similar to the one above 



        }
}

