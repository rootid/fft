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
