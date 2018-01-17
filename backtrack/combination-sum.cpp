//## Combination Sum
//### Given a set of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.
//The same repeated number may be chosen from C unlimited number of times.
//Note:
//All numbers (including target) will be positive integers.
//The solution set must not contain duplicate combinations.
//For example, given candidate set [2, 3, 6, 7] and target 7, 
//A solution set is: 
//[
//  [7],
//  [2, 2, 3]
//]

#include "../headers/global.hpp"



//Thinking about there is an opt[] array, each element in the array is a vector<vector<int>>.
//We do DP from opt[0] to opt[target].
//// base case
//opt[0] = [[]]
//// iteration
//opt[i] = 
//	1.add candidates[j] to each list in opt[i-candidates[j]] if i > candidates[j] 
//	.Add each list to opt[i]
//	2 create candidates[j] as a new vector<int> if i == candidates[j]
//	.Add this list to opt[i]

//##################################################### DP Like coin change  + Sort ##################################################### 
vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector< vector< vector<int> > > combinations(target + 1, vector<vector<int>>());
    combinations[0].push_back(vector<int>());
    for (auto& score : candidates)
        for (int j = score; j <= target; j++){
            auto sls = combinations[j - score];
            if (sls.size() > 0) {
                for (auto& s : sls)
                    s.push_back(score);
                combinations[j].insert(combinations[j].end(), sls.begin(), sls.end());
            }
        }
    return combinations[target];
}

//##################################################### DP ##################################################### 
class Solution {
public:
	vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
		vector< vector< vector<int> > > combinations(target + 1, vector<vector<int>>());
		combinations[0].push_back(vector<int>());
		for (auto& score : candidates)
			for (int j = score; j <= target; j++)
				if (combinations[j - score].size() > 0)	{
					auto tmp = combinations[j - score];
					for (auto& s : tmp)
						s.push_back(score);
					combinations[j].insert(combinations[j].end(), tmp.begin(), tmp.end());
				}
		auto ret = combinations[target];
		for (int i = 0; i < ret.size(); i++)
			sort(ret[i].begin(), ret[i].end());
		return ret;
	}
};

//##################################################### Backtracking ##################################################### 
 public List<List<Integer>> combinationSum(int[] candidates, int target) {
     List<List<Integer>> resultList = new LinkedList<>();
     Arrays.sort(candidates);
     List<Integer> localList = new ArrayList<>();
     int sum = 0;
     combinationSumHelper(candidates, 0 ,resultList, localList, sum,target);
     return resultList;
 }
 
 private void combinationSumHelper(int[] candidates, int k, List<List<Integer>> resultList, List<Integer> localList, int sum, int target) {
     if(sum > target) return;
     int m = candidates.length;
     if(sum == target) resultList.add(new LinkedList<>(localList));
     for(int i=k;i<m;i++) {
         if(candidates[i] <= target) {
             localList.add(candidates[i]);
             combinationSumHelper(candidates,i,resultList, localList, sum + candidates[i],target); //PICK SAME ELEMENT so use 'i' instead of k
             k += 1;
             localList.remove(localList.size() - 1);
         }
     }
 }

//##################################################### SKIENA WAY ##################################################### 
void genSolution(int last_choice,int level,int choice,vector<int>&candidates,vector<int>& local_store,int& local_result
   ,int target,vector< vector<int> >&result) {
       if(local_result == target) {
           result.push_back(local_store);
       } else {
         level += 1;  //unnecessary however it is to compute the levels after I get the result I need to set it zero 
             for(int i=last_choice;i<candidates.size();i++) {
                if(local_result + candidates[i] <= target) {
                    local_result += candidates[i];
                    local_store.push_back(candidates[i]);
                    genSolution(i,level,choice,candidates,local_store,local_result,target,result);
                    local_result -= candidates[i];
                    local_store.pop_back();
              }
          }
       }
}
vector<vector<int> > combinationSum(vector<int>& candidates, int target) {
       vector<vector<int> > result;
       int level = 0;
       int choice = 0;
       int local_result = 0;
       vector<int> local_store;
       int last_choice = 0;
       genSolution(last_choice,level,choice,candidates,local_store,local_result,target,result);
       return result;
}


//##################################################### DFS WAY ##################################################### 
void dfsHelper(int level_,vector<int>& iv,vector<int>& cv,vector<vector<int> >& result,int target) {
  if(target < 0) {
	return;
  }
  if(target == 0) {
     result.push_back(cv);
     return;	
  }
  for(int i=level_;i<iv.size();i++) {
    cv.push_back(iv[i]);
    //level_ += 1;
    dfsHelper(level_,iv,cv,result,target-iv[i]);
    level_ += 1;
    cv.pop_back();
}
 
}

vector<vector<int> > getCombinationSum(vector<int>& iv,int target) {

	int n = iv.size();
	sort(iv.begin(),iv.end());
	vector<vector<int> > result;
	int level_ = 0;
	vector<int> cv;
	dfsHelper(level_,iv,cv,result,target);
	return result;

}

int main() {

}
