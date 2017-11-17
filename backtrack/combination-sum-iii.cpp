//Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.
//Example 1:
//Input: k = 3, n = 7
//Output:
//[[1,2,4]]
//Example 2:
//Input: k = 3, n = 9
//Output:
//[[1,2,6], [1,3,5], [2,3,4]]

#include "../headers/global.hpp"



//######################################### DFS - Backtracking ######################################### 
public List<List<Integer>> combinationSum3(int k, int n) {
        List<List<Integer>> result = new LinkedList<>();
    List<Integer> localList = new ArrayList<>();
    combinationSumHelper(n,k,1,localList,result);
    return  result;
}

private void combinationSumHelper(int n,int k, int start, List<Integer> localList,List<List<Integer>> result) {
    if(n <0 || localList.size() > k) return;
    if(localList.size() == k && n ==0) 
        result.add(new ArrayList<>(localList));
    for(int i=start;i<=9;i++) {
        if(n-i >= 0) { //Pruning to pick only + sum
            localList.add(i);
            combinationSumHelper(n - i, k, i+1, localList, result);
            localList.remove(localList.size() - 1);
        }
    }
    
}

//######################################### DFS - Backtracking  ######################################### 
public List<List<Integer>> combinationSum3(int k, int n) {
    List<List<Integer>> result = new LinkedList<>();
    List<Integer> localList = new ArrayList<>();
    combinationSumHelper(n,k,1,localList,result);
    return  result;
}

private void combinationSumHelper(int n,int k, int start, List<Integer> localList,List<List<Integer>> result) {
    if(n <0) return;
    if(n == 0 && k == 0) result.add(new ArrayList<>(localList));
    for(int i=start;i<=9;i++) { //(start-9)
        localList.add(i);
        combinationSumHelper(n - i, k - 1, i+1, localList, result);
        localList.remove(localList.size() - 1);
    }
}

//######################################### DFS ######################################### 
void dfs(vector<vector <int> > &res,vector<int>& cv,int start,int k,int n) {
      
      if(n < 0 || cv.size() > k) {
          return; // prune
      }
      if(cv.size() == k && n == 0) {
          res.push_back(cv);
      }
      for(int i=start;i<=9;i++) {
        if(n-i >= 0 ) {  //Biggest gain pruning while traversing
          cv.push_back(i);
          dfs(res,cv,i+1,k,n-i);
          cv.pop_back();
        }
      }
      
  }
  
vector<vector<int> > combinationSum3(int k, int n) {
      //iv : sz = 9
      vector<vector<int> > res;    
      vector<int> cv;
      int start = 1;
      dfs(res,cv,start,k,n);
      return res;
}

int main() {
  combinationSum3();
}
