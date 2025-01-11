
@SuppressWarnings("unchecked")

public class Links
{
	public static void main(String[] args)
	{
          	Node pos1 = null;
    		Node pos2 = null;
    		pos1 = new Node(new Integer(13));
   		pos1.setNext(new Node(new Integer(15), null));
    		pos2 = new Node(new Integer(11), null);
		pos2.setNext(pos1);
		printList(pos2);
		System.out.println( "\n"+count( pos2 ) );
		System.out.println( findMax( pos2 ) );
	}

	private static void printList(Node head)
	{
		if (head != null)
		{
			System.out.println(head.getItem());
			printList(head.getNext());
		}
	}

	private static int count( Node head ){
		if( head == null )
			return 0;
		return 1 + count( head.getNext() );
	}

	private static Comparable findMax( Node n ){
		Node curr =  n;
		Comparable curMax = (Comparable) curr.getItem();
		for( int x = 1 ; x < count(n); x++){
			if( curMax.compareTo( (Comparable) curr.getNext().getItem() ) < 0 )
				curMax = (Comparable) curr.getNext().getItem();
			curr = curr.getNext();
		}
		return curMax;
	}
}
