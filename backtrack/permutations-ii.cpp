//Given a collection of numbers that might contain duplicates, return all possible unique permutations.
//For example,
//[1,1,2] have the following unique permutations:
//[
//  [1,1,2],
//  [1,2,1],
//  [2,1,1]
//]


Backtracking is a nightmare for this problem.

The solution of "backtracking" is not efficient in spece since its creating arrays memories for each depth of the recursion function. If you do not pass by value, the swap action will disturb the sorted sequence and you are going to meet repeating answers.

One way to do it is to take advantage of nextPermutaion, which is to find the next larger permutation. And loop the nextPermutation function to find the complete unique permutation sequences.

Another way to solve it is DFS. DFS does not swap the array elements and preserves the sorted property.

For example you have want to solve permuteUnique[3,2,0,3,1,0,1]

Sort it you get

permuteUnique[0,0,1,1,2,3,3] =

0, permuteUnique[0,1,1,2,3,3]

1, permuteUnique[0,0,1,2,3,3]

2, permuteUnique[0,0,1,1,3,3]

3, permuteUnique[0,0,1,1,2,3]

and then you solve the sub question.

Sidenote: make sure in the current-depth DFS you don’t pick multiple duplicate and dig into sub-question.

public class Solution {
    public List<List<Integer>> permuteUnique(int[] nums) {
        Arrays.sort(nums);
        List<List<Integer>> ans = new ArrayList<List<Integer>>();
        List<Integer> cur = new ArrayList<Integer>();
        boolean[] used = new boolean[nums.length];
        solve(0, nums, ans, cur, used);
        return ans;
    }
    
    private void solve(int depth, int[] nums, List<List<Integer>> ans, List<Integer> cur, boolean[] used) {
        if (depth == nums.length) {
            ans.add(new ArrayList<Integer>(cur));
            return;
        }
        
        for (int i = 0; i < nums.length; i++) {
            if (used[i] || (i > 0 && nums[i - 1] == nums[i] && !used[i - 1])) continue;
            used[i] = true; cur.add(nums[i]);
            solve(depth + 1, nums, ans, cur, used);
            used[i] = false; cur.remove(cur.size() - 1);
        }
    }


Thanks for the explanation! I finally figured it out.

Yes, the reason of sorting is to skip duplicates. Take [1, 2, 2, 3] for example, when pos equals 0, we have below cases

(1,2,2,3) (pos = 0, i = 0)

(2,1,2,3) (pos = 0, i = 1)

(2,1,2,3) (pos = 0, i =2) skipped, since array[0]=array[2]; in other words, its subset (1,2,3) is the same as the second case (pos = 0, i=1)

(3,1,2,2) (pos = 0, i =3)

As we can see, the subset of the above four cases are still sorted. Amazing! Recursion continues.

On the other hand, if we use pass-by-reference, the set are ALWAYS sorted AFTER the extra swap, as below. The above amazing trick doesn’t work and duplicates won’t be avoided. So, the result of pass-by-reference algorithm is not correct.

(1,2,2,3) (pos = 0, i = 0)

(1,2,2,3) (pos = 0, i = 1)

(1,2,2,3) (pos = 0, i =2)

(1,2,2,3) (pos = 0, i =3)




Using an unordered_map to get all the distinct elements and the number of their occurence so that we don't need to do sorting. Then do dfs and backtracking to generate all the permutations: for each iteration, put each available distinct element (i.e. numMap->second >0) into path, update numMap, and do DFS at the next level. Once path has a length of len, then we get a new permutation and just add path to res.

class Solution {
private: 
    void  dfsHelper(vector<vector<int>>  &res, vector<int> &path, unordered_map<int, int> &numMap, int len)
    {
        if(path.size()==len) {res.push_back(path); return;}
        for(auto it = numMap.begin(); it != numMap.end(); ++it)
        {
            if(it->second)
            {
                path.push_back(it->first); // update the current path
                --(it->second); // and map
                dfsHelper(res, path, numMap, len); // then do dfs at the next level
                path.pop_back(); // backtracking by recovering path and map
                ++(it->second);
            }
        }
    }

public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        int i,len = nums.size();
        vector<vector<int>> res;
        if(len>0)
        {
            vector<int> path;

            unordered_map<int, int> numMap; //generate a map
            for(i=0; i<len; ++i) ++numMap[nums[i]];

            dfsHelper(res, path, numMap, len);
        }
        return res;
        
        
    }
};
If we do soring, then the unordered_map is not needed.

class Solution {
private:
    void dfs(vector<vector<int>> &res, vector<int> &cur, vector<int> canVec, int len)
    {
        if(cur.size()==len)
        {
            res.push_back(cur);
        }
        else
        {
            for(auto i=0; i<canVec.size(); ++i)
            {
                if(i>0 && canVec[i] == canVec[i-1] ) continue;
                cur.push_back(canVec[i]);
                vector<int> temp = canVec;
                temp.erase(temp.begin()+i);
                dfs(res, cur, temp, len);
                cur.pop_back();
            }
        }
    }

public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        
        vector<vector<int>> res;    
        int  len = nums.size();
        if(len>0)
        {
            vector<int> cur;
            std::sort(nums.begin(), nums.end());
            dfs(res, cur, nums, len);
        }
        return res;
