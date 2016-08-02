//Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.
//For example, given array S = {-1 2 1 -4}, and target = 1.
//The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
//

#include<iostream>
#include<vector>
#include<cmath>
#include<climits>
#include<algorithm>
using namespace std;


int threeSumClosest(vector<int>& nums, int target) {

  int len = nums.size();
  if(len < 3) {
    return 0;
  }
  bool closestFound = false;
  sort(nums.begin(),nums.end());
  int closestDist = nums[0] + nums[1] + nums[2];
  for(int i=0;i<len-2;i++) {
    if(closestFound == true) {
        return closestDist;
    }
    // optimization
    if(i > 0 && nums[i] == nums[i-1]) {
      continue;
    }
    int left = i+1;
    int right = len-1; 
    while(left < right) {
       // optimization
       //if(left > i+1 && nums[left+1] == nums[left]) {
       //  left = left + 1;
       //  continue;
       //}
       int cdist = nums[i] + nums[left] + nums[right];
       if(abs(closestDist-target) > abs(cdist-target) ) {
          closestDist = cdist;
          if(abs(closestDist-target) == 0) {
              closestFound = true;
              break;
          }
       }
       if(cdist > target) {
         right -= 1;
       } else {
         left += 1;
       }

    }
  }
  return closestDist;
}


int main() {

}
