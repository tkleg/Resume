package main

import (
        "fmt"
        "math"
       )

// Drink represents a beverage that can be purchased from a vending machine.
type Drink struct {
    // Class variables
    MaximumCapacity int
        DefaultDrinkCost float64

        // Instance variables
        Available int
        Consumed int
        UseDefaultCost int
        UseSuppliedCost int
        DrinkCost float64
        MoneyMade float64
        Name string
}

// NewDrink creates a new Drink object.
func NewDrink(name string) *Drink {
    return &Drink{
     Name : name,
     Consumed : 0,
     Available : 0,
     MoneyMade : 0.0,
     DrinkCost : 1.75,
     UseDefaultCost : 1,
     UseSuppliedCost : 0,
     MaximumCapacity : 10,
     DefaultDrinkCost : 1.75,
    }
}

// NewDrinkWithCost creates a new Drink object with a custom cost.
func NewDrinkWithCost(name string, cost float64) *Drink {
    return &Drink{
          Name: name,
          Consumed: 0,
          Available: 0,
          MoneyMade: 0.0,
          DrinkCost: cost,
          UseDefaultCost: 0,
          UseSuppliedCost: 1,
          MaximumCapacity: 10,
          DefaultDrinkCost: 1.75,
    }
}

// Vend dispenses a Drink from the vending machine.
func (d *Drink) Vend() {
    if d.Available > 0 {
        d.Available--
            d.Consumed++
            d.MoneyMade += (float64(d.UseDefaultCost) * d.DefaultDrinkCost +
                    float64(d.UseSuppliedCost) * d.DrinkCost)
            fmt.Println(d.Name + " purchased.")
    } else {
        fmt.Println("************")
        fmt.Println("* SOLD OUT *")
        fmt.Println("************")
    }
}

// Refill fills the vending machine with Drinks to their maximum capacity.
func (d *Drink) Refill() {
    d.Available = d.MaximumCapacity
}

// Profit calculates the profit made from selling Drinks.
func (d *Drink) Profit() float64 {
    return math.Round(d.MoneyMade*100.0) / 100.0
}

// DrinksSold returns the number of Drinks that have been sold.
func (d *Drink) DrinksSold() int {
    return d.Consumed
}

// GetDrinkName returns the name of the Drink.
func (d *Drink) GetDrinkName() string {
    return d.Name
}

// RestockAmount returns the number of Drinks that need to be restocked.
func (d *Drink) RestockAmount() int {
    return d.MaximumCapacity - d.Available
}
