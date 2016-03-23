//2Sum
//Given nums = [2, 7, 11, 15], target = 9,
//Because nums[0] + nums[1] = 2 + 7 = 9,
//return [0, 1].
#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

vector<int> twoSum(vector<int>& nums,int target) {

  unordered_map<int,int> idxMap;
  //early loading
  for(int i=0;i<nums.size();i++) {
    idxMap[nums[i]] = i;
  }
 
  // 
  for(int i=0;i<nums.size();i++) {
    int newTarget = target - nums[i];
    if ( idxMap.find(newTarget) != idxMap.end()) {
      int newIdx = idxMap[newTarget];
      if(newIdx != i) {
        return vector<int> {i,newIdx};
      }
    }
  }
  return vector<int> {};
}
  
int main() {
  //int a[] = {2,7,11,15};
  //int a[] = {2,9,11,15};
  int a[] = {2,4,4,15}; // TODO : target : 8 need to keep the vector to store the idxes
  vector<int> av(a,a+sizeof(a)/sizeof(a[0]));
  vector<int> result = twoSum(av,9);

  for(int i=0;i<result.size();i++) {
    cout << result[i] << " \t ";
  }
  cout << endl;

}
