//Target Sum
//You are given a list of non-negative integers, a1, a2, ..., an, and a target, S. Now you have 2 symbols + and -. For each integer, you should choose one from + and - as its new symbol.
//Find out how many ways to assign symbols to make sum of integers equal to target S.
//Example 1:
//Input: nums is [1, 1, 1, 1, 1], S is 3. 
//Output: 5
//Explanation: 
//-1+1+1+1+1 = 3
//+1-1+1+1+1 = 3
//+1+1-1+1+1 = 3
//+1+1+1-1+1 = 3
//+1+1+1+1-1 = 3
//There are 5 ways to assign symbols to make the sum of nums be target 3.
//Note:
//The length of the given array is positive and will not exceed 20.
//The sum of elements in the given array will not exceed 1000.
//Your output answer is guaranteed to be fitted in a 32-bit integer.
//

//######################################### Recursion ######################################### 
public int findTargetSumWays(int[] nums, int S) {
    return findTargetSumWaysHelper(nums,0,S,0);
}

private int findTargetSumWaysHelper(int[] nums, int idx,int S,int cSum) {
    if(nums.length == idx) {
        if(S == cSum) return 1;
        return 0;
    }
    int count = 0;
    count += findTargetSumWaysHelper(nums, idx+1,S,cSum + nums[idx]);
    count += findTargetSumWaysHelper(nums, idx+1,S,cSum - nums[idx]);
    return count;
}

//######################################### Recursion ######################################### 
int helper(vector<int> &nums,int &S,int index,int sum) {
    if(index == nums.size()) {
        if(sum == S)
            return 1;
        return 0;
    }
   
    int count = 0;
    count += helper(nums,S,index+1,sum - nums[index]); // add
    count += helper(nums,S,index+1,sum + nums[index]);  //substract
    return count;
}
int findTargetSumWays(vector<int>& nums, int S) {
   return helper(nums,S,0,0);
}
