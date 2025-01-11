import java.util.Scanner;

public class sunAndMoon{

public static void main( String[] args ){

	Scanner scan = new Scanner(System.in);

	int ds = scan.nextInt();
	int ys = scan.nextInt();
	int dm = scan.nextInt();
	int ym = scan.nextInt();

	int sunTime = ys - ds;
	int moonTime = ym - dm;
	System.out.println( ( ( sunTime > moonTime ) ? sunTime : moonTime ) );
}

}
