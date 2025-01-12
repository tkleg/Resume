//This is just used to test the Queue class
public class TestQueue{

public static void main( String[] args ){

    Queue q = new Queue();
    for( int x = 25; x >= 0; x-- )
	q.enqueue( new Integer(x) );
    q.enqueue( new Integer( 100 ) );
    while( ! q.isEmpty() )
      System.out.print( q.dequeue() + ", "  );  
}

}
