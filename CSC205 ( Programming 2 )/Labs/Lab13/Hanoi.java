
import java.util.*;
class Hanoi
{
  public static void main(String[] args)
  {
	final char PEG1 = 'A',	// the three pegs
		   PEG2 = 'B',
		   PEG3 = 'C';

	System.out.println("This program solves the Hanoi Towers puzzle");
	System.out.print("Enter the number of disks:  ");
        Scanner s = new Scanner(System.in);
	int numDisks = s.nextInt();

	System.out.println( move(numDisks, PEG1, PEG2, PEG3) );
  }

  public static String move(int n, char source, char destination, char spare)
  {
	if (n <= 1)
		return "Move the top disk from " + source +
		       " to " + destination + "\n";
        else
		return move(n-1, source, spare, destination) +
                       move(1, source, destination, spare) +
                       move(n-1, spare, destination, source);
  }
}
