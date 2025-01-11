
import java.util.*;

@SuppressWarnings("unchecked")
public class JCFQueue
{
	public static void main(String[] args) throws CloneNotSupportedException
	{
		LinkedList queue1 = new LinkedList();
		LinkedList queue2 = new LinkedList();
		Object key = new Character('$');

        	queue1.addLast(new Character('b'));
        	queue1.addLast(new Character('$'));
        	queue1.addLast(new Character('E'));
        	queue1.addLast(new Character('$'));
        	queue2.addLast(new Character('b'));
        	queue2.addLast(new Character('$'));
        	queue2.addLast(new Character('E'));
        	queue2.addLast(new Character('b'));
		System.out.println("dup check = " +
                identicalCheck(queue1, queue2));
		findAndReplace(queue1, key, new Character('*'));
		System.out.println("** After findAndReplace **");
		printQueue(queue1);
	}

	private static boolean identicalCheck(LinkedList queue1,
                                              LinkedList queue2)
                throws CloneNotSupportedException
	{
		LinkedList temp1 = (LinkedList) queue1.clone();
		LinkedList temp2 = (LinkedList) queue2.clone();
		while( !temp1.isEmpty() ){
			char c1 = ( (Character) temp1.removeFirst() ).charValue();
			char c2 = ( (Character) temp2.removeFirst() ).charValue();
			if( c1 != c2 )
				return false;
		}
		return temp2.isEmpty();	

	}

	private static void findAndReplace(LinkedList queue1, 
		Object key, Object newVal)
	{
		LinkedList temp = new LinkedList();
		
		while( ! queue1.isEmpty() ){
			Object c = queue1.removeFirst();
			if( c.equals( key ) )
				temp.addLast( newVal );
			else
				temp.addLast( c );
		}
		while( ! temp.isEmpty() )
			queue1.addLast( temp.removeFirst() );
			
	}


	private static void printQueue (LinkedList q)
		 throws CloneNotSupportedException
	{
//		if( q.peek() == null )
//			System.out.println("The queue is empty");
		LinkedList temp = (LinkedList) q.clone();
		while( !temp.isEmpty() )
			System.out.print( temp.removeFirst() );
	}


}
