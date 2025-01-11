import java.util.*;

public class Employee extends Person{

  public double salary;
  public Date employment_date;
  
  public Employee( double salary, Date employment_date, String lastName, String firstName, Date birthDate ){
    super( lastName, firstName, birthDate );
    this.salary = salary;
    this.employment_date = employment_date;
  }
  
  public String toString(){
    String s ="";
    s += "name = " + getLastName() +", " + getFirstName() + "\n";
    s += "salaray = " + salary + "\n";
    s += "birth = " + getBirthDate() + "\n";
    s += "hired = " + employment_date + "\n";
    return s;
  }
  
}
  