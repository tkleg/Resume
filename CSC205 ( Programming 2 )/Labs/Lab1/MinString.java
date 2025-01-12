import java.io.*;
import java.util.*;
public class MinString
{
        private static final int SIZE = 10;
        public static void main(String[] args)
        {
                String[] list = new String[SIZE];
                int numItems;

                numItems = Initialize (list);
                System.out.println(FindMin (list, numItems));
        }

        private static int Initialize (String[] list)
        {
          //post : List is initialized with all strings from file.

          String filename, stateInput;
          int i = 0, numItems = 0;
          try  {
                System.out.print("Input File : ");
                Scanner stdin = new Scanner(System.in);
                filename = stdin.nextLine();
                stdin = new Scanner(new File(filename));

                while ((stdin.hasNext()) && (i < list.length))
                {
                        stateInput = stdin.nextLine();
                        System.out.println("S = " + stateInput);
                        list[i] = stateInput;
                        i++;
                }
                numItems = i;
          }
          catch (IOException e)  {
                System.out.println(e.getMessage());
          }
          return numItems;
        }

        // Method FindMin goes here
        //
	public static String FindMin( String[] list, int numItems ){
		//default the min string to the first in the list		
		String minString = list[0];
		
		//iterate through every String in list
		for( int index = 1; index < numItems; index++ ){
			//determine if the minString comes after a String in the list alphabetically
			if( minString.compareTo( list[index] ) > 0 ){
				//set the minString to a String in the list if the abov econiditon is true
				minString = list[ index ];
			}
		}
		//return the minString
		return minString;
	}

}


