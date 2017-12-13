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

//### A v/s B - (A - Pick the first item, B- Iterate over sample set and pick)
//A - ######################################### Pick/Don't pick item ######################################### 
public List<List<Integer>> subsets(int[] nums) {
    List<Integer> soFarList = new LinkedList<>();
    List<List<Integer>> result = new ArrayList<>();
    Arrays.sort(nums);
    subsetsHelper(nums,0,soFarList,result);
    return result;
}
private void subsetsHelper(int[] nums,int k,List<Integer>soFarList, List<List<Integer>> result) {
    int n = nums.length;
    if(n == k) {
        result.add(new ArrayList<>(soFarList));
        return;
    }
    soFarList.add(nums[k]); //Pick the item 
    subsetsHelper(nums, k+1, soFarList, result);
    soFarList.remove(soFarList.size() -1); //Don't pick the item
    subsetsHelper(nums, k+1, soFarList, result);
}

//B - ######################################### Recursion ######################################### 
class Solution {
    public List<List<Integer>> subsets(int[] nums) {
        List<Integer> soFar = new LinkedList<>();
        List<List<Integer>> result = new ArrayList<>();
        Arrays.sort(nums);
        subsetsHelper(nums,0,soFar,result);
        return result;
    }
    private void subsetsHelper(int[] nums,int k,List<Integer>soFar, List<List<Integer>> result) {
        int n = nums.length;
        result.add(new ArrayList(soFar));
        for(int i=k;i<n;i++) { 
            soFar.add(nums[i]);
            subsetsHelper(nums,i+1,soFar,result);
            soFar.remove(soFar.size() - 1);
        }
    }
}

//######################################### Recursion ######################################### 
class Solution {
public:
    vector<vector<int> > subsetsWithDup(vector<int> &nums) {
		sort(nums.begin(), nums.end());
        vector<vector<int> > res;
		vector<int> vec;
		subsetsWithDup(res, nums, vec, 0);
		return res;
    }
private:
	void subsetsWithDup(vector<vector<int> > &res, vector<int> &nums, vector<int> &vec, int begin) {
		res.push_back(vec);
		for (int i = begin; i != nums.size(); ++i)
			if (i == begin || nums[i] != nums[i - 1]) { 
				vec.push_back(nums[i]);
				subsetsWithDup(res, nums, vec, i + 1);
				vec.pop_back();
			}
	}
};

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
