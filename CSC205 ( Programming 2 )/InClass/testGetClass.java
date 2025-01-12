import java.util.ArrayList;

public class testGetClass{

	public static void main( String[] args ){
		Object obj = new ArrayList<Integer>();
		System.out.println( ((Object)  obj).getClass().getSimpleName() );
	}
}
