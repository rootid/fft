//Contains Duplicate II
//Given an array of integers and an integer k, find out whether there are two distinct indices i and j in the array such that nums[i] = nums[j] and the difference between i and j is at most k.

#include "../headers/global.hpp"

//######################## WITH SET ##########################################
bool containsNearbyDuplicate(vector<int>& nums, int k) {
   unordered_set<int> s;
   
   if (k <= 0) return false;
   if (k >= nums.size()) {
     k = nums.size() - 1;
   }
   
   for (int i = 0; i < nums.size(); i++) {
       if (i > k)  {
         s.erase(nums[i - k - 1]); 
       }
       if (s.count(nums[i]) != 0)  {
         return true;
       }
       s.insert(nums[i]);
   }
   return false;
}
//######################## WITH MAP ##########################################
bool containsNearbyDuplicate(vector<int>& nums, int k) {
    int idx = 0;
    unordered_map<int,int> kv;
    for(auto &num:nums) {
        if(kv.find(num) == kv.end()) {
            kv[num] = idx;
        } else {
            if((idx - kv[num] ) > k ) {
                kv[num] = idx;
            } else {
                return true;
            }
        }
        idx += 1;
    }
    return false;
}
int main() {
}
