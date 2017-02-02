// Missing Number
//Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array.
//For example,
//Given nums = [0, 1, 3] return 2.
//Note:
//Your algorithm should run in linear runtime complexity. Could you implement it using only constant extra space complexity?
//[1,0] return 2
//
int missingNumber(vector<int>& nums) {
    int res  = nums.size();
    for(int i=0;i<nums.size();i++) {
        res ^= i;
        res ^= nums[i];
    }
    return res;
}
