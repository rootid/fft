#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//Contains Duplicate 
//TO : O(n lg n) + O(n)
//SO : O(k)
bool containsDuplicate(vector<int>& nums) {

  if( nums.size() <= 1) {
    return true;
  }
  sort(nums.begin(),nums.end()) ;
  int len = nums.size();
  
  for (int i=0;i<len-1;++i) {
    if(nums[i] == nums[i+1]) {
        return true;
    }
  }
 return false;
}
