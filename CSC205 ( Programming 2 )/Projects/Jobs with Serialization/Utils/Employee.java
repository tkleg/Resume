import java.io.Serializable;

abstract class Employee implements Serializable{
    String name;
    double wage;
    protected String wageType;
    
    public Employee( String name, double wage, String wageType ){
      this.name = name; 
      this.wage = wage;
      this.wageType = wageType;
    }
    
    protected String getName(){
      return name;
    }
  
    protected void setName( String name ){
      this.name = name;
    }
  
    protected double getWage(){
      return wage;
    }
  
    protected void setWage( double wage ){
      this.wage = ( (int) ( wage * 100 ) ) / 100.0;
    }
  
    protected void giveRaise( double raise ){
      wage *= 1 + ( raise / 100 );
    }
  
    protected boolean equals( Employee worker2 ){
        boolean sameType = this.wageType.equals( worker2.wageType );
        boolean sameWage = this.wage == worker2.wage;
        boolean sameName = this.name.equals( worker2.name );
        return sameType && sameWage && sameName;
    }
    
    public String toString(){
      double workerWage = this.correctWage();
      String formattedWage = String.format( "%.2f", workerWage );
      String endToString = "$"+formattedWage+"/"+wageType;
      if( endToString.length() + name.length() >= 40 )
        return name + "\t    " + endToString;
      int numSpaces = 40 - name.length();
      return String.format("%s%" + numSpaces +"s", name, endToString );
    }
    
    protected abstract double computePay( double hours );
    
    protected abstract double correctWage();
  
  }