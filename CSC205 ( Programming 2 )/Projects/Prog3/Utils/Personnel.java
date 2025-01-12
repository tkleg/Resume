import java.util.*;
import java.io.*;

public class Personnel implements Serializable{

  private static final int COMMAND_SEPERATOR_LENGTH = 34;
  private static final int NUM_COMMANDS = 10;
  
	public static void main( String[] args ){
     ArrayList<Employee> workers = new ArrayList<Employee>();
     String menu = getMenu();
     while( true ){
       System.out.print( menu );
       callACommand( workers );
     }
	}

  private static String getMenu(){
    //pre-conditions: none
    //post-conditions: a String object containing the entirety of the menu is returned to be printed in the main method
    String menu = "\n";
    
    String[] commands = new String[ NUM_COMMANDS - 1 ];
    commands[0] = "f - Fire employee";
    commands[1] = "c - Compute paychecks";
    commands[2] = "r - Raise wages";
    commands[3] = "p - Print records";
    commands[4] = "d - Download data";
    commands[5] = "u - Upload data";
    commands[6] = "x - Delete downloads";
    commands[7] = "z - Clear database";
    commands[8] = "q - Quit";
      
    for( int x = 0; x < COMMAND_SEPERATOR_LENGTH; x++ )
      menu += '-';
      
    menu += String.format("%s%-22s%s", "\n|Commands: ", "n - New employee","|\n");
    
    for( String command : commands )
        menu += String.format("%-11s%-22s%s", "|", command,"|\n");
    
    for( int x = 0; x < COMMAND_SEPERATOR_LENGTH; x++ )
      menu += '-';
      
    menu += "\nEnter commands: ";
    return menu;
  }

  private static void callACommand( ArrayList<Employee> workers ){
    //pre-conditions: the program just started running or the user did something other than quit the program after the menu prompted it
    //post-conditions: the apropriate menu action is called based off the user input
    Scanner scan = new Scanner( System.in );
    switch( scan.next().trim().toLowerCase() ){
      case "n" :
        createEmployee( workers );
        break;
      case "f" :
        fireEmployee( workers );
        break;
      case "c" :
        displayPay( workers );
        break;
      case "r" :
        raiseWages( workers );
        break;
      case "p" :
        printRecords( workers );
        break;
      case "d" :
        downloadData( workers, false );
        break;
      case "u" :
        uploadData( workers );
        break;
      case "x" :
        deleteFile();
        break;
      case "z" :
        deleteAllEmployees( workers );
        break;
      case "q" :
        quitProgram( workers );
        break;
      default:
        System.out.println("\nCommand was not recognized; please try again.");
      }
  }      
  
  private static void createEmployee( ArrayList<Employee> workers ){
    //pre-conditions: the user entered "n" when the option is printed by the menu
    //post-conditions: a new employee made with user input is added to the parameter if it does not exist already
    Scanner scan = new Scanner( System.in );
    System.out.print("Enter the name of new employee: ");
    String name = scan.nextLine().trim();
    
    //gets salary type
    String workerType = "";
    do{
      System.out.print("Hourly (h) or salaried (s): ");
      workerType = scan.nextLine().trim().toLowerCase();
      boolean invalid = !(workerType.equals("h")) && !(workerType.equals("s"));
      if( invalid )
        System.out.println("Input was not h or s; please try again.");
      else
        break;
      }while( true );
    
    //gets the wage/salary
    double wageOrSalary = 0;
    do{
      if( workerType.equals("s") )
        System.out.print("Enter annual salary: ");
      else
        System.out.print("Enter hourly wage: ");
      try{
        wageOrSalary = Double.parseDouble( scan.nextLine().trim() );
        break;
      }catch( Exception e ){
        System.out.println("Entry invalid, try again.");
      }
    }while( true );
    
    //calls the appropriate consuctor and assigns the result to a variable
    Employee newEmployee;
    if( workerType.equals("s") )
      newEmployee = new SalariedEmployee( name, wageOrSalary );
    else
      newEmployee = new HourlyEmployee( name, wageOrSalary );
      
    //makes sure the new employee is not already hired
    if( ! (duplicateEmployee( newEmployee, workers ) ) )
      workers.add( newEmployee );
    
  } 
  
  private static void fireEmployee( ArrayList<Employee> workers ){
    //pre-condition: the user enters "f" when prompted by the menu
    //post-condition: an employee object may be removed from the parameter
    if( workers.size() == 0 ){
      System.out.println("\nThere are no workers in the database to fire.");
      return;
    }
    printRecords( workers );
    String fireName = "";
    Scanner scan = new Scanner( System.in );
    do{
      System.out.println("\nEnter the name of the employee you wish to fire. Enter nothing and hit enter if you wish to return.");
      fireName = scan.nextLine().trim();
      if( fireName.equals("") )
        return;
      for( int x = 0; x < workers.size(); x++ )
        if( workers.get(x).getName().equalsIgnoreCase( fireName ) ){
          workers.remove(x);
          System.out.println( fireName + " has been fired." );
          return;
        }
      System.out.println("The employee with the name " + fireName + " is not in the database" );
    }while( true );
        
  }
  
  public static void displayPay( ArrayList<Employee> workers ){
    //pre-condition: the user entered "c" when prompted to by the menu
    //post-condition: the amount each worker gets paid for a user input number of hours is displayed unless there are no employees. In that case a message is printed
    if( workers.size() == 0 ){
      System.out.println("\nThere are no workers in the database to display pay for.");
      return;
    }
    Scanner scan = new Scanner( System.in );
    double hours = 0;
    for( Employee worker : workers ){
      do{
        System.out.printf("Enter the number of hours worked by %s: ", worker.getName() );
        try{
          hours = Double.parseDouble( scan.nextLine().trim() );
          break;
        }catch( Exception e ){
          System.out.println("\nInvalid entry. Enter just a decimal or integer and no other characters.\n");
        }
      }while( true );
      System.out.printf("Pay: $%.2f\n", worker.computePay( hours ) );
    }  
  }
  
  private static void raiseWages( ArrayList<Employee> workers ){
    //pre-conditions: the user entered "r" when prompted by the menu
    //post-conditions: the raises of all the employees are raised by a user inputted percentage. If there are no employees in the list, the program prints out a message to the console
    if( workers.size() == 0 ){
      System.out.println("\nThere are no workers in the database to give raises.");
      return;
    }
    Scanner scan = new Scanner( System.in );
    double increase = 0;
    do{
      System.out.print("Enter the percentage increase: ");
      try{
        increase = Double.parseDouble( scan.nextLine().trim() );
        break;
      }catch( Exception e ){
        System.out.println("\nInvalid entry. Enter just a number and no additional characters\n");
      }
    }while( true );
    for( Employee worker : workers )
      worker.giveRaise( increase );
    System.out.println("\nNew Wages");
    printChar( 9, '-' );
    System.out.println();
    for( Employee worker : workers )
      System.out.println( worker.toString() );
  }
  
  private static void printRecords( ArrayList<Employee> workers ){
    //pre-conditions: the user input "p" when prompted by the menu
    //post-conditions: the name, type of employee, and wage of each employee are printed out. If the list is empty, a message is printed out instead
    if( workers.size() == 0 ){
      System.out.println("\nThere are no workers in the database so there are no employee records.");
      return;
    }
    System.out.println("Employees Records");
    printChar( 17, '-' );
    System.out.println();
    for( Employee worker : workers )
      System.out.println( worker.toString() );
  }
  
  private static boolean downloadData( ArrayList<Employee> workers, boolean callFromQuitMethod ){
    //pre-conditions: the user types "d" when prompted by the menu
    //post-conditions: Every employee object in the list is downlnaoded to a file using an OutPutStream. If the list is empty, a message is printed out instead
    //returns true if data is downloaded, returns false if data is not fully downloaded
    if( workers.size() == 0 && !callFromQuitMethod ){
        System.out.println("\nThere are no workers in the database to download.");
      return false;
    }
    uploadData( workers );//needed to prevent workers already in the downloaded file from being erased
    String fileName = "employee.dat";
        try {
          FileOutputStream fileOut =
            new FileOutputStream(fileName);
          ObjectOutputStream out =
            new ObjectOutputStream(fileOut);
          for( Employee worker : workers )
            out.writeObject( worker );
          out.close();
        }
        catch (IOException e) {
          System.out.println(e.getMessage());
          return false;
        }
    return true;
  }
  
  private static void uploadData( ArrayList<Employee> workers ){
    //pre-condition: the user entered "u" when prompted by the menu
    //post-conditions: all employee objects stored in the file named "employee.dat" are saved to the parameter ArrayList object
    String fileName = "employee.dat";
    try {
      FileInputStream fileIn =
        new FileInputStream(fileName);
      ObjectInputStream in =
        new ObjectInputStream(fileIn);
      Employee newEmployee;
      while( workers.size() >= 0 ){
          newEmployee = (Employee) in.readObject();
          if( ! ( duplicateEmployee( newEmployee, workers ) ) )
            workers.add( newEmployee );
      }
        in.close();
      }catch( EOFException e ){//thrown/caught when nothing is left to read and readObject is called
      }catch( FileNotFoundException e ){
        System.out.println("\nThe downloaded employee database does not exist or cannot be accessed.\nThe file is named \"employee.dat\".");
      }catch( InvalidClassException e ){
        System.out.println("\nThe Employee.java file has been changed since the last download of data.\nThis makes the downloaded data unreadable. you will need to erase the data or convert the Employee class to be the exact same as at the time of the last downaload.");
      }catch( Exception e ){
          System.out.println( e.getMessage() );
      }
  }
  
  private static void quitProgram( ArrayList<Employee> workers ){
    //pre-condition: the user entered "q" when prompted by the program
    //post-condition: the program stops if the user enters "yes" or "no". If the user enters "yes", then the parameter is downaloaded to a file, if the user enters "no", the data is not downloaded
    Scanner scan = new Scanner( System.in );
    do{
      System.out.println("\nWould you like to download all current data to the computer so the information is not lost.\nIf so, type \"yes\", if you would like to not download the data type \"no\".\nIf you would like to not exit the program, type \"cancel\".\n");
      String input = scan.nextLine().trim().toLowerCase();
      if( input.equals( "yes" ) ){
        if( downloadData( workers, true ) )
          System.out.println("\nEmployee data downloaded to computer. Have a nice day.\n");
        else
          System.out.println("\nThere is no Employee data to download. Have a nice day.\n");
        System.exit(1);
      }else if( input.equals( "no" ) ){
        System.out.println("\nHave a nice day");
        System.exit(1);
      }else if( input.equals( "cancel" ) ){
        System.out.println("\nProgram termination cancelled. Returning to database.");
        return;
      }else
        System.out.println("\nCommand not recognized, please try again.\n");
    }while( true );
  }
  
  private static boolean duplicateEmployee( Employee potentialHire, ArrayList<Employee> workers ){
    //pre-conditions: an employee object is trying to be added to the ArrayList parameter
    //post-conditions: returns true if potentialHire does not have the same name, wage, and employee type as any employee in the ArrayList workers, otherwise returns false.
    for( Employee worker : workers )
      if( potentialHire.equals( worker ) )
        return true;
    return false;
  }
  
  private static void deleteFile(){
    //pre-condition: the user entered "x" when prompted by the menu
    //post-conditions: if the user enters "yes" the program prints a message then terrminates, otherwise the program returns to the menu to await more user input
    if( ! ( (new File("employee.dat")).exists() ) ){
      System.out.println("\nThe downloaded employee database does not exist or cannot be accessed.\nThe file is named \"employee.dat\".");
      return;
    }
    Scanner scan = new Scanner(System.in);
    System.out.print("\nAre you sure you want to delete the downloaded data? This is irreversible. Enter \"yes\" if so: ");
    if( scan.nextLine().trim().equalsIgnoreCase("yes") ){
      ( new File( "employee.dat" ) ).delete();
      System.out.println( "\nDownloaded data successfuflly deleted." ); 
    }
    else
      System.out.println( "\nDeletion of downloaded data cancelled." );
  }
  
  private static void deleteAllEmployees( ArrayList<Employee> workers ){
    //pre-condition: the user entered "z" when prompted by the menu
    //post-conditoins: if the user enters "yes" when propmted then the ArrayList worker is cleared and a message is printed, otherwise a different message is printed and nothing changes in the parameter
    if( workers.size() == 0 ){
      System.out.println("\nThere are no workers in the database to delete.");
      return;
    }
    Scanner scan = new Scanner(System.in);
    System.out.print("\nAre you sure you want to delete the database data? This is irreversible. Enter just \"yes\" if so: ");
    if( scan.nextLine().trim().equalsIgnoreCase("yes") ){
      workers.clear();
      System.out.println( "\nDatabase data successfuflly deleted." ); 
    }
    else
      System.out.println( "\nDeletion of database data cancelled." );
  }
  
  private static void printChar( int num, char c ){
    //pre-condition: a set number of a certain char needs to be printed in a row. num must be > 0
    //post-conditions: c is printed to the console num times
    for( int x = 0; x < num; x++ )
      System.out.print(c);
  }
}


/*

    Note 1: This try catch block's purpose is to prevent null from being printed while objects are being read while still allowing errors that arise to be printed. I used a catch block that just caught a base Exception then immediately printed out the exception caught so I could see what exception I needed to have in the catch block ( this ended up being an EOFException ). Unfortunately the block needs to be inside the while loop because otherwise the compiler sees the loop as infinite and throws an error

*/
