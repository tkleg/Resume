import java.util.*;

public class conversions{

	public static void main( String[] args ){
		Scanner scan = new Scanner(System.in);
		int numCases = Integer.parseInt(scan.nextLine());
		String[] units = new String[numCases];
		double[] vals = new double[numCases];
		for( int x = 0; x < numCases; x++ ){
			double val = scan.nextDouble();
			String unit = scan.next();
			if( unit.equals("kg") ){
				val *= 2.2046;
				units[x] = "lb";
			}else if( unit.equals("lb") ){
				val *= 0.4536;
				units[x] = "kg";
			}else if( unit.equals("l") ){
				val *= 0.2642;
				units[x] = "g";
			}else{
				val *= 3.7854;
				units[x] = "l";
			}
			vals[x] = val;
		}
		for( int x =0 ; x < numCases; x++ )
			System.out.printf("%d%s%.4f%s%s\n", (x+1), " ", vals[x], " ", units[x] );
	}
}
