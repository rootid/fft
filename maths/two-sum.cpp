//2Sum
//Given nums = [2, 7, 11, 15], target = 9,
//Because nums[0] + nums[1] = 2 + 7 = 9,
//return [0, 1].
#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

//######################################### 2 Sum with Map  ######################################### 
public int[] twoSum(int[] nums, int target) {
    //RemainingVal, idx
    //if match
    Map<Integer, Integer> store = new HashMap<>();
    for(int i=0;i<nums.length;i++) {
        if(store.containsKey(nums[i])) return new int[] {store.get(nums[i]), i};
        store.put(target - nums[i], i);
    }
    return new int[] {-1,-1};
}


//######################################### Lazy loading ######################################### 
vector<int> twoSum(vector<int>& nums,int target) {
  //lazy loading
  unordered_map<int,int> idxMap;
 
  for(int i=0;i<nums.size();i++) {
    int newTarget = target - nums[i];
    if ( idxMap.find(newTarget) != idxMap.end()) {
      int newIdx = idxMap[newTarget];
      int first = min(i,newIdx);
      int second = max(i,newIdx);
      return vector<int> {first,second};
    }
    //store the visited number with idx
    idxMap[nums[i]] = i;
  }
  return vector<int> {};
}

vector<int> twoSum(vector<int>& nums, int target) {
     vector<int> result;
     unordered_map<int,int> idxMap;
     int idx = 0;
     for(auto &i:nums) {
         int r = target - i;
         if(idxMap.find(r) != idxMap.end()) {
             result.push_back(idxMap[r]);
             result.push_back(idx);
             return result;
         }
        
         idxMap[i] = idx;
          idx += 1;
     }
      return result;
}
  
int main() {
  //int a[] = {2,7,11,15};
  //int a[] = {2,9,11,15};
  int a[] = {2,4,4,15}; // TODO : target : 8 need to keep the vector to store the idxes
  vector<int> av(a,a+sizeof(a)/sizeof(a[0]));
  //vector<int> result = twoSum(av,9);
  vector<int> result = twoSum(av,8);
  for(int i=0;i<result.size();i++) {
    cout << result[i] << " \t ";
  }
  cout << endl;
}
