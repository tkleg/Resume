
import java.util.*;
import java.io.*;

//  Lab program 1
//  This program reads integers and stops when 0 is read.
//  It will print the product of all the integers before the 0.

//  The program contains no error handling.

public class Prog1 
{
	public static void main (String[] args) throws IOException
	{

   		int Product = 1;
   		int value;
                Scanner in = new Scanner(System.in);
		value = in.nextInt();

   		while (value != 0)
   		{
      			Product *= value;
		        value = in.nextInt();
   		}

   		System.out.println("The product is "  + Product);
	}
}
