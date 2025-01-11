import java.util.Scanner;

public class smile{

	public static void main(String[] args){
		int ind1 = -1;
		int ind2 = 0;
		int ind3 = 1;
		int index = -1;
		int count = 0;
		Scanner scan = new Scanner(System.in);
		String line = scan.nextLine();

		while( line.length() >= 3 ){
			if( line.charAt(0) != ':' ){
				line = line.substring(1);
				continue;
			}
			if( line.charAt(1) != '-' ){
				line  = line.substring(1);
				continue;
			}
			if( line.charAt(2) != ')' ){
				line = line.substring(1);
				continue;
			}
			count++;
			line = line.substring(3);
		}

		System.out.println("Smiley Count = " + count );

	}


}
