//# of ways to count the
#include<iostream>
#include<vector>
using namespace std;


//This program is unbounded version of Knapsack Problem. Here we have to find
//the minimum number of coins using which we can make our resultant amount. We
//make an array of size as total amount. The ith value will store the minimum
//number of coins used to get amount equal to i and if its not possible to get
//sum i, value will be zero.

//num of coins needed to get sum i = min of (num of coins till now, num of
//coins to get [i-coin(j)] + 1)
//a[i] = min( a[i], a[i-c[j]]+1)

int coinChange(vector<int>& coins, int amount) {

  int result = 0;
  vector<int> av(amount+1,0);
  int len = coins.size();
  for(int i=0;i<amount;i++) {
    av[i] = min(  )
  }
  return result;

}

int main() {

}
