
public class Table
{
  	private static final int ROWS = 3;
  	private static final int COLS = 3;
	
	public static void main(String[] args)
	{
		int[][] table = new int[ROWS][COLS];

		initialize (table);

    scale( table, 5 );

		print (table);
   
   int[][] myTable = {{ 1, 1, 1 },
                      { 1, 1, 1 },
                      { 1, 1, 1 }};
                      
	}

	private static void initialize (int[][] table)
	{
           // Post : Each element of Table is initialized to the sum
           //        of its components

	   for (int i = 0;  i < table.length;  i++)
	   	for (int j = 0;  j < table[i].length;  j++)
			table[i][j] = i + j;
	}
 
  public static void scale( int[][] table, int factor ){
    //pre-conditions: table and factor are initialized
    //post-conditions: every int in table is multipled by factor
    
    for( int x = 0; x < table.length; x++ ){
      for( int y = 0; y < table[x].length; y++ )
        table[x][y] = factor * table[x][y];
    }
    
  }

	private static void print (int[][] table)
	{
	   // Post : The contents of Table are printed to the screen
           //        in tabular format

	   System.out.println("\t[0]\t[1]\t[2]");

	   for (int i = 0;  i < table.length;  i++)
	   {
		System.out.print("[" + i  + "]");
	   	for (int j = 0;  j < table[i].length;  j++)
			System.out.print("\t" + table[i][j]);
		System.out.println();
	   }
	}
}
