import java.io.*;

class HourlyEmployee extends Employee implements Serializable{
    
    public HourlyEmployee( String name, double wage ){
      super( name, wage, "hour" );
    }
  
    public double computePay( double hours ){
      double pay = 0;
      if( hours <= 40 )
        return wage * hours;
      else
        return wage * 40 + 1.5*wage*( hours - 40 );
    }
    
    protected double correctWage(){
      return wage;
    }
    
  }