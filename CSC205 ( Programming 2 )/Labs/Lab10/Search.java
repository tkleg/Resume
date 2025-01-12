
import java.io.*; 
import java.util.*;
@SuppressWarnings("unchecked")

public class Search { 
 public static void main(String argv[]) throws IOException { 

  Scanner stdin = new Scanner(System.in);
  System.out.println("Please input 0 or more values at keyboard");
  Node head = buildList();

  System.out.println("Now printing list");
  printList(head);
  System.out.println("\nWhat key in list are you searching for? ");
  int key = stdin.nextInt();
  System.out.print("Your key was ");
  if (search(head, key))
    System.out.println("found.");
  else
    System.out.println("not found.");

  }

  private static void printList(Node head)
  {
                if (head != null)
                {
                        System.out.print(head.getItem() + " ");
                        printList(head.getNext());
                }
  }


  private static Node buildList() throws IOException
  {
        Scanner in = new Scanner(System.in);
        Node head;
        if(in.hasNext())
        {
                head = new Node(new Integer(in.nextInt()),null);
        }
        else
        {
                head = new Node(null,null);
                return head;
        }

        while(in.hasNext())
                head = insert(head,new Integer(in.nextInt()));

        return head;
  }

  private static Node insert(Node head, Comparable newValue)
  {
	Node prev, curr = head;

	for (prev = null,  curr = head;
             curr != null && newValue.compareTo(curr.getItem()) > 0;
             prev = curr, curr = curr.getNext() ) {}

        Node newNode = new Node(newValue, curr);
	if (prev != null)
        {
        	prev.setNext(newNode);
		return head;
        }
	else
		return newNode;
  }

  private static boolean search(Node head, Comparable key)
  {
     // PRE:  head points to the front of linked list;  list may be
     //         empty or non-empty;  key is item searching for
     // POST: returns true or false regarding whether key is found in
     //         list
     if( head == null )
       return false;
     Comparable item = (Comparable) head.getItem();
     return item.compareTo( key ) == 0 || search( head.getNext(), key );

  } 

} 
