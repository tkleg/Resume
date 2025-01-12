public class Drink {

// the following will be class variables

   final int MAXIMUM_CAPACITY = 10;
   final double DEFAULT_DRINK_COST = 1.75;

   private int available, consumed;
   private int useDefaultCost, useSuppliedCost;
   private double drinkCost, moneyMade;
   private String name;

// Start defining constructors here...

// This constructor sets the name of the drink only.

   public Drink (String brandName) {
      name = brandName;
      consumed = 0;
      available = 0;
      moneyMade = 0.0;
      drinkCost = DEFAULT_DRINK_COST;
      useDefaultCost = 1;
      useSuppliedCost = 0;
   }

   public Drink (String brandName, double cost) {
      name = brandName;
      consumed = 0;
      available = 0;
      moneyMade = 0.0;
      drinkCost = cost;
      useDefaultCost = 0;
      useSuppliedCost = 1;
   }

// This is the basic vend method.  
   public void vend () {
      if ( available > 0 ) {
         available -= 1;
         consumed += 1;
         moneyMade += ( useDefaultCost * DEFAULT_DRINK_COST +
                        useSuppliedCost * drinkCost );
         System.out.println(name + " Puchased.");
         }
      else {
         System.out.println("************");
         System.out.println("* SOLD OUT *");
         System.out.println("************");
        }
     }


// Add a "setter" function called fillDrinks to set the number of
// drinks to their maximum capacity.
   public void refill () {
      available = MAXIMUM_CAPACITY;
      }


   public double profit () {
      return Math.round(moneyMade*100.0)/100.0;
      }


   public int drinksSold () {
      return consumed;
      }

   public String getDrinkName () {
      return name;
      }

   public int restockAmount () {
       return MAXIMUM_CAPACITY - available;
   }
}
