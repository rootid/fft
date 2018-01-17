//Contains Duplicate II
//Given an array of integers and an integer k, find out whether there are two distinct 
//indices i and j in the array such that nums[i] = nums[j] and the difference between i and j is at most k.
#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
using namespace std;


bool containsNearbyDuplicate(vector<int>& nums, int k) {
  unordered_map<int,int> numStore;
  if (nums.size() == 0) {
    return false;
  }
  for(int i=0;i<nums.size();i++) {
    if (numStore.find(nums[i]) == numStore.end()) {
      numStore[ nums[i] ] = i;
    } else {
      if (i - numStore[ nums[i] ] <= k ) {
        return true;
      }
      numStore[ nums[i] ] = i;
    }
  }
  return false;
}

bool containsNearbyDuplicate1(vector<int>& nums, int k) {
  unordered_set<int> numStore;
  if (nums.size() == 0 || k == 0) {
    return false;
  }
  if (k >= nums.size() ) {
    k = nums.size() - 1;
  }
  for(int i=0;i<nums.size();i++) {
    if(i > k) {
      numStore.erase(nums[i-k-1] );
    } else {
      if(numStore.find(nums[i]) != numStore.end() ) {
        return true;
      }
      numStore.insert(nums[i]);
    }
    
  }
  return false;
}

int main() {

}
