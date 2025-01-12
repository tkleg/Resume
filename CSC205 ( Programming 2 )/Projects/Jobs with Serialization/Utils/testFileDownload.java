import java.util.*;
import java.io.*;

public class testFileDownload{

	public static void main( String[] args ){
    //pre-condition: the user entered "u" when prompted by the menu
    //post-conditions: all employee objects stored in the file named "employee.dat" are saved to the parameter ArrayList object
    String fileName = "employee.dat";
    ArrayList<Employee> workers = new ArrayList<Employee>();
    try {
      FileInputStream fileIn =
        new FileInputStream(fileName);
      ObjectInputStream in =
        new ObjectInputStream(fileIn);
      Employee newEmployee;
      while( workers.size() >= 0 ){
          newEmployee = (Employee) in.readObject();
          
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
      
      for( Employee worker : workers )
        System.out.println( worker.getName() );
  }
}