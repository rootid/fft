//Subsets
//Given a set of distinct integers, nums, return all possible subsets.
//Note:
//Elements in a subset must be in non-descending order.
//The solution set must not contain duplicate subsets.
//For example,
//If nums = [1,2,3], a solution is:
//[
//  [3],
//  [1],
//  [2],
//  [1,2,3],
//  [1,3],
//  [2,3],
//  [1,2],
//  []
//]
#include "../headers/global.hpp"
void enum_subset(vector<int>& ip,int& len,int k,vector<bool>&cv
    ,vector<vector<int> >& sv) {
  if(k == len) {
    vector<int> lv;
    int idx = 0;
    for(auto c:cv) {
      if (c == true) {
        lv.push_back(ip[idx]);
      }
      idx+= 1;
    }
    sv.push_back(lv);
    return;
  }
    cv[k] = true;
    enum_subset(ip,len,k+1,cv,sv);
    cv[k] = false;
    enum_subset(ip,len,k+1,cv,sv);
}
vector<vector<int> > subsets(vector<int>& nums) {
  int len = nums.size();
  vector<bool> cv(len,true);
  int k = 0;
  vector<vector<int> > sv;
  vector<int> lv;
  enum_subset(nums,len,k,cv,sv);
  return sv;
}
//Iteative with BFS at each level  1. copy all previous set
//                                 2. append
vector<vector<int> > subsets(vector<int> &nums) {
    int len = nums.size();
    sort(nums.begin(), nums.end());
    vector<vector<int> > res(1);//start by adding empty set   [ [] ]
    for(int i = 0; i < len; ++i) { // BFS tree with levels = len
        int k = res.size();
        for(int j = 0; j < k; j++) { //@ each level there will be at most k childern
            res.push_back(res[j]); //[ [],[] ]
            res.back().push_back(nums[i]); //[ [],[1] ]
        }
    }
  return res;
}
//////
//
//At each level either select kth element or not
void dfs(int n,int k,vector<int>&ip,vector<int>&tmp,vector< vector<int> >&res) {
  if(n == k) {
    res.push_back(tmp);
    return;
  }
  tmp.push_back(ip[k]); // select kth element
  dfs(n,k+1,ip,tmp,res);
  tmp.pop_back();      //remove kth element
  dfs(n,k+1,ip,tmp,res);
}
vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    int level = 0;
    vector<int> tmp;
    vector< vector<int> > res;
    sort(nums.begin(),nums.end());
    dfs(nums.size(),level,nums,tmp,res);
    return res;
}
//////
//The characteristics of C++ reference is an outstanding tool for backtracking
//algorithm!
//
//let us use [1,2,3,4] as an example to explain my solution:
//
//subsets([1,2,3,4]) = []
//                     // push(1)
//                     [1, subsets([2,3,4])] // if push N times in subsets([2,3,4]), the pop times is also N, so vec is also [1] after backtrack.
//                     // pop(), push(2)
//                     [2, subsets([3,4])]
//                     // pop(), push(3)
//                     [3, subsets([4])]
//                     // pop(), push(4)
//                     [4, subsets([])]
//                     // pop()
//
//
// think it is O(2^n), you can calculate the total push times as follow:
//
//t(0) = 0
//t(1) = 1+t(0)
//t(2) = 2+t(1)+t(0)
//...
//t(n-1) = n-1+t(n-2)+t(n-3)+...+t(1)+t(0)
//t(n) = n+t(n-1)+t(n-2)+...+t(1)+t(0) = n+t(n-1)+t(n-1)-n+1=2t(n-1)+1
//
//=> t(n)+1 = 2(t(n-1)+1) => t(n)+1 = 2^n => t(n) = 2^n-1
/////////
void enum_subsets(vector<vector<int> > &res, vector<int> &nums, vector<int> &vec, int begin) {
	res.push_back(vec);
	for (int i = begin; i <= nums.size(); ++i) {
		vec.push_back(nums[i]);
		enum_subsets(res, nums, vec, i + 1);
		vec.pop_back();
	}
}
vector<vector<int> > subsets(vector<int> &nums) {
	sort(nums.begin(), nums.end());
      vector<vector<int> > res;
	vector<int> vec;
	enum_subsets(res, nums, vec, 0);
	return res;
}
//////
//
//
void enum_subsetsWithDup(vector<vector<int> > &res, vector<int> &nums, vector<int> &vec, int begin) {
	res.push_back(vec);
	for (int i = begin; i != nums.size(); ++i)
		if (i == begin || nums[i] != nums[i - 1]) {
			vec.push_back(nums[i]);
			enum_subsetsWithDup(res, nums, vec, i + 1);
			vec.pop_back();
		}
}
vector<vector<int> > subsetsWithDup(vector<int> &nums) {
  sort(nums.begin(), nums.end());
  vector<vector<int> > res;
  vector<int> vec;
  enum_subsetsWithDup(res, nums, vec, 0);
  return res;
}
int main() {
}
