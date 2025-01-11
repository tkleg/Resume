public class Person
{
  private String name;
  private int    id;
  private static int personCount = 0;

  // constructor
  public Person(String pname)
  {
    name = pname;
    personCount++;
    id = 100 + personCount;
  }

  public Person(){
    name = "N/A";
    id = -1;
    personCount++;
  }

  public void reset( String newName, int newId ){
    name = newName;
    id = newId;
  }

  public String getName(){
    return name;
  }

  public int getId(){
    return id;
  }

  public String  toString()
  {
    return "name: " + name + "  id: " + id 
      + "  (Person count: " + personCount + ")";
  }

  // static/class method
  public static int getCount()
  {
    return personCount;
  }
  
}
