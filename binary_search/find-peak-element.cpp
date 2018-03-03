//Find Peak Element
//
//A peak element is an element that is greater than its neighbors.
//Given an input array where num[i] ≠ num[i+1], find a peak element and return
//its index.
//The array may contain multiple peaks, in that case return the index to any
//one of the peaks is fine.
//You may imagine that num[-1] = num[n] = -∞.
//For example, in array [1, 2, 3, 1], 3 is a peak element and your function
//should return the index number 2.

#include "../headers/global.hpp"

//##################################################  O(log n) + Iteration ##################################################
int findPeakElement(int[] num)  {
      int low = 0;
      int high = num.length-1;
      while(low < high) {
          int mid1 = low + (high-low)/2;
          System.out.println(mid1);
          if(num[mid1] < num[mid1+1])
              low = mid1+1;
          else
              high = mid1;
      }
      return low; // [1]
}


//##################################################  Recursion + O(log n) ##################################################
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

//##################################################  Ugly ##################################################
int findPeakElement(vector<int>& nums) {
  int len = nums.size();
  if(len <= 1) {
    return len - 1;
  }
  if(len == 2) {
    if(nums[0] > nums[1]) {
      return 0;
    }
    return 1;
  }
  for (int i=1;i<len-1;i++) {
    if(nums[i] > nums[i-1] && nums[i] > nums[i+1]) {
      return i;
    }
  }
  if(nums[0] > nums[1]) {
    return 0;
  }
  if(nums[len - 1] > nums[len -2]) {
    return len-1;
  }
  return -1;
}

//##################################################  Ugly ##################################################
int findPeakBinHelper(vector<int>& nums,int left,int right) {
  if(left < right) {
    int mid = left + (right-left)/2;
    if (nums[mid] > nums[mid-1] && nums[mid] > nums[mid+1]) {
      //cout << "mid = " << mid << endl;
      return mid;
    }
    int l = findPeakBinHelper(nums,left,mid-1);
    if (l != -1) {
      return l;
    }
    int r = findPeakBinHelper(nums,mid+1,right);
    if (r != -1) {
      return r;
    }
  }
  return -1;
}

int findPeakElement(vector<int>& nums) {
  int len = nums.size();
  return findPeakBinHelper(nums,0,len);
}

int main() {

  int a[] = {1, 2, 3, 1};
  vector<int> av (a,a+sizeof(a)/sizeof(a[0]));
  int peakIdx = findPeakElement(av);
  cout << " PEAK idx = " << peakIdx  << " | VAL = " << av[peakIdx] << endl;
}
