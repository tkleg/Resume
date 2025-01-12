public class TestEmployee{

  public static void main( String[] args ){
  
    Date hireDate = new Date();
    Date birthDate = new Date( 1908, 3, 8 );
    
    Employee e = new Employee( 40000, hireDate, "Brown", "Morris", birthDate );
    System.out.print(e);
  }
  
}