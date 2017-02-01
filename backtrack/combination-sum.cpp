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
