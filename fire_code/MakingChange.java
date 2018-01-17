// Given an integer array containing the available denominations of coins in
// descending order, write a method to compute the number of possible ways of
// representing a monetary amount in cents.
// For simplicity, assume that there are an infinite number of coins available
// for each coin denomination in the array.
// Examples:
// makeChange({25,10,5,1},10) ==> 4

public class MakingChange {
  //### Iteration -> Bottom-Up  solution
  public static int makeChange(int[] coins, int amount) {
    int m = coins.length;
    if (amount <= 0 || m < 0) {
      return 0;
    }
    int[] dp = new int[amount + 1];
    dp[0] = 1;
    for (int coin : coins) {
      for (int i = coin; i <= amount; i++) {
        dp[i] += dp[i - coin];
      }
    }
    return dp[amount];
  }

  // http://www.algorithmist.com/index.php/Coin_Change
  // Prereq : input[] array must be non decreaing  s1<s2<s3..<sm
  // C(N,m) = C(N,m - 1) + C(N - Sm,m)
  // C(N,m) = 1,N = 0 (one solution -- we have no money, exactly one way to
  // solve the problem - by choosing no coin change, or, more precisely, to
  // choose coin change of 0)
  // C(N,m) = 0,N <= 0 (no solution -- negative sum of money)
  // C(N,m) = 0 N >= 1,m < 0(no solution -- we have money, but no change
  // available)
  // Recursive -> Top->Down
  public static int makeChangeRecursive(int[] coins, int amount) {
    int m = coins.length;
    if (amount <= 0 || m < 0) {
      return 0;
    }
    return makeChangeHelper(coins, amount, m - 1);
  }

  private static int makeChangeHelper(int[] coins, int amount, int pickIdx) {
    int m = coins.length;
    if (pickIdx < 0 || amount < 0) {
      return 0;
    }
    if (amount == 0) return 1;
    return makeChangeHelper(coins, amount, pickIdx - 1) +
        makeChangeHelper(coins, amount - coins[pickIdx], pickIdx);
  }
}
