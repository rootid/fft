//3Sum
//For example, given array S = {-1 0 1 2 -1 -4},
//A solution set is:
//(-1, 0, 1)
//(-1, -1, 2)
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


//O(n^2) : can we do better?
//Need to avoid duplicates
vector<vector<int>> threeSum(vector<int>& nums) {
  vector<vector<int> > result;
  sort(nums.begin(),nums.end());
  int tLen = nums.size();
  for(int i=0;i<tLen;i++) {
    int c = -nums[i];
    int j = i+1;
    int k = tLen;
    while(j < k) {
      if (nums[j] +nums[k] == c) {
        result.push_back( {-c,nums[j],nums[k]} );
        j++;
        k--;
      } else if(nums[j] + nums[k] > c) {
        k--;
      } else {
        j++;
      }
    }
  }
  return result;
}


  
int main() {
  int a[] = {-1,0,1,2,-1,-4};
  vector<int>av(a,a+sizeof(a)/sizeof(a[0]));
  vector<vector<int> > result = threeSum(av);
  for(int i=0;i<result.size();i++) {
    vector<int> temp = result[i];
    for(int i=0;i<temp.size();i++) {
      cout << temp[i] << "\t" ;
    }
    cout << endl;
  }
}
