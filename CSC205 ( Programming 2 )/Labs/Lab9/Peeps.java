
public class Peeps
{
	public static void main(String[] args)
	{
		peeps (5);
	}

	private static void peeps (int n)
	{
        	System.out.println(n + " Peeps");

        	if (n == 1)
                	return;
        	else
                	peeps ( n - 1 );

        	System.out.println(n + " Peeps");
	}
}
