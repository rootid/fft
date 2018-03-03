// Combination Sum IV
//Given an integer array with all positive numbers and no duplicates, find the
//number of possible combinations that add up to a positive integer target.
//Example:
//nums = [1, 2, 3]
//target = 4
//The possible combination ways are:
//(1, 1, 1, 1)
//(1, 1, 2)
//(1, 2, 1)
//(1, 3)
//(2, 1, 1)
//(2, 2)
//(3, 1)
//Note that different sequences are counted as different combinations.
//Therefore the output is 7.
//Follow up:
//What if negative numbers are allowed in the given array?
//How does it change the problem?
//What limitation we need to add to the question to allow negative numbers?
//

//######################################### Bottom-up #########################################
class Solution {

    public int combinationSum4(int[] nums, int target) {
        int[] dp = new int[target+1];
        Arrays.fill(dp, -1);
        dp[0] = 1;
        return combinationSum4Helper(nums, target,dp);
    }

    private int combinationSum4Helper(int[] nums,int target, int[] dp) {
        int count = 0;
        int n = nums.length;
        if(dp[target] != -1) return dp[target];
        for(int i=0;i<n;i++) {
            if(target >= nums[i]) {
                target = target-nums[i];
                count += combinationSum4Helper(nums,target,dp);
                target = target+nums[i];
            }
        }
        dp[target] = count;
        return dp[target];
    }
}

//######################################### Recursion #########################################
public int combinationSum4(int[] nums, int target) {
    return combinationSum4Helper(nums, target);
}

private int combinationSum4Helper(int[] nums, int target) {
    int count = 0;
    int n = nums.length;
    if(target == 0) return count+1;
    for(int i=0;i<n;i++) {
        if(target >= nums[i]) {
            target = target-nums[i];
            count += combinationSum4Helper(nums, target);
            target = target+nums[i];
        }
    }
    return count;
}

//######################################### KnapSack with only weights - TOP Down #########################################
int combinationSum4(vector<int>& nums, int target) {
    vector<int> dp(target + 1,0);
    sort(nums.begin(),nums.end());
    //dp[0] = 1;
    for(int i=1;i<=target;i++) {  //i -> current weight
        for(int j=0;j<nums.size();j++) { //iterate over sample set
            if(i - nums[j] < 0) {
                break;
            }
            if (i - nums[j] > 0) {
                dp[i] += dp[ i - nums[j] ];
            }  else if(i == nums[j]) { //found matched weight
                dp[i] += 1;
            }

        }
    }
    return dp[target];
}

//######################################### Recursion  #########################################
//
//        1 - 1 - 0
//       /
//     1 - 2 - 0
//   ／
// 1 － 2 - 1 - 0
//   \
//    3 - 0              ==> total ways = 7
//
//     1 - 1 - 0
//   /
// 2 - 2 - 0
//
// 3 - 1 - 0
//target is the sum of numbers in the array. Imagine we only need one more
//number to reach target, this number can be any one in the array, right? So
//the # of combinations of target, comb[target] = sum(comb[target - nums[i]]),
//where 0 <= i < nums.length, and target >= nums[i].
//In the example given, we can actually find the # of combinations of 4 with
//the # of combinations of 3(4 - 1), 2(4- 2) and 1(4 - 3). As a result, comb[4]
//= comb[4-1] + comb[4-2] + comb[4-3] = comb[3] + comb[2] + comb[1].
//Then think about the base case. Since if the target is 0, there is only one
//way to get zero, which is using 0, we can set comb[0] = 1.
//EDIT: The problem says that target is a positive integer that makes me feel
//it's unclear to put it in the above way. Since target == 0 only happens when
//in the previous call, target = nums[i], we know that this is the only
//combination in this case, so we return 1.
//Now we can come up with at least a recursive solution.

public int combinationSum4(int[] nums, int target) {
    if (target == 0) {
        return 1;
    }
    int res = 0;
    for (int i = 0; i < nums.length; i++) {
        if (target >= nums[i]) {
            res += combinationSum4(nums, target - nums[i]);
        }
    }
    return res;
}
//implementation of bottom-up approach, you will notice that it may have more
//"intermediate steps" than the top-down one.
//For example, given nums = [100], target = 100, the top-down approach will get
//the result directly, while the bottom-up has to build comb[1] all the way to
//comb[100].
//Is it possible to calculate only necessary intermediate steps in bottom-up
//approach? It's possible because you can find the next smallest sum with the
//nums given. But I think it's hard enough to be another independent problem.
//######################################### Top-Down #########################################
private int[] dp;

public int combinationSum4(int[] nums, int target) {
    dp = new int[target + 1];
    Arrays.fill(dp, -1);
    dp[0] = 1;
    return helper(nums, target);
}

private int helper(int[] nums, int target) {
    if (dp[target] != -1) {
        return dp[target];
    }
    int res = 0;
    for (int i = 0; i < nums.length; i++) {
        if (target >= nums[i]) {
            res += helper(nums, target - nums[i]);
        }
    }
    dp[target] = res;
    return res;
}

//######################################### Bottom-Up #########################################
public int combinationSum4(int[] nums, int target) {
    int[] comb = new int[target + 1];
    comb[0] = 1;
    for (int i = 1; i < comb.length; i++) {
        for (int j = 0; j < nums.length; j++) {
            if (i - nums[j] >= 0) {
                comb[i] += comb[i - nums[j]];
            }
        }
    }
    return comb[target];
}
