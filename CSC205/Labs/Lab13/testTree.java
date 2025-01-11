public class testTree{
	
	public static void main( String[] args ){

		BinarySearchTree b = new BinarySearchTree();
		b.insert( new KeyedItem(45) );
		b.insert( new KeyedItem(25) );
		b.insert( new KeyedItem( 75 ) );
		b.insert( new KeyedItem( 15 ) );
		b.insert( new KeyedItem( 35 ) );
		b.postOrder();
	}
}
