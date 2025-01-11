package main

import (
  "fmt"
)

func main() {

// Our drink machine has four slots
  slot1 := NewDrink("Coke") 
  slot2 := NewDrink("Sprite") 
  slot3 := NewDrinkWithCost("Guinness", 6.50) 
  slot4 := NewDrinkWithCost("Bud Light", 0.25)

  slot1.Refill()
  slot2.Refill()
  slot3.Refill()
  slot4.Refill()

  // Sell some drinks
  for i:=0; i < 5;  i++ {  slot1.Vend() }
  for i:=0; i < 2;  i++ {  slot2.Vend() }
  for i:=0; i < 11; i++ {  slot3.Vend() }
  for i:=0; i < 2;  i++ {  slot4.Vend() }

  totalProfit := slot1.Profit() + slot2.Profit() + slot3.Profit() + slot4.Profit()

  // Print the profit made
  fmt.Println("Total Profit:", totalProfit)

}
