//Continuous Subarray Sum
//Given a list of non-negative numbers and a target integer k, write a function to check 
//if the array has a continuous subarray of size at least 2 that sums up to the multiple of k, 
//that is, sums up to n*k where n is also an integer.
//Example 1:
//Input: [23, 2, 4, 6, 7],  k=6
//Output: True
//Explanation: Because [2, 4] is a continuous subarray of size 2 and sums up to 6.
//Example 2:
//Input: [23, 2, 6, 4, 7],  k=6
//Output: True
//Explanation: Because [23, 2, 6, 4, 7] is an continuous subarray of size 5 and sums up to 42.
//Note:
//The size() of the array won't exceed 10,000.
//You may assume the sum of all the numbers is in the range of a signed 32-bit integer.
#include "../headers/global.hpp"
///################################################### O(n)
bool checkSubarraySum(vector<int>& nums, int k) { 
 unordered_map<int, int> map;
 map[0] = -1; //for case [0,0] 0
 int runningSum = 0;
 for (int i=0;i<nums.size();i++) {
     runningSum += nums[i];
     if (k != 0) {
       runningSum %= k; 
     }
     if (map.count(runningSum)) {
         if (i - map[runningSum] > 1) { //length is at least 2
           return true;
         }
     } else {
       map[runningSum] = i;
     }
 }
 return false;
}
///################################################### Remove the 0th check condition LN : 22 ################################################### 
bool checkSubarraySum(vector<int>& nums, int k) { 
  unordered_map<int, int> map;
  map[0] = -1;
  int runningSum = 0;
   if (k == 0) k = 0x80000000;
  for (int i=0;i<nums.size();i++) {
      runningSum += nums[i];
      runningSum %= k; 
      if (map.count(runningSum)) {
          if (i - map[runningSum] > 1) { //length is at least 2
            return true;
          }
      } else {
        map[runningSum] = i;
      }
  }
  return false;
}

//############################### 
bool checkSubarraySum(vector<int>& nums, int k) { 
  if(nums.size() < 2) {
    return false;
  }
  //To avoid divide by zero
  if (k == 0) {
      for (int i = 0; i < nums.size() - 1; i++) {
          if (nums[i] == 0 && nums[i + 1] == 0) 
            return true;
      }
      return false;
  }
  vector<int> dp(nums.begin(),nums.end());
  for (int i = 1; i < nums.size(); i++) {
      for (int j = 0; j < nums.size() - i; j++) {
          dp[j] += nums[j + i];
          if (dp[j] % k == 0) {
            return true;
          }
      }
  }
  return false;
}
int main() {
}
