//2Sum
#include<iostream>
#include<vector>
using namespace std;

vector<vector<int>> twoSum(vector<int>& nums,int target) {

  vector<<int>> result;
  unordered_map<int,int> idxMap;
  for(int i=0;i<nums.size();i++) {
    idxMap[nums[i]] = i;
  }
  
  for(int i=0;i<nums.size();i++) {
    int newTarget = target - nums[i];
    if ( idxMap.find(newTarget) != 0) {
      int newIdx = idxMap[newTarget];
      if(newIdx != i) {
        vector<int> r;
        r.push_back(i);
        r.push_back(new_idx);
        result.push_back(r);
      }
    }
  }
  return result;
}
  
int main() {

}
