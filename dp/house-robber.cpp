//House Robber
//You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.
//Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.

#include<iostream>
#include<vector>
using namespace std;

//Base Case : {2} => 2
//Rec case :  dp[i] = Math.max(nums[i] + dp[i-2],dp[i-1]);
public int rob(int[] nums) {
    int m = nums.length;
    if(m == 0) return 0;
    if(m == 1) return nums[0];
    int dp[] = new int[m];
    dp[0] = nums[0];
    dp[1] = Math.max(nums[0],nums[1]);
    for(int i=2;i<m;i++) {
        dp[i] = Math.max(nums[i] + dp[i-2],dp[i-1]);
    }
    return dp[m-1];
}

//This code handles odd-even overlapping [2,1,1,2] max=4
int rob1(vector<int>&nums) {
  int odd = 0;
  int even = 0;
  for(int i=0;i<nums.size();i++) {
      if (i%2 == 0) {
        even = max (odd ,even + nums[i]);
      } else {
        odd = max(even , odd + nums[i]);
      }
  }
  return max(even,odd);
}


int rob(vector<int>&nums ) {
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
  //vector<int> av( {0,0,0} );
  vector<int> av( {1,1,1} );
  rob(av);
}
