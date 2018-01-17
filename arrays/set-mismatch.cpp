//Set Mismatch
//The set S originally contains numbers from 1 to n. But unfortunately, due to the data error, one of the numbers in the set got duplicated to another number in the set, which results in repetition of one number and loss of another number.
//Given an array nums representing the data status of this set after the error. Your task is to firstly find the number occurs twice and then find the number that is missing. Return them in the form of an array.
//Example 1:
//Input: nums = [1,2,2,4]
//Output: [2,3]
//Note:
//The given array size will in the range [2, 10000].
//The given array's numbers won't have any order.

//############################### Swap ############################### 
//Put each nums[i] into the position with index nums[i] - 1
//[1,2,3,4,5...,n]. So we can find the duplicate number when nums[i] != i+1.
public int[] findErrorNums(int[] nums) {
     int[] result = new int[2];
     int n = nums.length;
     for(int i=0;i<n;i++) {
         while(nums[i] != nums[nums[i] - 1]) swap(nums,i,nums[i] -1);
     }
     for(int i=0;i<n;i++) 
         if(nums[i]-1 != i) { 
             result[0] = nums[i];
             result[1] = i+1;
             return result;
         }
     return result;
 }
 
 private void swap(int[] nums, int i,int j) {
     int tmp = nums[i];
     nums[i] = nums[j];
     nums[j] = tmp;
 }


//############################### Swap ############################### 
//The main idea is to put the value in the array to its right position.
//For example, if the given array is [4,2,3,5,2], after the restructure step, the array would be [-2,-2,-3,-4,-5].
//Therefore, the missing number would be the index of the array whose value is not compatible with its index. In our example it's 1, because the number in the index of 0 should be -1 instead of -2
//The duplicate number would be the value of that index. In our example, it's 2.
//The restructure step is to swap the value in current index to its right position and make the moved number negative as the visited.
//[4, 2, 3, 5, 2] -> [5, 2, 3, -4, 2] -> [2, 2, 3, -4, -5] -> [2, -2, 3, -4, -5] -> [-2, -2, 3, -4, -5] -> [-2, -2, -3, -4, -5]

public class Solution {
    public int[] findErrorNums(int[] nums) {
        int duplicate = 0;
        int missing = 0;
        for (int i = 0; i < nums.length; i ++) {
            while (nums[i] > 0){
                int idx = nums[i] - 1;
                int tmp = nums[i];
                nums[i] = nums[idx];
                nums[idx] = -tmp;
            }
            if (-nums[i] != i + 1){
                missing = i + 1;
            }
        }
        return new int[] {-nums[missing - 1], missing};
    }
}
