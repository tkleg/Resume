import java.io.*;
import java.util.*;

public class MirroredPairs{

  final static int MIRROR = 0;
  final static int ORDINARY = 1;
  final static int FINISHED = 2;	
  static Set<String> validPairs;;
 
public static void main( String[] args ) throws FileNotFoundException{

  validPairs = new HashSet<String>();
  validPairs.add("bd");
  validPairs.add("db");
  validPairs.add("pq");
  validPairs.add("qp");
  
	File file;
	if( args.length != 0 )
		file = new File( args[0] );
	else
		file = new File("pairs.txt");
   	Scanner scan = new Scanner( file );
	System.out.println("Ready!");
	
	findMirrors( scan );

}

public static void findMirrors( Scanner scan ){
	String line = "";
	int mirrorCount = 0;
	int ordinaryCount = 0;
	while( true ){
		line = scan.nextLine();
		switch( mirroredPair( line ) ){
			case MIRROR:
				System.out.println( "Mirrored pair" );
				mirrorCount++;
				break;
			case ORDINARY:
				System.out.println( "Ordinary pair" );
				ordinaryCount++;
				break;
			default:
				printResults( mirrorCount, ordinaryCount );
				System.exit(1);
		}
	}
}

public static int mirroredPair( String line ){
	if( line.substring(0,2).equals("  ") )
		return FINISHED;
  else if( validPairs.contains( line ) )
    return MIRROR;
  else
    return ORDINARY;
}


public static void printResults( int mirrorCount, int ordinaryCount ){
	String sMirror = ( mirrorCount == 1 ) ? "" : "s";
	String sOrdinary = ( ordinaryCount == 1 ) ?  "" : "s";
	System.out.println("Summary: " + mirrorCount + " Mirrored pair" + sMirror + ", " + ordinaryCount + " Ordered pair" + sOrdinary );	
}

}
