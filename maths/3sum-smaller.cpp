//3Sum Smaller
//Given an array of n integers nums and a target, find the number of index triplets i, j, k with 0 <= i < j < k < n that satisfy the condition nums[i] + nums[j] + nums[k] < target.
//For example, given nums = [-2, 0, 1, 3], and target = 2.
//Return 2. Because there are two triplets which sums are less than 2:
//[-2, 0, 1]
//[-2, 0, 3]
//

#include<iostream>
#include<vector>
using namespace std;


int threeSumSmaller(vector<int>& nums, int target) {

  int len = nums.size();
  if(len < 3) {
    return 0;
  } 
  int cnt = 0;
  for(int i=0;i<len-2;i++) {
    int left = i + 1;
    int right = len -1;
    while(left < right) {
      int sum_ = nums[i] + nums[left] + nums[right];
      if(sum_ < target) {
        cnt += (right-left);
        left += 1;
      } else {
        right -= 1;
      }
    }
  }
 return cnt; 
}

int main() {

}

