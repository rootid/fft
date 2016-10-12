#include<iostream>
#include<vector>
using namespace std;

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
int main() {
  int target = 7;
  vector<int> av ({2,2,3,7});
  combinationSum(av,target);
}
