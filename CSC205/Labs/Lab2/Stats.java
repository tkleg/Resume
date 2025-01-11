
public class Stats
{
	private static final int MAX_SIZE = 100;
	public static void main(String[] args)
	{
        	int[] List = new int[MAX_SIZE];		
		int numItems;

        	numItems = fillUp (List);

        	System.out.println("\n\10\7" + " The range of your " +
                                   numItems + " items is :  " + 
				   range (List, numItems));

        	System.out.println("\n\10\7" + " The mean of your " + 
                                   numItems + " items is  :  " +
				   mean (List, numItems));
	}
 
   public static int fillUp( int[] list ){
    //the while loop appears infinite but it is not because the if statement  
    //within is guaranteed to be activated and run a break statement
     java.util.Scanner scan = new java.util.Scanner(System.in);
     System.out.println("Please Input Your Values (Enter a 0 to Stop):");
     int index = 0;
     while( true ){
       int n = scan.nextInt();
       list[index] = n;
       if( n == 0 || index+2 == list.length )
         break;
       index++;
     }
     return index;
   }

   public static int range( int[] list, int numItems ){
   //this method works by going through every number in the list and chekcing
   //if it is either less than the current mimimum value or if it's larger
   //than the current macimum value
     int min = list[0], max = list[0];
     for( int index = 0; index < numItems; index++ ){
       min = ( list[index] < min ) ? list[index] : min;
       max = ( list[index] > max ) ? list[index] : max;
     }
     return max - min;
   }

   public static double mean( int[] list, int numItems ){
     double sum = 0;
     for( int index = 0; index < numItems; index++ )
       sum += list[index];
     return sum/numItems;
   }






}
