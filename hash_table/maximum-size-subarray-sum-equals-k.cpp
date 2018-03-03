//Maximum Size Subarray Sum Equals k
//Given an array nums and a target value k, find the maximum length of a
//subarray that runningSums to k. If there isn't one, return 0 instead.
//Example 1:
//Given nums = [1, -1, 5, -2, 3], k = 3,
//return 4. (because the subarray [1, -1, 5, -2] runningSums to 3 and is the
//longest)
//Example 2:
//Given nums = [-2, -1, 2, 1], k = 1,
//return 2. (because the subarray [-1, 2] runningSums to 1 and is the longest)
//Follow Up:
//Can you do it in O(n) time?
//
//

//######################################### Running Sum trick #########################################
public int maxSubArrayLen(int[] nums, int k) {
    if (nums == null || nums.length == 0) return 0;
    HashMap<Integer, Integer> map = new HashMap<>();
    map.put(0, -1);
    int runningSum = 0;
    int maxLen = Integer.MIN_VALUE;
    for (int i=0; i<nums.length; i++) {
        runningSum += nums[i];
        if (!map.containsKey(runningSum)) map.put(runningSum, i);

        if (map.containsKey(runningSum-k)) {
            int index = map.get(runningSum-k);
            maxLen = Math.max(maxLen, i-index);
        }
    }
    return maxLen==Integer.MIN_VALUE? 0 : maxLen;
}
