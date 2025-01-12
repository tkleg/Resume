
public class CheckingAccount extends Account{

  private static int numChecks;
  
  public CheckingAccount( double balance ){
    super( balance );
    numChecks = 0;
  }
  
  public int getChecksWritten(){
    return numChecks;
  }
  
  public void writeCheck( double payment ){
    withdraw( payment );
    numChecks++;
  }
  
  

}

