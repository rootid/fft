//House Robber II
//After robbing those houses on that street, the thief has found himself a new place for his thievery so that he will not get too much attention. This time, all houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, the security system for these houses remain the same as for those in the previous street.
//Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.

#include<iostream>
#include<vector>
using namespace std;
int rob(vector<int>& nums) {
        int len = nums.size();
        if(len == 0) {
            return 0;
        } 
        if(len == 2) {
           return max(nums[0],nums[1]);
        }
        if(len == 1) {
            return nums[0];
        }
        //0,n-1 
        //1,n
        vector<int> first_half(nums.begin(),nums.end() - 1);
        vector<int> second_half(nums.begin() + 1,nums.end());
        return max(robHelper(first_half),robHelper(second_half));
}
    
int robHelper(vector<int>&nums) {
  int odd = 0;
  int even = 0;
  for(int i=0;i<nums.size();i++) {
      if (i % 2 == 0) {
        even = max ( odd ,even + nums[i]);
      } else {
        odd = max(even , odd + nums[i]);
      }
  }
  return max(even,odd);
}


int robHelper(vector<int>&nums ) {
  int len = nums.size();
  vector<int> dp(len+1,0);
  if(len == 0) {
    return 0;
  }
  dp[1] = nums[0];
  if(len == 1) {
    return nums[0];
  }
  dp[2] = max(nums[0],nums[1]);
  if(len == 2) {
    return max(nums[0],nums[1]);
  }
  //cout << dp[2] << endl;
  //cout << dp[len] << endl;
  for(int i=3;i<=len;i++) {
    //cout << " i " << dp[i] << endl;
    dp[i] = max(dp[i-1] , dp[i-2] + nums[i-1]);
    //cout << " after " << dp[i] << endl;
  }
  //cout << dp[len] << endl;
  return dp[len];
}

int main() {
  vector<int> av( {1,2,1,1} );
}
