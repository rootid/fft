//Rotate Array
//Rotate an array of n elements to the right by k steps.
//
//For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] is rotated to
//[5,6,7,1,2,3,4].

#include<iostream>

void doSwap(vector<int>& nums,int start,int end) {

  while(start <= end) {
    swap(nums[start],nums[end]);
    start +=1;
    end -=1;
  }

}

void rotate(vector<int>& nums, int t) {

  int n = nums.size();
  //if t > n
  t = t % n;
  int k = n-t-1;
  doSwap(nums,0,k);
  doSwap(nums,k+1,n-1);
  doSwap(nums,0,n-1);

}

int main () {

}
