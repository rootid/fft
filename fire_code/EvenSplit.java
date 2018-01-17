import java.util.*;
// Given an array of integers, determine if it is possible to split
// the array into two parts such that the sum of all elements in each part is
// the same.
// Examples:
// splitArray({1,2,3,4}) ==> true
// splitArray({1,2,4}) ==> false

// 0/1 Knapsack or BinPack solution
public class EvenSplit {
  //#### T : O(n^2), S : O(n) ####
  public static boolean splitArray(int[] nums) {
    int sum = Arrays.stream(nums).sum();
    sum >> >= 1;
    boolean[] dp = new boolean[sum + 1];
    dp[0] = true;
    for (int k : nums) {
      for (int j = sum; j >= k; j--) dp[j] = dp[j] || dp[j - k];
    }
    return dp[sum];
  }
}
