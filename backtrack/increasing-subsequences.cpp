//Increasing Subsequences
//Given an integer array, your task is to find all the different possible increasing subsequences of the given array, and the length of an increasing subsequence should be at least 2 .
//Example:
//Input: [4, 6, 7, 7]
//Output: [[4, 6], [4, 7], [4, 6, 7], [4, 6, 7, 7], [6, 7], [6, 7, 7], [7,7], [4,7,7]]
//Note:
//The length of the given array will not exceed 15.
//The range of integer in the given array is [-100,100].
//The given array may contain duplicates, and two equal integers should also be considered as a special case of increasing sequence.
//######################################## DFS ######################################## 
vector<vector<int>> findSubsequences(vector<int>& nums) {
    set<vector<int>> res;
    vector<int> seq;
    helper(nums, seq, res, 0);
    return vector<vector<int>>(res.begin(), res.end());
}
    
void helper(vector<int> &nums, vector<int>& seq, set<vector<int>>& result, int index) {
    if (seq.size() >= 2) {
        result.insert(seq);
    }
    for (int i=index; i<nums.size(); ++i) {
        if (seq.size() == 0 || nums[i] >= seq.back()) {
            seq.push_back(nums[i]);
            helper(nums, seq, result, i+1);
            seq.pop_back();
        }
    }
}
//######################################## DFS ######################################## 
void findSubsequences(vector<int> &nums, vector<int> &subsequence,
                      set<vector<int> > &result, int size, int index) {
  if (size >= 2) {
      result.insert(subsequence);
      //return;
  }
  for (int i = index; i < nums.size(); ++i) {
      if (subsequence.size() == 0 || nums[i] >= subsequence[subsequence.size() - 1]) {
          subsequence.push_back(nums[i]);
          findSubsequences(nums, subsequence, result, size + 1, i + 1);
          subsequence.pop_back();
      }
    }
}
vector<vector<int>> findSubsequences(vector<int>& nums) {
    unordered_set<vector<int> > resultSet;
    vector<int> subsequence;
    findSubsequences(nums, subsequence, resultSet, 0, 0);
    vector<vector<int>> result(resultSet.begin(), resultSet.end());
    return result;
}
//######################################## FAST ######################################## 
vector<vector<int>> findSubsequences(vector<int>& nums) {
     vector<vector<int>> ans(0);
     if(nums.size()<2) return ans;
     int fst[nums.size()];       //first
     bool rep[nums.size()];      //repeat
     for(int i=0;i<nums.size();++i){
         fst[i]=ans.size();
         rep[i]=false;
         for(int j=i-1;j>=0;--j){
             if(nums[j]<=nums[i]){
                 if(!rep[j]){
                     ans.emplace_back(vector<int>(2,nums[i]));
                     ans.back()[0]=nums[j];
                 }
                 for(int k=fst[j];k<fst[j+1];++k){
                     ans.push_back(ans[k]);
                     ans.back().emplace_back(nums[i]);
                 }
                 if(nums[j]==nums[i]){
                     rep[i]=true;
                     break;
                 }
             }
         }
     }
     return ans;
}


This is similar to Subsets II.

O(n2^n) For each number, we can either take it or drop it. Duplicates are removed by set.
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        set<vector<int>> res;
        vector<int> one;
        find(0,nums, one, res);
        return vector<vector<int>>(res.begin(),res.end());
    }
    void find(int p, vector<int>& nums, vector<int>& one, set<vector<int>>& res) {
        if(p==nums.size()) {
            if(one.size()>1) res.insert(one);
            return;
        }
        if(one.empty()||nums[p]>=one.back()) {
            one.push_back(nums[p]);
            find(p+1,nums,one,res);
            one.pop_back();
        }
        find(p+1,nums,one,res);
    }
We can also generate all increasing subsequences by adding each number to the current sequencies iteratively and use set to remove duplicates.
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        vector<vector<int>> seq(1);
        set<vector<int>> bst;
        for(int i=0;i<nums.size();i++) {
            int n = seq.size();
            for(int j=0;j<n;j++)
                if(seq[j].empty() || seq[j].back()<=nums[i]) {
                    seq.push_back(seq[j]);
                    seq.back().push_back(nums[i]);
                    if(seq.back().size()>1) bst.insert(seq.back());
                }  
        }
        return vector<vector<int>>(bst.begin(),bst.end());
    }
We can do better by not generating duplicates. When adding a duplicate number to existing sequences, we don't need to add to all sequences because that will create duplicate sequence. We only need to add to the sequences created since adding this number last time.
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        vector<vector<int>> res(1);
        unordered_map<int,int> ht;
        for(int i=0;i<nums.size();i++) {
            int n = res.size();
            int start = ht[nums[i]];
            ht[nums[i]] = n;
            for(int j=start;j<n;j++)
                if(res[j].empty() || res[j].back()<=nums[i]) {
                    res.push_back(res[j]);
                    res.back().push_back(nums[i]);
                }  
        }
        for(int i=res.size()-1;i>=0;i--) 
            if(res[i].size()<2) {
                swap(res[i],res.back());
                res.pop_back();
            }
        return res;
    }
Duplicates can also be avoided in recursion. Starting from a given number, we pick the next number. We cache the numbers already tried to avoid duplicates.
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> one;
        find(0,nums,one,res);
        return res;
    }
    void find(int p, vector<int>& nums, vector<int>& one, vector<vector<int>>& res) {
        int n = nums.size();
        if(one.size()>1) res.push_back(one);
        unordered_set<int> ht;
        for(int i=p;i<n;i++) {
            if((!one.empty() && nums[i] < one.back()) || ht.count(nums[i])) continue;
            ht.insert(nums[i]);
            one.push_back(nums[i]);
            find(i+1,nums,one,res);
            one.pop_back();
        }
    }
