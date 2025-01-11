import java.util.Scanner;

public class lookAndSay{

	public static void main( String[] args ){
		Scanner scan = new Scanner(System.in);
		int numStrings = Integer.parseInt(scan.nextLine());
		String[] lines = new String[numStrings];
		for( int x = 0; x < numStrings; x++ )
			lines[x] = scan.nextLine();

		for( int x = 0; x < numStrings; x++ ){
			char curNum = lines[x].charAt(0);
			int curCount = 1;
			String line = lines[x];
			line = line.substring(1);
			while( line.length() != 0 ){
				if( line.charAt(0) == curNum )
					curCount++;
				else{
					System.out.print( curCount +""+ curNum );
					curCount = 1;
					curNum = line.charAt(0);
				}
				line = line.substring(1);
			}
			System.out.print( curCount +""+ curNum );
			System.out.println();
		}
	}

}
