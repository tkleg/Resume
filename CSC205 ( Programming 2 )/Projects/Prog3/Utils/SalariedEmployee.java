import java.io.*;

class SalariedEmployee extends Employee implements Serializable{
       
    public SalariedEmployee( String name, double wage ){
      super( name,  ( wage / ( 52*40 ) ), "year" );
    }
    
    public double computePay( double hours ){
      return wage*40;
    }
    
    protected double correctWage(){
      return wage * 52 * 40 ;
    }
    
  }