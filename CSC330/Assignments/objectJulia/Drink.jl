# These are global variables
const MAXIMUM_CAPACITY = 10
const DEFAULT_COST = 1.75


mutable struct Drink
  name::String
  consumed::Int
  available::Int
  moneyMade::Float64
  drinkCost::Float64
  useDefaultCost::Int
  useSuppliedCost::Int
end

# Constructor that takes either just the drink name, or the drink name and the cost
function Drink(brandName::String, cost::Float64 =  DEFAULT_COST)
  drink = Drink(brandName, 0, 0, 0.0, cost, 0, 0)
  if cost ==  DEFAULT_COST
    drink.useDefaultCost = 1
    drink.useSuppliedCost = 0
  else
    drink.useDefaultCost = 0
    drink.useSuppliedCost = 1
  end
  return drink
end

function refill(drink::Drink)
  drink.available =  MAXIMUM_CAPACITY
  println("*****************************")
  println("* " * drink.name * " refilled")
  println("*****************************")
end

function vend(drink::Drink)
  if drink.available > 0
    drink.available -= 1
    drink.consumed += 1
    drink.moneyMade += drink.useDefaultCost *  DEFAULT_COST + drink.useSuppliedCost * drink.drinkCost
    println(drink.name * " purchased.")
  else
    println("************")
    println("* SOLD OUT *")
    println("************")
  end
end

function getProfit(drink::Drink)
  return round(drink.moneyMade * 100.0) / 100.0
end

function getDrinksSold(drink::Drink)
  return drink.consumed
end

function getDrinkName(drink::Drink)
  return drink.name
end

function getRestockAmount(drink::Drink)
  return MAXIMUM_CAPACITY - drink.available
end
