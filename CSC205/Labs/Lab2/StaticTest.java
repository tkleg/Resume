public class StaticTest
{
    public static void main(String args[])
    {
        Person tom = new Person("Tom Jones");
        System.out.println("Person.getCount(): " + Person.getCount());
        System.out.println(tom);
	System.out.println();

        Person sue = new Person("Susan Top");
        System.out.println("Person.getCount(): " + Person.getCount());
        System.out.println(sue);
	System.out.println("sue.getCount(): " + sue.getCount());
	System.out.println();

        Person fred = new Person("Fred Shoe");
        System.out.println("Person.getCount(): " + Person.getCount());
        System.out.println(fred);
	System.out.println();

	System.out.println("tom.getCount(): " + tom.getCount());
	System.out.println("sue.getCount(): " + sue.getCount());
	System.out.println("fred.getCount(): " + fred.getCount());

	Person samplePerson = new Person();
	samplePerson.reset( "Troy Kleger", 5937 );
	System.out.println("My name is " + samplePerson.getName() );
	System.out.println("My id is " + samplePerson.getId() );
    }
}
