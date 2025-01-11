#include <iostream>
#include <math.h>

using namespace std;

class Drink {
    public:
        // Class constants
        int MAXIMUM_CAPACITY = 10;
        double DEFAULT_DRINK_COST = 1.75;

    private:
        // Class variables
        int available;
        int consumed;
        int useDefaultCost;
        int useSuppliedCost;
        double drinkCost;
        double moneyMade;
        string name;

    public:
        // Constructors
        Drink(string brandName);
        Drink(string brandName, double cost);

        // Class methods
        void vend();
        void refill();
        double profit();
        int drinksSold();
        string getDrinkName();
        int restockAmount();
};
