//3Sum
//Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.
//Note:
//Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)
//The solution set must not contain duplicate triplets.
//    For example, given array S = {-1 0 1 2 -1 -4},
//    A solution set is:
//    (-1, 0, 1)
//    (-1, -1, 2)
//
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<vector<int> > threeSum(vector<int>& nums) {
  vector<vector<int> > triplet;
  int len = nums.size();
  if(len < 3) {
      return triplet;
  }
  sort(nums.begin(),nums.end());
  for(int i=0;i<len;i++) {
    int a = nums[i];
    int j = i + 1;
    int k = len - 1;
    while(j < k) {
      int b = nums[j];
      int c = nums[k];
      //cout << " ---> a,b,c = " << a << "," << b << "," << c << endl;
      //cout << " ---> j,k = " << j << "," << k << endl;
      if(a + b + c  == 0) {
        cout << " a,b,c = " << a << "," << b << "," << c << endl;
        triplet.push_back({a,b,c});
        while(b == nums[j+1] && j<k) {
          j++;
        } 
        while(c == nums[k-1] && j<k) {
          k--;
        } 
        j++;
        k--;
      } else if (a+b+c < 0) {
        while( j<k && b == nums[j+1] ) {
          j++;
        } 
        j++;
      } else {
        while(j<k && c == nums[k-1] ) {
          k--;
        }
        k--;
      }
    }
    while(i + 1<len && a == nums[i+1] ) { //avoid a duplicates
      i++;
    }
  }
  return triplet;
}
int main(int argc, char *argv[])
{
 
  //int a[] =  {1,-1,-1,0};
  //int a[] =  {-2,0,0,2,2};
  //int a[] = {-2,0,1,1,2};
  int a[] = {-1,0,1,2,-1,-4};
  //int a[] = {1,2,-2,-1};
  vector<int> r (a,a+sizeof(a)/sizeof(a[0]));
  threeSum(r);
  return 0;
}
//vector<int> twoSum(int target,int idx,vector<int>& nums) {
//  vector<int> result;
//  unordered_map<int,int> idxMap;
//  int len = nums.size();
//  for(int i=idx;i<len;i++) {
//    int r = target - nums[idx];
//    if(idxMap.find(r) != idxMap.end()) {
//      return vector<int> {idxMap[r],idx};
//    }
//    idxMap[ nums[idx] ] = i;
//  }
//  return vector<int> {};
//}
//vector<vector<int>> threeSum(vector<int>& nums) {
//  vector<vector<int> > result;
//  vector<int> partialResult;
//  int i = 0;
//  int len = nums.size();
//  if(len < 3) {
//      return result;
//  }
//  for(int i=0;i<len;i++) {
//    int target = -nums[i];
//    partialResult= twoSum(target,i,nums);
//    if(partialResult.size() > 1) {
//      partialResult.push_back(i);
//      sort(partialResult.begin(),partialResult.end());
//      result.push_back(partialResult);
//    }
//  }
//  return result;
//}
