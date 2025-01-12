import java.util.*;
public class TestArrayList
{
    public static void main(String[] args)
    {
	ArrayList<String> myArrayList = new ArrayList<String>(10);
	
     myArrayList.add( "Python" );
     for( int count = 0; count < 5; count++ )
       myArrayList.add( "Java" );
     for( int count = 0; count < 4; count ++ )
       myArrayList.add( "C++" );

      //printArrayList( myArrayList );
      delete( myArrayList, "Java" );
      printArrayList( myArrayList );




    }

    private static void printArrayList(ArrayList<String> myArrayList)
    {
	// Pre  : myArrayList has been initialized
	// Post : The elements of Vector v are printed to the screen on separate lines
      for( String s : myArrayList )
        System.out.println( s );



    }

    private static void delete(ArrayList<String> myArrayList, Object key)
    {
	// Pre  : myArrayList has been initialized
	// Post : All copies of key are removed from myArrayList
      for( int index = 0; index < myArrayList.size(); index++ ){
          if( myArrayList.get( index ).equals( key ) ){
                myArrayList.remove( index );
                index--;
          }
      }


    }

    private static int count(ArrayList<String> myArrayList, Object key)
    {
	// Pre  : myArrayList has been initialized
	// Post : number of occurrences of key is computed and returned
      int count = 0;
      for( String s : myArrayList )
        count += ( s.equals( key ) ) ? 1 : 0;
      return count;

    }
}
