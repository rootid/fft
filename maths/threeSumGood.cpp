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
vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    for (unsigned int i=0; i<nums.size(); i++) {
        if ((i>0) && (nums[i]==nums[i-1]))
            continue;
        int l = i+1, r = nums.size()-1;
        while (l<r) {
            int s = nums[i]+nums[l]+nums[r];
            if (s>0) r--;
            else if (s<0) l++;
            else {
                res.push_back(vector<int> {nums[i], nums[l], nums[r]});
                while (nums[l]==nums[l+1]) l++;
                while (nums[r]==nums[r-1]) r--;
                l++; r--;
            }
        }
    }
    return res;
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
