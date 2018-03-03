//Move Zeroes
//Given an array nums, write a function to move all 0's to the end of it while
//maintaining the relative order of the non-zero elements.
//For example, given nums = [0, 1, 0, 3, 12], after calling your function, nums
//should be [1, 3, 12, 0, 0].
//Note:
//You must do this in-place without making a copy of the array.
//Minimize the total number of operations.

#include<iostream>

using namespace std;

//######################################### Trick #########################################
public void moveZeroes(int[] nums) {
     int m = nums.length;
     int idx = 0;
     for(int i=0;i<m;i++) {
         if(nums[i] != 0) swap(nums,i,idx++);
     }
 }
 private void swap(int[] nums, int i,int j) {
     int tmp = nums[i];
     nums[i] = nums[j];
     nums[j] = tmp;
 }

//######################################### Trick #########################################
void moveZeroes(vector<int>& nums) {
  int len = nums.size();
  int idx = 0;
  for(int i=0;i<len;i++) {
    if(nums[i] != 0) {
      swap(nums[idx],nums[i]);
      idx += 1;
    }
  }
}

int main() {

}
