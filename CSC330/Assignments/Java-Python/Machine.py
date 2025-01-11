from Drink import *
import warnings

warnings.filterwarnings('always')

if __name__ == "__main__":

    drink1 = Drink("Coke Zero")
    drink2 = Drink("Ginger Ale")
    drink3 = Drink("Pedialyte", 3.75)
    drink4 = Drink("Bud Light", 1.00 )

# Fill machine

    drink1.refill()
    drink2.refill()
    drink3.refill()
    drink4.refill()

# Buy 8 Cokes

    drink1.vend()
    drink1.vend()
    drink1.vend()
    drink1.vend()
    drink1.vend()
    drink1.vend()
    drink1.vend()
    drink1.vend()

# Buy 6 Sprites

    drink2.vend()
    drink2.vend()
    drink2.vend()
    drink2.vend()
    drink2.vend()
    drink2.vend()

# Buy 2 Doctor Peppers

    drink3.vend()
    drink3.vend()

# Buy 11 Guinness

    drink4.vend()
    drink4.vend()
    drink4.vend()
    drink4.vend()
    drink4.vend()
    drink4.vend()
    drink4.vend()
    drink4.vend()
    drink4.vend()
    drink4.vend()
    drink4.vend()

    totalSold = ( drink1.drinksSold() + drink2.drinksSold() +
                  drink3.drinksSold() + drink4.drinksSold() )

    totalProfit = ( drink1.profit() + drink2.profit() +
                    drink3.profit() + drink4.profit() )

    print("A Total of " + str(totalSold) + " drinks were ")
    print("sold for a profit of $" + str(totalProfit))
    print()
    print( str(drink1.restockAmount()) + " " + drink1.getDrinkName() + " needed to restock machine")
    print( str(drink2.restockAmount()) + " " + drink2.getDrinkName() + " needed to restock machine")
    print( str(drink3.restockAmount()) + " " + drink3.getDrinkName() + " needed to restock machine")
    print( str(drink4.restockAmount()) + " " + drink4.getDrinkName() + " needed to restock machine")
