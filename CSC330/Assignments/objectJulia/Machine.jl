include("Drink.jl")

drink = Vector{Drink}(undef,4)

# Create Drink vector
drink[1] = Drink("Coca-Cola")
drink[2] = Drink("Fanta", 1.05)
drink[3] = Drink("Guinness", 6.50)
drink[4] = Drink("Bud Light", 0.25)

# Refill the drink machine.
for i in 1:4
  refill(drink[i])
end

# Buy 4 Cokes.
for i in 1:4
vend(drink[1])
end

# Buy 8 Sprites.
for i in 1:8
vend(drink[2])
end

# Buy 11 Guinness
for i in 1:11
  vend(drink[3])
end

# Buy 1 Bud Light
for i in 1:1
  vend(drink[4])
end

# Refill Guinness
refill(drink[3])

# Compute the total Profit
profit = 0.0
for i in 1:4
  global profit += getProfit(drink[i])
end

# Show the total profit
println("The total profit is \$" * string(profit))

# Generate a report per drink

for i in 1:4
  println( "You sold " * string(getDrinksSold(drink[i])) * " " * getDrinkName(drink[i]) * " for a total of \$" * string(getProfit(drink[i])) )
  println( "         " * string(getRestockAmount(drink[i])) * " of " * getDrinkName(drink[i]) * " needed to restock the machine " )
end
