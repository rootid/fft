#include<iostream>
#include<vector>
using namespace std;

int robber(vector<int>&nums) {
  int odd = 0;
  int even = 0;
  for(int i=0;i<nums.size();i++) {
      if (i % 2 == 0) {
        even += nums[i];
      } else {
        odd += nums[i];
      }
  }

  return max(even,odd);

}

int main() {

}
