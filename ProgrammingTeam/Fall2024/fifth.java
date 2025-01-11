import java.util.Scanner;

public class fifth{

	public static void main(String[] args){
		Scanner scan = new Scanner(System.in);
		int numTests = Integer.parseInt(scan.nextLine());
		int[][] results = new int[numTests][2];
		for( int x =0; x < numTests; x++ ){
			int num1 = scan.nextInt();
			int num2 = scan.nextInt();
			int less = 0 , more = 0;
			if( num1 < num2 ){
				less = num1;
				more = num2;
			}else{
				less = num2;
				more = num1;
			}
			//GCF
			results[x][1] = 1;
			for( int i = 1; i < less; i++ ){
				if( less == more ){
					results[x][1] = less;
					break;
				}
				if( less % i == 0 && more % i == 0 )
					results[x][1] = i;
			}
			//LCM
			for( int i = 1; true; i++ ){
				if( (more*i) % less == 0 ){
					results[x][0] = more*i;
					break;
				}
			}
		//	System.out.println( (x+1) + " " + results[x][0] +" " + results[x][1] );
		}
		for( int x = 0; x < numTests; x++ )
			System.out.println( (x+1) + " " + results[x][0] +" " + results[x][1] );
	}
}
