//Remove Duplicates from Sorted Array

//Given a sorted array, remove the duplicates in place such that each element
//appear only once and return the new length.
//Do not allocate extra space for another array, you must do this in place with
//constant memory.
//For example,
//Given input array nums = [1,1,2],
//Your function should return length = 2, with the first two elements of nums
//being 1 and 2 respectively. It doesn't matter what you leave beyond the new
//length.
//
#include "../headers/global.hpp"
using namespace std;


//################### Iteration  ###################
public int removeDuplicates(int[] nums) {
     int lastIdx = 1;
     for(int i=1;i<nums.length;i++)  {
         if(nums[i] != nums[i-1]) nums[lastIdx++] = nums[i];
     }
     return lastIdx;
}
//################### GOOD  ###################
int removeDuplicates(int A[], int n) {
  int count = 0;
  for(int i = 1; i < n; i++){
      if(A[i] == A[i-1]) {
        count++;
      } else {
        A[i-count] = A[i];
      }
  }
  return n-count;
}


//################### bad ###################
int removeDuplicates(vector<int>& nums) {
  int len = nums.size();
  if(len <= 1) {
    return len;
  }
  int idx = 1;
  for(int i=0;i<len-1;i++) {
    if(nums[i] != nums[i+1]) {
      nums[idx + 1] = nums[i+1];
      idx += 1;
    }
  }
  return idx;
}

//################### Ugly  #######################
int removeDuplicates(int A[], int n) {
      if(n < 2) return n;
      int idx = 1;
      for(int i = 1; i < n; ++i)  {
          if(A[i] != A[i-1]) {
            A[idx] = A[i];
            idx += 1;
          }
      }
      return idx;
}

int main () {

}
