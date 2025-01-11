
import java.util.*;
public class arThree
{

  public static void main(String args[])
  {
    System.out.print("Enter maximum number of numbers you want to enter: ");
    Scanner stdin = new Scanner(System.in);
    int item_count = stdin.nextInt();

    // create the input array
    double in_array[] = new double[item_count];
    
    boolean stop = false;

    for(int i = 0; (i < in_array.length) && !stop; i++)
      {
	System.out.print("\nEnter value " + (i+1) + "/" + item_count + ": ");
	double number = stdin.nextDouble();

	if (number < 0) // stop loop
	  stop = true;
	else            // save input in our array
	  in_array[i] = number;
      }
  }

}
