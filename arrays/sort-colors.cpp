//Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.
//Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.
//Note:
//You are not suppose to use the library's sort function for this problem.
//

#include<iostream>
#include<vector>
using namespace std;

void sortColors(vector<int>& nums) {
    //2 -pass solution
    int len = nums.size();
    int last_zero_idx = 0;
    for(int i=0;i<len;i++) {
        if(nums[i] == 0) {
            swap(nums[i],nums[last_zero_idx]);
             last_zero_idx += 1;
        } 
    }
    int last_one_idx = last_zero_idx;
    for(int i=last_zero_idx;i<len;i++) {
        if(nums[i] == 1) {
            swap(nums[last_one_idx],nums[i]);
            last_one_idx += 1;
        }
    }
}
