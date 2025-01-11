
@SuppressWarnings("unchecked")
public class Queue implements QueueInterface { // A Queue class built under the hood as a circular linked list.
  private Node lastNode;  // Points to item in rear.  The next field of lastNode always points to front of the queue.
  
  public Queue() {
    lastNode = null;   
  }  // end default constructor
  
  // queue operations:
  public boolean isEmpty() {
        return (lastNode == null);
  }  // end isEmpty

  public void dequeueAll() {
    lastNode = null;
  }  // end dequeueAll

  public void enqueue(Object newItem) {

    // INSERT YOUR CODE HERE to handle 2 cases: when queue is empty and when it is not empty 
    if( lastNode == null ){
      lastNode = new Node( newItem );
      lastNode.setNext( lastNode );
      return;
    }
    
    Node front = lastNode.getNext();
    Node newNode = new Node( newItem, front );
    lastNode.setNext( newNode );
    lastNode = newNode;

  } 

  public Object dequeue() throws QueueException {

     // INSERT YOUR CODE HERE to handle 3 cases: when queue is empty, has one item, and has more than one item
    if( lastNode == null ){//empty queue
      throw new QueueException("The Queue is empty");
    }
    
    if( lastNode.getNext() == lastNode ){//1 item in queue
      Object o = lastNode.getItem();
      lastNode = null;
      return o;
    }
    
    
    //more than 1 item in the queue
    Object temp = lastNode.getNext().getItem();
    lastNode.setNext( lastNode.getNext().getNext() );
    return temp;
  } 
  
  public Object peek() {
    return lastNode.getNext().getItem();
  }

  public Object front() throws QueueException {
    if (!isEmpty()) {
      Node firstNode = lastNode.getNext();
      return firstNode.getItem();
    }
    else {
      throw new QueueException("QueueException on front:"
                             + "queue empty");
    }
  }

  public Object clone() throws CloneNotSupportedException
  {
	boolean copied = false;
        Queue copy = new Queue();
        Node curr = lastNode, prev = null;
        while ( (! copied) && (lastNode != null) )
        {
                Node temp = new Node(curr.getItem());
                if (prev == null)
                        copy.lastNode = temp;
                else
                        prev.setNext(temp);
                prev = temp;
                curr = curr.getNext();
		copied = (lastNode == curr);
        }
	prev.setNext(copy.lastNode);
        return copy;
  }
} // end Queue
