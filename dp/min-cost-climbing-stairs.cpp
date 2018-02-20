//Min Cost Climbing Stairs
//On a staircase, the i-th step has some non-negative cost cost[i] assigned (0 indexed).
//Once you pay the cost, you can either climb one or two steps. You need to find minimum cost to reach the top of the floor, and you can either start from the step with index 0, or the step with index 1.
//Example 1:
//Input: cost = [10, 15, 20]
//Output: 15
//Explanation: Cheapest is start on cost[1], pay that cost and go to the top.
//Example 2:
//Input: cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
//Output: 6
//Explanation: Cheapest is start on cost[0], and only step on 1s, skipping cost[3].
//Note:
//    cost will have a length in the range [2, 1000].
//    Every cost[i] will be an integer in the range [0, 999].
//


//######################################### DP -2D #########################################
//Simple DP solution - at each step we make a decision to take this step or not. If we take current step, then we take the min of taking and not taking previous step and add the current cost.
//If we don't take the current step, then we have to take the previous step - so directly get the value from taking the previous step
//Finally return the min of taking and not taking the final step

class Solution {
  public int minCostClimbingStairs(int[] cost) {
    int n = cost.length;
    int[][] dp = new int[n+1][2];
    for(int i = 1; i < dp.length; i++) {
      dp[i][0] = Math.min(dp[i-1][0] + cost[i-1], dp[i-1][1]+cost[i-1]); // taking current step
      dp[i][1] = dp[i-1][0]; // not taking current step
    }
    return Math.min(dp[n][0], dp[n][1]);
  }
}

//######################################### DP #########################################
//There is a clear recursion available: the final cost f[i] to climb the staircase from some step i is f[i] = cost[i] + min(f[i+1], f[i+2]). This motivates dynamic programming.
//Algorithm
//Let's evaluate f backwards in order. That way, when we are deciding what f[i] will be, we've already figured out f[i+1] and f[i+2].
//We can do even better than that. At the i-th step, let f1, f2 be the old value of f[i+1], f[i+2], and update them to be the new values f[i], f[i+1]. We keep these updated as we iterate through i backwards. At the end, we want min(f1, f2).
//Time Complexity: O(N) where NNN is the length of cost.
//Space Complexity: O(1), the space used by f1, f2.

class Solution {
    public int minCostClimbingStairs(int[] cost) {
        int f1 = 0, f2 = 0;
        for (int i = cost.length - 1; i >= 0; --i) {
            int f0 = cost[i] + Math.min(f1, f2);
            f2 = f1;
            f1 = f0;
        }
        return Math.min(f1, f2);
    }
}


//######################################### DP #########################################
class Solution {
    // [1, 100, 1, 1, 1, 100, 1, 1, 100, 1] -> [1, 100]
    public int minCostClimbingStairs(int[] cost) {
        //
        int len = cost.length;
        int[] dp = new int[len+1];
        dp[0] = cost[0];
        dp[1] = cost[1];
        for(int i=2;i<=len;i++) {
            int cst = i == len ? 0 : cost[i];
            dp[i] = cst + Math.min(dp[i-1], dp[i-2]);
        }
       return dp[len];
    }
}


//######################################### DP #########################################
class Solution(object):
    def minCostClimbingStairs(self, cost):
        f1 = f2 = 0
        for x in reversed(cost):
            f1, f2 = x + min(f1, f2), f1
        return min(f1, f2)

//######################################### Recursion O(2^N) #########################################
def minCostClimbingStairs(self, cost):
    def recurse(index, cost):
        if index >= len(cost):
            return 0
        else:
            return cost[index] + min(recurse(index+1, cost), recurse(index+2, cost))

    return min(recurse(0, cost), recurse(1, cost))

// vim: set sw=2 sts=2 tw=120 et nospell :
//
