//Given a collection of integers that might contain duplicates, nums, return all possible subsets.
//Note: The solution set must not contain duplicate subsets.
//For example,
//If nums = [1,2,2], a solution is:
//[
//  [2],
//  [1],
//  [1,2,2],
//  [2,2],
//  [1,2],
//  []
//]
//
//

//At each level either select kth element or not
void dfs(int n,int k,vector<int>&ip,vector<int>&tmp,vector<int>&res) {
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

int main() {

}
