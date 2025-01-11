import java.util.*;
@SuppressWarnings("unchecked")

public class JCFStack
{
   public static void main(String[] args) throws CloneNotSupportedException
   {
        	Stack stack1 = new Stack();
		stack1.push(new Integer(27));
		stack1.push(new Integer(0));
		stack1.push(new Integer(-3));
		stack1.push(new Integer(-18));
		stack1.push(new Integer(99));
        	printStack (stack1); 
		
		System.out.print("key value = ");
		Scanner scan = new Scanner( System.in );
		int index = stack1.search( new Integer( scan.nextInt() ) );
		if( index != -1 )
			System.out.println("key value found at position " + index );
		else
			System.out.println("key value not found");
  }

  private static void printStack (Stack s) throws CloneNotSupportedException
  {
        Stack tempStack = (Stack) (s.clone());
        if (! tempStack.isEmpty())
                System.out.println("*** Printing Out Stack:  ");

        while (! tempStack.isEmpty())
        {
               System.out.print(tempStack.peek() + "  ");
               tempStack.pop();
        }
	System.out.println();
  }
}
