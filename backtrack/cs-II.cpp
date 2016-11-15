//## Combination Sum III
//### Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.
//Example 1:
//Input: k = 3, n = 7
//Output:
//[[1,2,4]]
//Example 2:
//Input: k = 3, n = 9
//Output:
//[[1,2,6], [1,3,5], [2,3,4]]
	
#include "../headers/global.hpp"
//TO keep track of visited nodes use the visited set and check whether it is
//visited
void dfsHelper(int level_,vector<int>& iv,vector<int>& cv,vector<vector<int> >& result,int target) {
  if(target < 0) {
	return;
  }
  if(target == 0) {
     result.push_back(cv);
     return;	
  }

  int pre = -1;
  for(int i=level_;i<iv.size();i++) {
    if(pre != iv[i]) {
      cv.push_back(iv[i]);
      //level_ += 1;
      dfsHelper(i+1,iv,cv,result,target-iv[i]);
      pre = iv[i];
      //level_ += 1;
      cv.pop_back();
    }
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
