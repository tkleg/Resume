import math
import warnings

warnings.filterwarnings('always')

class Drink:

    MAXIMUM_CAPACITY = 10
    DEFAULT_COST = 2

    def __init__(self, brandName, cost = None):
      self.name = brandName
      self.consumed = 0
      self.available = 0
      self.moneyMade = 0
      if cost is None:
        self.drinkCost = Drink.DEFAULT_COST
        self.useDefaultCost = 1
        self.useSuppliedCost = 0
      else:
        self.drinkCost = cost
        self.useDefaultCost = 0
        self.useSuppliedCost = 1

    def refill(self):
        self.available = Drink.MAXIMUM_CAPACITY

    def vend(self):
        if (self.available > 0):
            self.available = self.available - 1
            self.consumed = self.consumed + 1
            self.moneyMade = self.moneyMade + (
                    self.useDefaultCost * Drink.DEFAULT_COST +
                    self.useSuppliedCost * self.drinkCost )
            print( self.name + " purchased.")
        else:
            print("************")
            print("* SOLD OUT *")
            print("************")


    def profit(self):
        return round(self.moneyMade * 100.0)/100.0

    def drinksSold(self):
        return self.consumed

    def getDrinkName(self):
        return self.name

    def restockAmount(self):
        return Drink.MAXIMUM_CAPACITY - self.available
