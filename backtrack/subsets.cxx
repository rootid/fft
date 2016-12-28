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
//vector<vector<int> > subsets(vector<int> &S) {
//    int len = S.size();
//    sort(S.begin(), S.end());
//    vector<vector<int> > res(1);//start by adding empty set   [ [] ]
//    for(int i = 0; i < len; ++i) // BFS tree with levels = len
//    {
//        int resSize = res.size();
//        for(int j = 0; j < resSize; j++)
//        {
//            res.push_back(res[j]); //[ [],[] ]
//            res.back().push_back(S[i]); //[ [],[1] ]
//        }
//    }
//  return res;
//}

int main() {

}
