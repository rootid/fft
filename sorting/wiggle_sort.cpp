//Wiggle Sort
//Given an unsorted array nums, reorder it in-place such that nums[0] <= nums[1] >= nums[2] <= nums[3]....
//For example, given nums = [3, 5, 2, 1, 6, 4], one possible answer is [1, 6, 2, 5, 3, 4]
//
//
//

#include<iostream>
#include<vector>

using namespace std;

void wiggleSort(vector<int>& nums) {

  //base case
  if(nums.size() == 0) {
    return;
  }
  //3,5,2,1,6,4
  for(int i=0;i<nums.size() - 1;i++) {
    if (i%2 == 0) { //even must be less than its odd counterpart
      if(nums[i] > nums[i+1]) {
        swap(nums[i],nums[i+1])
      }
    } else {
      if(nums[i] < nums[i+1]) {
        swap(nums[i],nums[i+1])
      }
    }
  }
}


//https://leetcode.com/discuss/57120/4-lines-o-n-c
void wiggleSort(vector<int>& nums) {
    for (int i=1; i<nums.size(); ++i)
        if (i%2 == (nums[i-1] > nums[i]))
            swap(nums[i-1], nums[i]);
}

//The final sorted nums needs to satisfy two conditions:
//
//If i is odd, then nums[i] >= nums[i - 1];
//If i is even, then nums[i] <= nums[i - 1].
//The code is just to fix the orderings of nums that do not satisfy 1 and 2.

   void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        for (int i = 1; i < n; i++)
            if (((i & 1) && nums[i] < nums[i - 1]) || (!(i & 1) && nums[i] > nums[i - 1]))
                swap(nums[i], nums[i - 1]);
    } 

void wiggleSort(vector<int>& nums) {
    for (int i=1; i<nums.size(); ++i)
        swap(nums[i], nums[i - (i%2 ^ (nums[i-1] < nums[i]))]);
}



int main () {

}
