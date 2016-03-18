//3Sum
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


//For example, given array S = {-1 0 1 2 -1 -4},
//A solution set is:
//(-1, 0, 1)
//(-1, -1, 2)
//O(n^2) : can we do better?
vector<vector<int>> threeSum(vector<int>& nums) {
  sort(nums.begin(),nums.end());
  vector<<int>> result;
  int tLen = nums.size();
  for (int i=0;i< tLen - 2;i++) {
    int temp = a[i];
    for(int j = i+1,k=tLen;j<tLen || k>=i;) {
    int tSum = a[j] + a[k];
    if(tSum + temp == 0) {
      vector<int> tmpResult;
      result.push_back(tmpResult);
      break;
    } else if(tSum + temp > 0) {
      j++;
    } else {
      k--;
    }
  }
 return result;
}
  
int main() {

}
