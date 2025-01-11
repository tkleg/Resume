import java.util.Scanner;
import java.util.ArrayList;

public class islands{
public static void main( String [] args ){
	Scanner scan = new Scanner( System.in );
	int numRows = scan.nextInt();
	int numCols = scan.nextInt();
	scan.useDelimiter("");
	int[][] map = new int[numRows][numCols];
	for( int x = 0; x < map.length; x++ ){
		scan.next();
		for( int y = 0; y < map[x].length; y++ )
			map[x][y] = (int) ( scan.next().charAt(0) );
	}
	int infector = 133;
	
	boolean passNeededNewInfector = true;
	while( passNeededNewInfector ){
		passNeededNewInfector = false;
		boolean thisIterInfect = false;
		for( int colIter = 0; colIter < map.length; colIter++ ){
			for( int rowIter = 0; rowIter[0].length; rowIter++ ){
				if( map[colIter][rowIter] >= 133 )//is it already infected
					continue;
				//reached if not infected
				if( ! thisIterInfect ){
					map[colIter][rowIter] = infector;
					thisIterInfect = true;
				}else{
					ArrayList<int> adjacentRows = getAdjacents( (colIter == 0 ), (colIter+1 == map.length), (rowIter == 0), (rowIter+1 == map[0].length ), colIter, rowIter );		
				}
			}
		}

	}
}

public ArrayList<int> getAdjacents( boolean topCol, boolean bottomCol, boolean leftRow, boolean rightRow, int colIter, int rowIter ){
	ArrayList<int> adjacents = new ArrayList<int>();
	

}

