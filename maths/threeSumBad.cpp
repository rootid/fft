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
    vector<vector<int>> result;

    sort(nums.begin(), nums.end());

    for (auto i = 0; i < nums.size();) {
        auto target = -nums[i];
        int l = i + 1, u = nums.size() - 1;

        while (l < u) {
            auto sum = nums[l] + nums[u];

            if (sum < target)
                while (nums[++l] == nums[l - 1]);  // Processing duplicates of Number 2
            else if (sum > target)
                while (nums[--u] == nums[u + 1]);  // Processing duplicates of Number 3
            else {
                result.push_back(vector<int>{nums[i], nums[l], nums[u]});
                while (nums[++l] == nums[l - 1]);  // Processing duplicates of Number 2
                while (nums[--u] == nums[u + 1]);  // Processing duplicates of Number 3
            } 

        }

        // Processing duplicates of Number 1
        while (nums[++i] == nums[i - 1]);
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
