import java.util.*;
import java.io.*;

public class Library{

    public static void main( String[] args ){
      printOpenerMessage();
      ArrayList<LibraryBook> books = getBooks();
      sortBooks( books );
      System.out.println("\n\tA total of "+books.size()+" have been input & sorted by title\n");
      System.out.print("\tPlease Hit Return to Continue...");
      if( new Scanner( System.in ).nextLine().contains("") )
        runDatabase( books );
    }
    
    public static void clearScreen(){
    //pre-conditions: none
    //post-conditions: everything currently on the screen is cleared
      System.out.println("\u001b[H\u001b[2J");
    }
    
    public static void printOpenerMessage(){
    //pre-conditions: none
    //post-conditions: a message explaining what the program is gets printed in a neat format
      clearScreen();
      String header = "THE BOOK SEARCH PROGRAM";
      System.out.println( getChars( ' ', 28 ) + header );
      System.out.println( getChars( '-', 56 + header.length() ) );
      System.out.println("\n\tWhat file is your book data stored in?\n\t");
      
    }
      
    public static String getChars( char c, int n ){
    //pre-conditions: n must be over 0
    //post-conditions: a String containing 'n' many 'c''s is returned
      String s = "";
      for( int x = 0; x < n; x++ )
         s += c;
      return s;
    }
    
    public static ArrayList<LibraryBook> getBooks(){
      //pre-conditions: the package this class is in has at least one valid file which can be used to make LibraryBook objects
      //post-conditions: an array list containing a library book object for every library book in the user picked file is returned
      
      ArrayList<String> fileNames = getFileNames();
      
      String usedFileName = getUsedFileName( fileNames );
      
      Scanner scanFile = null;
      try{
      scanFile = new Scanner( new File( usedFileName ) );
      }catch( IOException e ){};
      
      return inputBooks( scanFile );
    
    }
    
    public static ArrayList<LibraryBook> inputBooks( Scanner scanFile ){
    //pre-conditions: scanFile scans a file which holds only text which can be made into a LibraryBook object
    //post- an array list containing a library book object for every library book in the user picked file is returned
      ArrayList<LibraryBook> books = new ArrayList<LibraryBook>();
        while( scanFile.hasNext() ){
          Scanner lineScan = new Scanner( scanFile.nextLine() ).useDelimiter(";");
          String title = lineScan.next();
          String name = lineScan.next();
          int copyright = lineScan.nextInt();
          double price = lineScan.nextDouble();
          String genre = lineScan.next();
          books.add( new LibraryBook ( title, name, copyright, price, genre ) );
        }
      return books;
    }    
    
    public static ArrayList<String> getFileNames(){
      //pre-conditions: the package this class is in has at least one valid file which can be used to make LibraryBook objects
      //post-conditions: the name of every file that is in the same package as this class file and ends in ".dat" is returned in a String ArrayList
    
      ArrayList<String> usableFiles = new ArrayList<String>();
      
      String[] files = new File(".").list();
      for( String s : files ){
        if( s.endsWith(".dat") )
          usableFiles.add( s );
      }
      
      return usableFiles;
      
    }
    
    public static String getUsedFileName( ArrayList<String> fileNames ){
    //pre-conditions: fileNames has a size of at least 1
    //post-conditions: one user picked String from fileNames is returned
      Scanner scan = new Scanner( System.in );
      String inputName = null;
      boolean firstRun = true;
      
      do{
      
        if( !firstRun )
          System.out.println("\n\t** Can't open input file. Try again. **\n");
        firstRun = false;
        
        System.out.print("\tHere are the files in the current directory :\n\t");
        
        for( String file : fileNames )
          System.out.print( file + "\t" );
        
        System.out.print("\n\n\tFilename : ");
        inputName = scan.next();
        
      }while( !( fileNames.contains( inputName ) ) );
           
      return inputName;
      
    }

    public static void sortBooks( ArrayList<LibraryBook> books ){
    //pre-conditions: books has been filled with LibraryBook objects
    //post-conditoins: books is sorted according to alphabetical order of the book's titles
      for( int outer = 0; outer < books.size(); outer++ ){
        int minBookIndex = outer;
        for( int inner = outer; inner < books.size(); inner++ ){
          if( books.get( inner ).compareTo( books.get(minBookIndex) ) < 0 )
            minBookIndex = inner;     
        }
        if( books.get( outer ).compareTo( books.get( minBookIndex ) ) != 0 ){
          LibraryBook temp = books.get( outer );
          books.set( outer, books.get( minBookIndex ) );
          books.set( minBookIndex, temp );
        }
      }
   }   
   
   public static void runDatabase( ArrayList<LibraryBook> books ){
   //pre-conditions: books is filled with at least one LibraryBook object
   //post-conditions: the program displays the menu, then it either ends, displays books, or allows the user to search through books, depending on user input
     int input = runMenu();
     switch( input ){
       case 1: displayRecords( books );
         break;
       case 2: searchByTitle( books );
         break;
       case 3: System.out.print("\n\tGoodbye. Have a nice day. :-)\n\n");
         System.exit(1);
       default: break;
     }
       
   }
   
   public static int runMenu(){
   //pre-conditions: the user entered a usable file name when prompted by the program
   //post-conditions: an integer is returned representing what the user wants to do with the database 
     Scanner scan = new Scanner( System.in );
     int input = 0;
     do{
       printMenu();
       try{
         input = Integer.parseInt( scan.nextLine() );
         if( input > 3 || input < 1 )
           throw new Exception();
       }catch( Exception e ){
         System.out.println("\n\tYou have made an error. Please try again.\n");
         System.out.print("\tPlease Hit Return to Continue..." );
         if( new Scanner( System.in ).nextLine().contains("") )
           continue;
       }
       break;//reachable only if input is valid
     }while( true );
       
     return input;
       
   }
   
   public static void printMenu(){
   //pre-conditions: the user has entered a valid file name to get LibraryBook objects from
   //post-conditions: a menu is diplsayed in a neat format so the user can choose what they want to do with the search program
     clearScreen();
     String header = "THE GREAT BOOKS SEARCH PROGRAM";
     System.out.println("\t" + getChars( '^', 22 + header.length() ) );
     System.out.println( getChars( ' ', 20 ) + header );
     System.out.println("\t" + getChars( '^', 22 + header.length() ) );
     System.out.println("\t1) Display all book records" );
     System.out.println("\t2) Search for a book by Title" );
     System.out.println("\t3) Exit Search Program" );
     System.out.println( "\t"+ getChars( '^', 22 + header.length() ) );
     System.out.print("\tPlease Enter Your Choice > " );
   }
   
   public static void displayRecords( ArrayList<LibraryBook> books ){
   //pre-conditions: the user entered 1 when prompted by the program
   //post-conditions: between 1 and all of the LibraryBook objects in 'books' are displayed in a neat pattern, then the menu is reprinted
     Scanner scan = new Scanner( System.in );
     for( int index = 0; index < books.size(); index++ ){
       clearScreen();
       printRecord( books.get( index ), index );
       System.out.println("\tPlease Hit Return to Continue or M for Menu...\n");
       System.out.println("\tEnter no additional characters (except spaces ) with M\n\n\tThis will make the program display the next book,\n\tinstead of returning\n");
       System.out.print("\tInput: " );
       if( scan.nextLine().trim().equalsIgnoreCase("m") ){
         runDatabase( books );
         return; 
       }    
     }
       runDatabase( books );
   }
   
   public static void printRecord( LibraryBook book, int index ){
   //pre-conditions: book and all of its instance variables are not null and index is above -1
   //post-conditions: all of the data in the object 'book' is printed in a neat format
     String genre = null;
     switch( book.getGenre() ){
       case "f": genre = "Fiction";
         break;
       case "n": genre = "Non-Fiction";
         break;
       case "d": genre = "Drama";
         break;
       case "p": genre = "Poetry";
         break;
       default: break;
     }
     System.out.println( "\tRecord #" + ( index + 1 ) + " :" );
     System.out.println( "\t" + getChars( '^', 48 ) );
     System.out.printf( "%28s%25s%s", "Title :", book.getTitle(),"\n" );
     System.out.printf( "%28s%25s%s", "Author's Name :", book.getAuthor(), "\n" );
     System.out.printf( "%28s%25d%s", "Copyright :", book.getCopyright(), "\n" );
     System.out.printf( "%28s%25.2f%s", "Price :", book.getPrice(), "\n" );
     System.out.printf( "%28s%25s%s", "Genre :", genre, "\n" );
     System.out.println("\t" + getChars( '^', 48 ) );
   
   }
   
   public static void searchByTitle( ArrayList<LibraryBook> books ){
   //pre-conditions: the user entered 2 when prompted by the menu, books must be filled with initialized LibraryBook objects
   //post-conditions: if the user enters the title of a book wihtin 'books', the data for that book gets displayed. Otherwise, a message explaining the book can not be found is printed and the program returns to the menu
     Scanner scan = new Scanner( System.in );
     System.out.print("\n\tSearch Title > ");
     String input = scan.nextLine();
     int first = 0, last = (books.size()- 1), middle = -1;
     do{
       middle = ( first + last ) / 2;
       int searchResult = books.get( middle ).getTitle().compareTo( input );
       if( searchResult == 0 ){
         printSearchedBook( books, middle );
         if( scan.nextLine().contains("") )
           runDatabase( books );
         return;
       }
       else if( searchResult > 0 )
         last = middle -1;
       else
         first = middle + 1;
     }while( first <= last );
     System.out.println("\n\tSorry, the book was not found.\n");
     System.out.print("\tPlease Hit Return to Continue... ");
     if( scan.nextLine().contains("") )
       runDatabase( books );
   }
   
   public static void printSearchedBook( ArrayList<LibraryBook> books, int index ){
   //pre-conditions: books is filled with initialized LibraryBook objects, an object exists in 'books' at index 'index'
   //post-conditions: the data for the LibraryBook object at index 'index' is printed in a neat format along with a message saying it was found
     clearScreen();
     System.out.println("\n\tBook Found in Alphabetized List in :\n" );
     printRecord( books.get( index ), index );
     System.out.print("\n\tPlease Hit Return to Continue... ");
     if( new Scanner( System.in ).nextLine().contains("") )
       runDatabase( books );
   }

}