import java.util.*;
import java.io.*;

public class VowelFrequencies{

	public static void main( String[] args ) throws FileNotFoundException{
		Scanner scan = new Scanner( new File("vowels.txt") );
		while( scan.hasNext() ){
			processLine( scan.nextLine() );	
		}
	}

	public static void processLine( String line ){
		
		VowelCounter[] counters = new VowelCounter[5];
		counters[0] = new VowelCounter( 'a' );
		counters[1] = new VowelCounter( 'e' );
		counters[2] = new VowelCounter( 'i' );
		counters[3] = new VowelCounter( 'o' );
		counters[4] = new VowelCounter( 'u' );
		
    getCounts( counters, line );
    
    for( int x = 0 ; x < 5 ; x++ ){
      VowelCounter maxVowel = new VowelCounter( 'z', -1 );
      for( int y = 0 ; y < 5 ; x++ ){
        if( counters[y] == null )
          continue;
        if( counter[y].count > maxVowel.count )  
          maxVowel = 
      }
      
	}
 
  public static void getCounts( VowelCounter[] counters, String line ){
    
    for( int x = 0 ; x < line.length(); x++ )
      switch( line.charAt( x ) ){
        case 'a':
          counters[0].count++;
          break;
        case 'e':
          counters[1].count++;
          break;
        case 'i':
          counters[2].count++;
          break;
        case 'o':
          counters[3].count++;
          break;
        case 'u':
          counters[4].count++;
          break;
        default:
          break;
      }
  }

}
}
