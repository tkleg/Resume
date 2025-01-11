#include <iostream>
#include <math.h>
#include "Drink.h"

// Constructors
Drink::Drink(string brandName) {
    name = brandName;
    consumed = 0;
    available = 0;
    moneyMade = 0.0;
    drinkCost = DEFAULT_DRINK_COST;
    useDefaultCost = 1;
    useSuppliedCost = 0;
}

Drink::Drink(string brandName, double cost) {
    name = brandName;
    consumed = 0;
    available = 0;
    moneyMade = 0.0;
    drinkCost = cost;
    useDefaultCost = 0;
    useSuppliedCost = 1;
}

// Class methods
void Drink::vend() {
    if (available > 0) {
        available -= 1;
        consumed += 1;
        moneyMade += (useDefaultCost * DEFAULT_DRINK_COST + useSuppliedCost * drinkCost);
        cout << name << " purchased." << endl;
    } else {
        cout << "************" << endl;
        cout << "* SOLD OUT *" << endl;
        cout << "************" << endl;
    }
}

void Drink::refill() {
    available = MAXIMUM_CAPACITY;
}

double Drink::profit() {
    return round(moneyMade * 100.0) / 100.0;
}

int Drink::drinksSold() {
    return consumed;
}

string Drink::getDrinkName() {
    return name;
}

int Drink::restockAmount() {
    return MAXIMUM_CAPACITY - available;
}
