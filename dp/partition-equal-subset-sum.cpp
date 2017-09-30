//Given a non-empty array containing only positive integers, find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.
//Note:
//Each of the array element will not exceed 100.
//The array size will not exceed 200.
//Example 1:
//Input: [1, 5, 11, 5]
//Output: true
//Explanation: The array can be partitioned as [1, 5, 5] and [11].
//Example 2:
//Input: [1, 2, 3, 5]
//Output: false
//Explanation: The array cannot be partitioned into equal sum subsets.
//
//The maximum possible sum is O(N^2). That makes DP O(N^3), 
//and backtracking is still O(2^N). 
//Even when N is around 20 they should be on about the same level, 
//for larger N backtracking should be prohibitively slow! And there are test cases as large as 50 elements.
//

//###############################dp[n][W] = dp[n - 1][W - a[n-1]] || dp[n - 1][W] // pick || skip ###############################
bool canPartition(vector<int>& nums) {
        int all = accumulate(nums.begin(), nums.end(), 0);
        if (all % 2 != 0)
            return false;
        unordered_set<int> sums;
        sums.insert(0);
        for (int num : nums) {
            unordered_set<int> nextSums = sums;
            for (int sum : sums) {
                if (sum + num == all - (sum + num))
                    return true;
                else if (sum + num < all - (sum + num))
                    nextSums.insert(sum + num);
            }
            sums = nextSums;
        }
        return false;
}
//https://chinmaylokesh.wordpress.com/2011/02/10/balanced-partition-problem-finding-the-minimized-sum-between-two-partitions-of-a-set-of-positive-integers/
//#################################################################### DP ##################################################
bool canPartition(vector<int>& nums) {
      int sum = accumulate(nums.begin(), nums.end(), 0);
      if (sum % 2 != 0) {
          return false;
      }
      int target = sum / 2;
      vector<bool> hasSum(target + 1, false);
      hasSum[0] = true;
      int localSum = 1;
      for (int num : nums) {
          if (num > target) { // A single number greater than half the sum?
              return false; // No way we can partition this!
          }
          for (int i = localSum - 1; i >= 0; --i) {
              if (hasSum[i] && i + num < hasSum.size()) {
                  if (i + num == target) {
                      return true;
                  }
                  hasSum[i + num] = true;
                  localSum = max(localSum, i + sum + 1);
              }
          }
      }
      return hasSum[target];
}
//############################# Backtracing ############################# 
bool hasSubsetSum(const vector<int> &nums, size_t start, int target) {
    if (target < 0) {
        return false;
    }
    if (target == 0) {
        return true;
    }
    for (size_t i = start; i < nums.size(); ++i) {
        if (hasSubsetSum(nums, i + 1, target - nums[i])) {
            return true;
        }
    }
    return false;
}
bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 != 0)
            return false;
        return hasSubsetSum(nums, 0, sum / 2);
}

//######################################### DP + T o(n) , s (sum) ######################################### 
 public boolean canPartition(int[] nums) {
        int sum=0;
        for(int n:nums) sum+=n;
        if((sum&1)==1) return false;
        sum>>>=1;
        boolean[] dp=new boolean [sum+1];
        dp[0]=true;
        for(int k:nums){
            for(int j=sum;j>=k;j--)
                dp[j]=dp[j]||dp[j-k];
        }
        return dp[sum];
    }

//######################################### 0/1 Knapsack problem  ######################################### 
//dp[n][W] = dp[n - 1][W - a[n-1]] || dp[n - 1][W]
//This problem is essentially let us to find whether there are several numbers in a set which are able to sum to a specific value (in this problem, the value is sum/2).
//Actually, this is a 0/1 knapsack problem, for each number, we can pick it or not. Let us assume dp[i][j] means whether the specific sum j can be gotten from the first i numbers. If we can pick such a series of numbers from 0-i whose sum is j, dp[i][j] is true, otherwise it is false.
//Base case: dp[0][0] is true; (zero number consists of sum 0 is true)
//Transition function: For each number, if we don't pick it, dp[i][j] = dp[i-1][j], which means if the first i-1 elements has made it to j, dp[i][j] would also make it to j (we can just ignore nums[i]). If we pick nums[i]. dp[i][j] = dp[i-1][j-nums[i]], which represents that j is composed of the current value nums[i] and the remaining composed of other previous numbers. Thus, the transition function is dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i]]

public boolean canPartition(int[] nums) {
    int sum = 0;
    
    for (int num : nums) {
        sum += num;
    }
    
    if ((sum & 1) == 1) {
        return false;
    }
    sum /= 2;

    int n = nums.length;
    boolean[][] dp = new boolean[n+1][sum+1];
    for (int i = 0; i < dp.length; i++) {
        Arrays.fill(dp[i], false);
    }
    
    dp[0][0] = true;
    
    for (int i = 1; i < n+1; i++) {
        dp[i][0] = true;
    }
    for (int j = 1; j < sum+1; j++) {
        dp[0][j] = false;
    }
    
    for (int i = 1; i < n+1; i++) {
        for (int j = 1; j < sum+1; j++) {
            dp[i][j] = dp[i-1][j];
            if (j >= nums[i-1]) {
                dp[i][j] = (dp[i][j] || dp[i-1][j-nums[i-1]]);
            }
        }
    }
   
    return dp[n][sum];
}


