#Coin Change
#You are given coins of different denominations and a total amount of money amount. Write a function to compute the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.
#Example 1:
#coins = [1, 2, 5], amount = 11
#return 3 (11 = 5 + 5 + 1)
#Example 2:
#coins = [2], amount = 3
#return -1.
#Note:
#You may assume that you have an infinite number of each kind of coin.
############################### Branch and Bound ############################## 
def coinChange(self, coins, amount):
    if len(coins) == 0:
        return -1
    if amount == 0:
        return 0
    
    # try biggest coins first
    sortedCoins = sorted(coins, reverse=True)

    # upper bound on number of coins (+1 to represent the impossible case)
    upperBound = (amount + sortedCoins[-1] - 1) / sortedCoins[-1] + 1

    self.bestNCoins = upperBound
    
    self.branchAndBoundSearch(sortedCoins, amount, 0)

    if self.bestNCoins == upperBound:
        return -1
    else:
        return self.bestNCoins

def branchAndBoundSearch(self, sortedCoins, amount, nCoins):
    # lower bound on number of coins, achieved using the biggest coin
    lowerBound = nCoins + (amount + sortedCoins[0] - 1) / sortedCoins[0]

    if lowerBound > self.bestNCoins:
        return
    
    if len(sortedCoins) == 0:
        return
    
    # if amount matches the biggest coin, that is the solution
    if amount == sortedCoins[0] and nCoins + 1 < self.bestNCoins:
        self.bestNCoins = nCoins + 1
        return
    
    # try use the biggest coin
    if amount > sortedCoins[0]:
        self.branchAndBoundSearch(sortedCoins, amount - sortedCoins[0], nCoins + 1)
    
    # else try not to use the biggest coin
    if len(sortedCoins) > 1:
        self.branchAndBoundSearch(sortedCoins[1:], amount, nCoins)

