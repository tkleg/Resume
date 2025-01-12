#include <iostream>
#include <vector>

using namespace std;

#include "Drink.h"

int main() {
    // Create a vector of Drink objects to represent the vending machine
    vector<Drink> drinks;

    // Add four drinks to the vending machine
    drinks.push_back(Drink("Coke"));
    drinks.push_back(Drink("Sprite"));
    drinks.push_back(Drink("Doctor Pepper"));
    drinks.push_back(Drink("Guinness", 6.25));

    // Fill all of the drinks
    for (int i = 0; i < drinks.size(); i++) {
        drinks[i].refill();
    }

    // Purchase 8 Cokes
    for (int i = 0; i < 8; i++) {
        drinks[0].vend();
    }

    // Purchase 6 Sprites
    for (int i = 0; i < 6; i++) {
        drinks[1].vend();
    }

    // Purchase 2 Doctor Peppers
    for (int i = 0; i < 2; i++) {
        drinks[2].vend();
    }

    // Purchase 11 Guinness
    for (int i = 0; i < 11; i++) {
        drinks[3].vend();
    }

    // Compute and print out the total number of drinks sold and the total profit
    int totalSold = 0;
    double totalProfit = 0.0;

    for (int i = 0; i < drinks.size(); i++) {
        totalSold += drinks[i].drinksSold();
        totalProfit += drinks[i].profit();
    }

    cout << "A total of " << totalSold << " drinks were sold for a profit of $" << totalProfit << endl;
    cout << endl;

    // Print out the restock amount for each drink
    for (int i = 0; i < drinks.size(); i++) {
        cout << drinks[i].restockAmount() << " " << drinks[i].getDrinkName() << " needed to restock machine" << endl;
    }

    return 0;
}
