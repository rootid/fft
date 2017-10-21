//Remove Duplicates from Sorted Array II
//Follow up for "Remove Duplicates":
//What if duplicates are allowed at most twice?
//For example,
//Given sorted array nums = [1,1,1,2,2,3],
//Your function should return length = 5, with the first five elements of nums being 1, 1, 2, 2 and 3. It doesn't matter what you leave beyond the new length.

#include "../headers/global.hpp"

//#################################################################################
public int removeDuplicates(int[] nums) {
    int lastIdx = 0;
    for(int i=0;i<nums.length;i++)  { 
       // nums[i] > nums[lastIdx - 2] : (1,1,3) current element differ from last 2 elements
       if(lastIdx < 2 || nums[i] > nums[lastIdx - 2]) nums[lastIdx++] = nums[i];
    }
    return lastIdx;
}


//#################################################################################
int removeDuplicates(vector<int>& nums) {
    int i = 0 ;
    for(auto& num : nums) {
        if(i < 2 || num > nums[i-2]) { //lookback at 2 numbers
            nums[i++] = num;
        }
    }
    return i;
}

//#################################################################################
int removeDuplicates(vector<int>& nums, int k) {
    int i = 0;
    for (int n : nums)
        if (i < k || n > nums[i-k])
            nums[i++] = n;
    return i;
}
