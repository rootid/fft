//Longest Continuous Increasing Subsequence
//Given an unsorted array of integers, find the length of longest continuous increasing subsequence.
//Example 1:
//Input: [1,3,5,4,7]
//Output: 3
//Explanation: The longest continuous increasing subsequence is [1,3,5], its length is 3. 
//Even though [1,3,5,7] is also an increasing subsequence, it's not a continuous one where 5 and 7 are separated by 4. 
//Example 2:
//Input: [2,2,2,2,2]
//Output: 1
//Explanation: The longest continuous increasing subsequence is [2], its length is 1. 
//Note: Length of the array will not exceed 10,000


//######################################### Linear traversal  ######################################### 
public int findLengthOfLCIS(int[] nums) {
    if(nums == null || nums.length == 0) return 0;
    int maxLength = 1;
    int cLen = 1;
    for(int i=1;i<nums.length;i++) {
        if(nums[i-1] < nums[i]) 
            cLen++;
        else cLen = 1;
        maxLength = Math.max(cLen, maxLength);
    }
    return maxLength;
}

//######################################### 2 Pointer ######################################### 
 int findLengthOfLCIS(vector<int>& nums) {
        if(nums.empty()) return 0;
        int i = 0, j = 1, maxlen = 1;
        while(j < nums.size()){
            while(j < nums.size() && nums[j] > nums[j - 1]) j++;
            maxlen = max(maxlen, j - i);
            i = j++;
        }
        return maxlen;
    }
//##################### T: O(N) ##################### 
public int findLengthOfLCIS(int[] nums) {
    if(nums.length <= 1) return nums.length;
    int j = 0, maxlen = 0, len = 1;
    while(j < nums.length) {
        if(j>0 && nums[j] > nums[j-1]) len++;
        else len = 1;
        maxlen = Math.max(maxlen, len);
        j++;
    }
    return maxlen;
}

//##################### T: O(N) ##################### 
class Solution(object):
    def findLengthOfLCIS(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if not nums:
            return 0
        prev = nums[0] - 1
        count = 0
        max_count = 0
        for num in nums:
            if num > prev:
                count += 1
            else:
                max_count = max(max_count, count)
                count = 1
            prev = num
        return max(max_count, count)

//######################################### DP S:(N) , T : O(N)######################################### 
//dp[i] represents the longest continuous increasing subsequence end at index i
//The logic is if nums[i]>nums[i-1], dp[i] = dp[i-1] + 1, otherwise dp[i] = 1

public int findLengthOfLCIS(int[] nums) {
    if( nums==null || nums.length == 0 ) return 0;
    int n = nums.length;
    int[] dp = new int[n];
    int result = 1;
    dp[0] = 1;
    for( int i=1; i<n; i++ ){
        if( nums[i]>nums[i-1] ){
            dp[i] = dp[i-1] + 1;
        }
        else{
            dp[i] = 1;
        }
        if( dp[i]>result ){
            result = dp[i];
        }
    }
    return result;
}

/* vim: set ts=4 sw=4 sts=4 tw=120 et: */
