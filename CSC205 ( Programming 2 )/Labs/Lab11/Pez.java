public class Pez{

	public static void main( String[] args ){
		Stack s = new Stack();
		addPez( s );
		removeGreen( s );
		printStack( s );
	}	

	public static void addPez( Stack s ){
		s.push("yellow");
		s.push("red");
		s.push("green");
		s.push("green");
		s.push("yellow");
		s.push("yellow");
		s.push("red");
		s.push("green");
	}

	public static void removeGreen( Stack s ){
		if( s.isEmpty() )
			return;
		Stack tempStack = new Stack();
		while( ! s.isEmpty() ) {
			String z = (String) s.pop();
			if( ! ( z.equals( "green" ) ) )
				tempStack.push(z);
		}
		while( ! tempStack.isEmpty() )
			s.push( tempStack.pop() );
	}

	public static void printStack( Stack stak ){
		Stack tempStack = new Stack();
		while( ! stak.isEmpty() ){
			String s = (String) stak.pop();
			System.out.println( s );
			tempStack.push( s );
		}
		while( ! tempStack.isEmpty() )
			stak.push( tempStack.pop() );
	}
	
}	
