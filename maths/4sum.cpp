//Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.
//Note: The solution set must not contain duplicate quadruplets.
//For example, given array S = [1, 0, -1, 0, -2, 2], and target = 0.
//A solution set is:
//[
//  [-1,  0, 0, 1],
//  [-2, -1, 1, 2],
//  [-2,  0, 0, 2]
//]
//
#include<iostream>
#include<vector>
using namespace std;

vector<vector<int> > fourSum(vector<int>& nums, int target) {
  vector<vector<int> > result;
  int len = nums.size();
  if(len < 4) {
    return result;
  }
  sort(nums.begin(),nums.end());

  for(int i=0;i<len-3;i++) {
    int firstV = nums[i];
    if(i > 0 && nums[i] == nums[i-1] ) {
      continue;
    }

    //optimization  (Rutime 76ms->16ms)
    if ( (firstV + nums[i+1] + nums[i+2] + nums[i+3]) > target) {
      break;
    }
    if ( (firstV + nums[len-1] + nums[len-2] + nums[len-3]) < target) {
      continue;
    }
    for(int j=i+1;j<len-2;j++) {
      if(j > i+1 && nums[j] == nums[j-1]) {
        continue;
      }
      int secondV = nums[j];

      //optimization 
      if ( (firstV + secondV + nums[j+1] + nums[j+2]) >  target) {
        break;
      }
      if ( (firstV + secondV + nums[len-1] + nums[len-2]) <  target) {
        continue;
      }
      int left = j+1;
      int right = len -1;
      while(left < right) {
        int thirdV = nums[left];
        int forthV = nums[right];
        if(firstV + secondV + thirdV + forthV == target) {
          result.push_back(vector<int> {firstV,secondV,thirdV,forthV} );
          while( left < right && thirdV == nums[left]) {
              left += 1;
          }
          while( left < right && forthV == nums[right]) {
              right -= 1;
          }
        } else if (firstV + secondV + thirdV + forthV < target) {
          left += 1;
        } else {
          right -= 1;
        }
      }
    }
  }
  return result;
}


int main() {

  vector<int> tmp.push_back (1,0,-1,0,-2,2);

}
