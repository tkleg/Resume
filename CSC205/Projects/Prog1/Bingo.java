import java.util.*;
import java.io.*;

public class Bingo{
  
  private static final int VERTICAL = 1;
  private static final int HORIZONTAL = 0;
  private static final int DIAGONAL = 2;
  
  private static final int FILE_NOT_FOUND = 0;
  private static final int INVALID_INT = 1;
  private static final int DUPLICATE_INTS = 2;
  private static final int INVALID_CHAR = 3;
  private static final int EMPTY_FILE = 4;
  private static final int NUM_OF_EXCEPTIONS = 5;
  
  private static final int LINE_BREAK_LENGTH = 79;
  
  private static final int NUM_COLS = 5;
  private static final int NUM_ROWS = 5;

  public static void main( String[] args ){
  
    int[][] card = new int[NUM_ROWS][NUM_COLS];
  
    printOpenerMessage();
    fillCard( card );
    playGame( card );
  
    System.out.println("\nIf you would like to play again then enter \"play\"\nIf you don't want to play again, enter anything else to terminate the program.\n");  
    if( new Scanner(System.in).next().equals("play") )
      main( new String[] {} ); 
      //main( newString[] {} ) was taken off of https://stackoverflow.com/questions/26565769/rerun-recall-main-method-program
      
  }

  public static void printOpenerMessage(){
  //pre-conditions: the main method calls this method
  //post-conditions: a long message is printed out to explain to the user how to play the game 
    printLineSeperator( LINE_BREAK_LENGTH );
    System.out.println("\n   Welcome to BINGO!!!!\n\n\tThe game can be played using an external file,\n\t a default file, a random board, or numbers from you own input\n");
    System.out.println("   If you would like to use a default bingo board then type \"default\"\n\t( This uses the file \"bingo.in\" )\n");
    System.out.println("   If you would like to use a random bingo board then type \"random\"\n");
    System.out.println("   If you would like to use an external file for the bingo board then type\n\t the name of file containing the numbers for the board\n");
    System.out.println("   If you would like to use user-inputted numbers for the bingo card,\n\tType \"custom\"\n");
    System.out.println("   Only the first 25 integers in any file will be used for the bingo card");
    printLineSeperator( LINE_BREAK_LENGTH );
    System.out.println();
    
  }  
    
  public static void fillCard( int[][] card ){
  //pre-conditions: the opening message has been printed. card must be initialized and empty
  //post-conditions: the 2d array 'card' is filled in one of several ways ( random nums, custom nums, a default file, or another external file ). All of these different ways of filling "card" use unique sets of methods ( besides the default file and other external files which share methods )
    
    Scanner scan = new Scanner( System.in );   
  
    do{//runs until input is given wihch can make a valid BINGO card
        String fileName = scan.nextLine();
        
      switch( fileName ){
        case "random" : 
          fillRandomCard( card );
          return;
        case "custom" :
          fillCustomCard( card );
          return;
        case "default" : fileName = "bingo.in";
          default:
      }
        
      if( fillFromFileSuccess( card, fileName ) )
        return;
          
    }while( true );
         
  }
   
  public static boolean fillFromFileSuccess( int[][] card, String fileName ){
   //pre-conditions: the user has entered something other than "random" or "custom" when prompted by the opening message. "card" must be initialized and empty. "fileName" must be initialized by user input
   //post-conditions: If 'fileName' is the name of a file which can be used for a BINGO card, then 'card' is filled with numbers from 'fileName' and the method returns true. Otherwise, 'card' remains empty and the method returns false;
   
    int exceptionCode = fillFromFile( card, fileName );
    if( exceptionCode != -1 ){
      String[] exceptionMessages = getExceptionMessages( fileName );
      card = new int[ NUM_ROWS ][ NUM_COLS ];
      System.out.println( exceptionMessages[ exceptionCode ] );
      printLineSeperator( LINE_BREAK_LENGTH );
      System.out.println("\n");
      return false;
    }
    return true;
  }
   
  public static String[] getExceptionMessages( String fileName ){
   //pre-conditions: The user has inputted something which cannot be used to generate a BINGO card when prompted to. This is contained in "fileName" which must be initlized for this method
   //post-conditions: An array list of Strings is returned which holds the different messages which are printed for different types of errors which may result from an invalid fileName being entered
   
    String[] exceptionMessages = new String[ NUM_OF_EXCEPTIONS ];
     
    exceptionMessages[ FILE_NOT_FOUND ] = "\nInvalid Input. File not found or typo in input.\nIf you input \"default\" and see this message,\n   the default file \"bingo.in\" cannot be found by this program.\nIf you entered another file name then the file cannot be found by this program.\n\nType a different file name or type \"default\", \"custom\", or \"random\".\nDo not enter any extra characters to the an inputted file name or other input\n(Including spaces)";
    exceptionMessages[ INVALID_INT ] = "\nInvalid Input. Invalid integers.\n\nThe file \""+fileName+"\" does not work for the BINGO card.\nThis is due to the integers in the file.\nThe first 5 integers must be between 1 and 15.\nThe next 5 must be between 16 and 30.\nSame pattern applies for rest of the first 25 numbers.\n\nType a different file name or type \"default\", \"custom\", or \"random\".\nDo not enter any extra characters to the an inputted file name or other input\n(Including spaces).";
    exceptionMessages[ DUPLICATE_INTS ] = "\nInvalid Input. Duplicate integers.\nThere are duplicate integers in the file prior to the first 25 integers in the file.\n\nType a different file name or type \"default\", \"custom\", or \"random\".\nDo not enter any extra characters to the an inputted file name or other input\n(Including spaces).";
    exceptionMessages[ INVALID_CHAR ] = "\nInvalid Input. Invalid characters.\nA non integer appeared in the file \""+fileName+"\" too early.\nThere must be at least 25 integers in the file prior to any non-integers.\n\nType a different file name or type \"default\", \"custom\", or \"random\".\nDo not enter any extra characters to the an inputted file name or other input\n(Including spaces).";
    exceptionMessages[ EMPTY_FILE ] = "\nInvalid Input. The file \""+fileName+"\" is empty.\n\nType a different file name or type \"default\", \"custom\", or \"random\".\nDo not enter any extra characters to the an inputted file name or other input\n(Including spaces).";
     
    return exceptionMessages;
  }
   
  public static int fillFromFile( int[][] card, String fileName ){
  //pre-conditions: The user entered something other than "random", or "custom" when prompted by the opening message. card and fileName must be be initialzed. card must be empty and fileName must contain some user input
  //post-conditions: If 'fileName' is the name of a file which can be used for a BINGO card, then 'card' is filled with numbers from 'fileName' and the method returns -1 (signalling to the calling method that "card" filled properly). Otherwise, "card" is either filled partly from a file or not at all and the method returns an integer associated with a particular type of error in filling "card"

  Scanner scan = new Scanner( System.in );
  final int SUCCESS = -1;
  try{
    scan = new Scanner( new File( fileName ) );
  }catch( Exception e ){
    return FILE_NOT_FOUND;
  }
    
  if( ! scan.hasNext() )
      return EMPTY_FILE;
      
  if( fileName.equals("bingo.in") ){//bingo.in fills using row-major, other files must use column-major
    for(int row = 0; row < NUM_ROWS; row++ ){
      for( int col = 0; col < NUM_COLS; col++ )
        card[row][col] = scan.nextInt();
    }
    return SUCCESS;
  }
  
    ArrayList<Integer> pickedNums = new ArrayList<Integer>();
    int num;
    for(int col = 0; col < NUM_COLS; col++){
      for(int row = 0; row < NUM_ROWS; row ++){
        try{
          num = Integer.parseInt( scan.next() );
          card[row][col] = num;
        }catch( Exception e ){
          return INVALID_CHAR;
        }
        if( pickedNums.contains( num ) )
          return DUPLICATE_INTS;
        pickedNums.add( num );
      }
    }
    
    for( int row = 0; row < NUM_ROWS; row++ ){//checks that the nums in the card work for a BINGO card
      for( int col = 0; col < NUM_COLS; col++ ){
        num = card[row][col];
        int lowerBound = 1 + ( col * 15 );
        int upperBound = ( col + 1 ) * 15;
        boolean numInBounds = ( num >= lowerBound ) && ( num <= upperBound );
        if( !numInBounds )
          return INVALID_INT;
      }
    }
    
    return SUCCESS;
  }
  
  public static void fillRandomCard( int[][] card ){
  //pre-conditions: the user must have typed "random" when prompted by the program. "card" must be initialized
  //post-conditions: the 2d array 'card' is filled with random numbers between 1 and 75. each numbers falls within the range allowed for its particular column
    ArrayList<Integer> generatedNums = new ArrayList<Integer>();
    int num;
    for(int row = 0; row < NUM_ROWS; row++){
		  for(int col = 0; col < NUM_COLS; col ++){
        int lowerBound = 1 + col * 15;
        int upperBound = 15 * ( 1 + col );
        int randomMultiply = upperBound - lowerBound + 1;
        int randomAdd = lowerBound;
        do{
          num = (int)( Math.random()*randomMultiply + randomAdd );
         }while( generatedNums.contains( num ) );
        generatedNums.add( num );
        card[row][col] = num;
      }
    }
  }
  
  public static void fillCustomCard( int[][] card ){
    //pre-conditions: the user inputted "custom" when prompted to input a board type. "card" must be initilialized
    //post-conditions: the 2d array "card" is filled with numbers from the user input in a manner which creates a valid BINGO card
    ArrayList<Integer> pickedNums = new ArrayList<Integer>();
    int num = -1;
    for( int col = 0 ; col < NUM_COLS; col++ ){
      int lowerBound = 1 +col*15;
      int upperBound = (col+1)*15;
      System.out.println("\nType 5 integers between "+lowerBound+" and "+upperBound+"\n");
       // System.out.println("After each individual number, hit enter/return\n");
      for( int row = 0; row < NUM_ROWS; row++ ){
        num = getCustomNum( col, pickedNums );
        if( row < ( NUM_ROWS - 1 ) )
          System.out.println("\nType another integer between "+lowerBound+" and "+upperBound+"\n");
        pickedNums.add(num);
        card[row][col] = num;
      }
    }
  }
  
  public static int getCustomNum( int col, ArrayList<Integer> pickedNums ){
  //pre-conditions: col is between 0 and 4. The user must have entered "custom" when prompted by the program. pickedNums must be initialized
  //post-conditions: an user entered integer that has not been entered already and that can be in the BINGO card in column "col" is returned
    Scanner scan = new Scanner( System.in );
    String validityStatus;
    boolean isItAnInt;
    int num = -1;
    int lowerBound = 1 + col * 15;
    int upperBound = ( col + 1 ) * 15;
    do{//runs until the user inputs a number that is valid for the current column of the board they are putting numbers into
      isItAnInt = false;
      try{
          num = Integer.parseInt( scan.nextLine() );
          isItAnInt = true;
      }catch( Exception e ){
        System.out.printf("\nPlease enter just one integer between %d and %d and nothing else for each line\n\n", lowerBound, upperBound);
        continue;
      }
      
      if( !( num >= lowerBound && num <= upperBound ) )
        System.out.println( "\nThe number must be between "+lowerBound+" and "+upperBound+"\n" );
      else if( pickedNums.contains( num ) )
        System.out.println( "\n"+num+" has already been picked\n" );
      else
        return num;
        
    }while( true );
    
  }
    
  public static void printCard( int[][] card ){
  //pre-conditions: fillCard and the methods it calls have filled "card" with numbers creating a BINGO card
  //post-conditoin: the bingo card is printed into the console in an orderly manner with a header and lines seperating each number
    final int ROW_SEPERATOR_LENGTH = 26;
    System.out.println( "\nYOUR BINGO CARD :\n" );
    System.out.printf("%4s%5s%5s%5s%5s", "B", "I", "N", "G", "O" );
    printLineSeperator( ROW_SEPERATOR_LENGTH );
    for( int row = 0; row < NUM_ROWS; row++ ){
      String printRow = "|";      
      for( int col = 0; col < NUM_COLS; col++ ){
        int num = card[row][col];
        String numAtIndex = ( num == 0 ) ? "X" : ""+num;
        printRow += String.format("%3s |", numAtIndex ) ;
      }
      System.out.print( printRow );
	    printLineSeperator( ROW_SEPERATOR_LENGTH );
    }
    
  }
  
  public static void printLineSeperator( int n ){
  //pre-conditions: n is greater than 0.
  //post-conditions: subtraction signs are printed in a row on a new line and anything being printed to the console after it will be on a new line. The number of substraction signs printed is equal to the parameter "n"
    System.out.println();
    for( int x = 0; x < n; x ++ )
      System.out.print("-");
    System.out.println();
  }

  public static void playGame( int[][] card ){
  //pre-conditions: 2d array 'card' has been filled with numbers by fillCard and the methods it calls
  //postconditions: The 2d array 'card' will have all the picked numbers changed to 0. All the numbers guessed are printed with a header. The BINGO card is printed. A message saying what type of win(s) the user got is displayed along with the number of guesses it took
    printCard( card );
    BitSet wins;
    ArrayList<Integer> guessedNums = new ArrayList<Integer>();
	  do{
	    markCard( guessNewNum( guessedNums ), card );  
	    wins = checkWin( card );
	  }while( wins.isEmpty() );
     //isEmpty() found on https://docs.oracle.com/javase/7/docs/api/java/util/BitSet.html
     printPickedNumbers( guessedNums );
     displayWinMessage( wins, guessedNums.size() );
     printCard( card );
  }
  
  public static void markCard( int findNum, int[][] card ){
  //pre-condition: the 2d array 'card' has been filled with numbers by fillCard and the methods it calls, findNum must be between 1 and 75 and must not have already guessed by the game 
  //post-conditions: "card" is changed so that wherever "findNum" was, there is now a 0
  
	  for( int row = 0; row < NUM_ROWS; row++ ){
		  for( int col = 0; col < NUM_COLS; col++ ){
			  if( card[row][col] == findNum ){
				  card[row][col] = 0;
				  return;
			  }
		  }
	  }	
  }
  
  public static int guessNewNum( ArrayList<Integer> guessedNums ){
  //pre-conditions: pickedNums has been initialized
  //post-conditions: a number between 75 and 1 not already in guessedNums when this method is called is added to guessedNums and that number is returned
	  int num = -1;
	  do{
  	  num = (int)(Math.random()*75+1);
	  }while( guessedNums.contains( num ) );
    guessedNums.add( num );
	  return num; 
  }
  
  public static void displayWinMessage( BitSet wins, int numPicks ){
    //pre-conditions: the game must have been one. at least one value in "wins" is true. numPicks must be between 5 and 75
    //post-conditions: the appropriate win message(s) are printed for the type of win(s) that have occured
    if( wins.get(VERTICAL) )
      System.out.printf("\n\nYOU WIN WITH A VERTICAL BINGO AFTER %d PICKS!\n", numPicks );
    if( wins.get(HORIZONTAL) )
      System.out.printf("\n\nYOU WIN WITH A HORIZONTAL BINGO AFTER %d PICKS!\n", numPicks );
    if( wins.get(DIAGONAL) )
      System.out.printf("\n\nYOU WIN WITH A DIAGONAL BINGO AFTER %d PICKS!\n", numPicks );
  }
  
  public static void printPickedNumbers( ArrayList<Integer> pickedNums ){
  //pre-condition: the game has been won and all the numbers picked are in pickedNums. pickedNums.size() must be between 5 and 75
  //post-conditoin: all the picked numbers are printed in an orderly manner along with a header
    System.out.println( "\nBINGO NUMBERS PICKED AT RANDOM FROM BIN :" );
    for( int x = 0; x < pickedNums.size(); x++ ){
       System.out.print( String.format("%-8s", pickedNums.get(x) ) );
       if( (x+1) % 9 == 0 )//makes sure 9 numbers are printer per line
          System.out.println();
    }
  }

  public static BitSet checkWin( int[][] card ){
  //pre-condition: "card" must be initialized and full of values using fillCard and the methods it calls
  //post-condition: a BitSet of length three is returned with between 0 and 3 of th evalues in it true. Each value corresponds with whether or not there is a particular type of win
    final int NUM_DIFF_WINS = 3;
    BitSet wins = new BitSet( NUM_DIFF_WINS );
  
	  for( int col = 0; col< NUM_COLS; col++ ){//checks for vertical wins
		  int columnSum = 0;
		  for( int row = 0 ; row < NUM_ROWS; row++ )
			  columnSum += card[row][col];
		  if( columnSum == 0 ){
			  wins.set( VERTICAL );
        break;
      }
    }
      
    for( int[] row : card ){//checks for horizontal wins
      int rowSum = 0;
      for( int num : row )
        rowSum += num;
      if( rowSum == 0 ){
        wins.set(HORIZONTAL);
        break;
      }
    }
      
    int diagonalSum = 0;//checls the bottom-left to top-right diagonal
    for( int index = 0; index < 5; index++ )
      diagonalSum += card[ index ][ index ];
    if( diagonalSum == 0 )
      wins.set(DIAGONAL);
 
    diagonalSum = 0;//checks the bottom-right to top-left diagonal
    for( int index = 4; index >= 0; index-- )
		  diagonalSum += card[ index ][ index ];
    if( diagonalSum == 0 )
      wins.set(DIAGONAL);
 
    return wins; 
  }

}

  
