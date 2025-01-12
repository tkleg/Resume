import java.util.*;
import java.io.*;

public class TimeShare{

  //fill inputQueue and assign it to a variable
  //note: initalize startTime to -1 for all jobs so that a value of -1 represents it not starting

  public static void main( String[] args )throws Exception{
    if( args.length == 0 ){
     System.out.println("File name must be given in command line.");
     System.exit(1);
    }
    Queue inputQueue = inputJobs( args[0] );
    
    Object[] results = processAndRun( inputQueue );//this whole block sorts out the output from processAndRun so it can be passed onto printJobs
    
    printResults( results );
    
  }
  
  public static Queue inputJobs( String fileName ){
    //pre-conditions: the user entered at least one file name in the command line
    //post-conditions: the inputQueue is returned if the file given can be found and has valid input data
    Scanner scan = null;
    try{
      scan = new Scanner( new File( fileName ) );
    }catch( FileNotFoundException e ){
      System.out.println("\nThe file with the name " + fileName + " cannot be found.\nPlease try a different file name or attempt to move the file you entered...\n...into a directory accessible by this program.\n");
      System.exit( 1 );
    }catch( Exception e ){
      System.out.println( e.getMessage() );
    }
        
    return fillInput( scan );
    
  }
  
  public static Queue fillInput( Scanner scan ){
    //pre-condition: the file name given on the command line can be found
    //post-condition: the inputQueue is filled and returned if the data in the file is valid, otherwise an erorr message is printed and the program is stopped
    Queue inputQueue = new Queue();
    try{
      int jobNum = 0;//used to check which job number should be next in the file
      while( scan.hasNext() ){
        jobNum++;
        buildJob( jobNum, inputQueue, scan );
      }
    }catch( IllegalArgumentException e ){
      System.out.println("\nFile has invalid data. Please refer to the sample job files to see how the file should be formatted.\n");
      System.exit(1);
    }catch( Exception e ){
      System.out.println( e.getMessage() );
      System.exit(1);
    }
    
    return inputQueue;
     
  }
  
  public static void buildJob( int jobNum, Queue inputQueue, Scanner scan )throws Exception{
    String jobIdentifier = scan.next();
    String correctJob = "job" + jobNum;
    if( jobIdentifier.length() != 4 || ! jobIdentifier.equals( correctJob ) )
      throw new Exception("\nError: Job names must be job1, job2, job3, etc.\n");
    int arrivalTime = Integer.parseInt( scan.next() );
    int runTime = Integer.parseInt( scan.next() );
    if( arrivalTime < 0 || runTime < 1 )
      throw new Exception("\n\nError: Invalid integers.\nArrival time or run time out of range.\nArrival time and run time must both be greater than 0.\n");
    inputQueue.enqueue( new Job( "job"+jobNum, arrivalTime, runTime ) );
  }
  
  
  public static Object[] processAndRun( Queue inputQueue ){
    //pre-conditions: the file name given on the command line was valid and the inputQueue was successfully filled form it
    //post-conditions: the inputQueue is emptied. Then the finishQueue, cpu Usage, cpu Idle, and cpu usage percent are filled and returned together in a single Object array
    Queue jobQueue = new Queue();
    Queue finishQueue = new Queue();
    int clockTime = 1, idle = 0, usage = 0;
    while( ! inputQueue.isEmpty() || ! jobQueue.isEmpty() ){
      
      arriveNew( inputQueue, jobQueue, clockTime );//step 1 general control logic
      finishedJob( jobQueue, finishQueue, clockTime );//step 2 general control logic
      startJob( jobQueue, clockTime );//step 3 general control logic
    
      if( jobQueue.isEmpty() && ! inputQueue.isEmpty() )//step 4 general control logic
        idle++;
      else if( ! jobQueue.isEmpty() )
        usage++;
      //end step 4 general control logic
    
      clockTime++;//step 5 general control logic
      //end step 5 general control logic
    }
    
    Object[] results = new Object[4];//puts all the information needed from this method into one array so they can all be returned at once and immediatley passed to the printJobs method
    results[0] = finishQueue;
    results[1] = new Double( idle );//CPU idle time
    results[2] = new Double( usage );//CPU usage time
    double percent = ( 1.0 * usage ) / ( usage + idle );
    results[3] = new Double( percent * 100 );//CPU usage %
    
    return results;
  }
  
  private static void arriveNew( Queue inputQueue, Queue jobQueue, int clockTime ){//pre-conditions: inputQueue is filled with data
  //post-conditions: the top job object in the input queue is removed and put it in the jobQueue if its arrival time is equal to the clockTime
  
    if( inputQueue.isEmpty() )
      return;
    
    Job front = (Job) inputQueue.front();
    if( front.arrivalTime == clockTime )
        jobQueue.enqueue( inputQueue.dequeue() );
        
  }
  
  private static void finishedJob( Queue jobQueue, Queue finishQueue, int clockTime ){
    //pre-conditions: the jobQueue has at least one Job object in it
    //post-conditions: the top job in the jobQueue is removed and added to the finishQueue if the runTime = clockTime - startTime 
    if( jobQueue.isEmpty() )
      return;
      
    Job front = (Job) jobQueue.front();
    if( front.startTime != -1 && front.runTime == ( clockTime - front.startTime ) ){
      front.turnTime = clockTime - front.arrivalTime;
      finishQueue.enqueue( jobQueue.dequeue() );
    }
  }
  
  private static void startJob( Queue jobQueue, int clockTime ){
    //pre-conditions: the jobQueue has at least one Job object in it
    //post-conditions: the front Job object in the jobQueue has its startTime set to the current clockTime
  
    if( jobQueue.isEmpty() )
      return;
      
    Job front = (Job) jobQueue.front();
    if( front.arrivalTime <= clockTime && front.startTime == -1 ){
      front.startTime = clockTime;
      front.waitTime = clockTime - front.arrivalTime;
    }
    
  }
  
  private static void printResults( Object[] results ){
    //pre-conditions: the finishQueue in the array results is filled, the three double values in the array are initialized
    //post-conditions: all the data from the results array is printed in a neat manner
    
    Queue finishQueue = ( Queue ) results[0];
    double idle = ( (Double) results[1] ).doubleValue();
    double usage = ( (Double) results[2] ).doubleValue();
    double percentUsage = ( (Double) results[3] ).doubleValue();
    
    clearScreen();
    String header = "Job Control Analysis: Summary Report";
    System.out.println("\n"+header);
    for( int x = 0; x < header.length(); x++ )
      System.out.print("-");
    System.out.println("\n\njob id    arrival    start    run    wait    turnaround");
    System.out.println("\t  time       time     time   time    time");
    System.out.println("------    -------    -----    ----   ----    ----------");
    System.out.println();
    double totalWait = 0;
    int size = 0;
    while( ! finishQueue.isEmpty() ){
      Job j = (Job) finishQueue.dequeue();
      totalWait += j.waitTime;
      size++;
      System.out.println( j );
    }
    
    System.out.println();
    
    System.out.printf("%s%.2f%s", " Average Wait Time => ", (totalWait/size), "\n" );
    System.out.printf("%s%.2f%s", "         CPU Usage => ", usage, "\n" );
    System.out.printf("%s%.2f%s","          CPU Idle => ", idle, "\n" );
    System.out.printf("%s%.2f%s","     CPU Usage (%) => ", percentUsage, "%\n" );    
    
  }
  
  public static void clearScreen(){
    //pre-conditions: none
    //post-conditions: everything currently on the screen is cleared
      System.out.println("\u001b[H\u001b[2J");
    }
    
}
