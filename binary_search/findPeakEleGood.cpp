//Find Peak Element
//
//A peak element is an element that is greater than its neighbors.
//Given an input array where num[i] ≠ num[i+1], find a peak element and return its index.
//The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.
//You may imagine that num[-1] = num[n] = -∞.
//For example, in array [1, 2, 3, 1], 3 is a peak element and your function should return the index number 2.

#include<iostream>
#include<string>
#include<vector>
using namespace std;

//O(n)
int findPeakBinHelper(const vector<int>& nums,int left,int right) {
  if(left == right) {
    return left;
  } else {
    int mid = left + (right-left)/2;
    if (nums[mid] > nums[mid+1]) {
      //cout << " left = " <<  left <<  "| mid = " << mid << "| V = "  << nums[mid] << endl;
      return findPeakBinHelper(nums,left,mid);
    } else {
      //cout << " rt = " <<  right <<  "| mid = " << mid << "| V = "  << nums[mid] << endl;
      return findPeakBinHelper(nums,mid+1,right);
    }
  }
}

int findPeakElement(vector<int>& nums) {
  int len = nums.size();
  return findPeakBinHelper(nums,0,len-1);
}

int main() {

  int a[] = {1, 2, 3, 1};
  vector<int> av (a,a+sizeof(a)/sizeof(a[0]));
  int peakIdx = findPeakElement(av);
  cout << " PEAK idx = " << peakIdx  << " | VAL = " << av[peakIdx] << endl;
}
