//Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.
//
//Note: The solution set must not contain duplicate triplets.
//
//For example, given array S = [-1, 0, 1, 2, -1, -4],
//
//A solution set is:
//[
//  [-1, 0, 1],
//  [-1, -1, 2]
//]


#include<iostream>
#include<vector>
using namespace std;

void twoSum(vector<int>& nums,int cIdx,int ltIdx,int rtIdx,int target,vector<vector<int>>& result) {
    while(ltIdx < rtIdx) {
        if(nums[ltIdx] + nums[rtIdx] > target) {
            rtIdx -= 1;
        } else if (nums[ltIdx] + nums[rtIdx] < target) {
            ltIdx += 1;
        } else {
            result.push_back(vector<int>{nums[cIdx], nums[ltIdx], nums[rtIdx]});
            int l = nums[ltIdx];
            int r = nums[rtIdx];
            while( ltIdx < rtIdx &&  l == nums[ltIdx]) {
              ltIdx += 1;
            }
            while(ltIdx < rtIdx && r == nums[rtIdx]) {
              rtIdx -= 1;
            }
        }
   }
}

vector<vector<int>> threeSum(vector<int>& nums) {
  int len = nums.size(); 
  if(len <=2) return {};
  sort(nums.begin(),nums.end());
  vector<vector<int>> result;
  for(int i=0;i<len-2;i++) {
    int target = -nums[i];
    int ltIdx = i+1;
    int rtIdx = len-1;
    int cIdx = i;
    twoSum(nums,cIdx,ltIdx,rtIdx,target,result);
    while( i < len && nums[i] == nums[i+1]) {
        i = i+1;
    }
  }
  return result;
}

int main() {
}
