
import java.util.*;

public class Sets
{
	private static final int BOUND = 8;
	public static void main(String[] args)
	{
		BitSet set1 = new BitSet(BOUND);
		BitSet set2 = new BitSet(BOUND);
		
		for (int i = 1;  i < BOUND;  i *= 2)
			set1.set(i);
     //set1 = 01101000

		for (int i = BOUND-1;  i > 0;  i /= 2)
			set2.set(i);
     //set2 = 01010001
     
		System.out.print("set1 = ");
		print(set1);
		System.out.print("set2 = ");
		print(set2);

		System.out.print("\ninverse of set1 = ");
		print(inverse(set1));
		System.out.print("inverse of set2 = ");
		print(inverse(set2));

	}
 
   public static void print( BitSet bits ){
   
     for( int x = 0; x < BOUND; x++ )
       System.out.print( ( bits.get(x) ) ? 1 : 0 );
     System.out.println();
       
   }
   
   public static BitSet inverse( BitSet bits ){
   
     BitSet invSet = new BitSet(BOUND);
     
     for( int x = 0; x < BOUND; x++ ){
       if( bits.get( x ) )
         invSet.clear( x );
       else
         invSet.set( x );
     }
              
     return invSet;
     
   }

}
