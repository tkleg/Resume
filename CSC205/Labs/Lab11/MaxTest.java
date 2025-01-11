
import java.io.*;
@SuppressWarnings("unchecked")

public class MaxTest 
{
   public static void main(String[] args) throws IOException, CloneNotSupportedException
   {
        	Stack stack1 = new Stack();
		stack1.push("Andy");
		stack1.push("Allison");
		stack1.push("Aaron");
		stack1.push("Austin");
		stack1.push("Abbey");
		stack1.push("Alex");
        	System.out.println("findMax(stack1)="+findMax(stack1)); 
        	System.out.println("stack1.findMax()="+stack1.findMax()); 
  }

  public static String findMax( Stack s ) throws CloneNotSupportedException{
	if( s.top() == null )
		return null;
	Stack sta = (Stack) s.clone();
	String max = (String) sta.top();
	if( max == null )
		return null;
	while( ! ( sta.isEmpty() ) ){
		if( (String) sta.top() == null )
			return max;
		String data = (String) sta.top();
		if( max.compareTo( data ) < 0 )
			max = data;
		sta.pop();
	}
	return max;
  }
	
}
