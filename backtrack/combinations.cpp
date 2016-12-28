//## Combinations
//### Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.
//For example,
//If n = 4 and k = 2, a solution is:
//[
//  [2,4],
//  [3,4],
//  [2,3],
//  [1,2],
//  [1,3],
//  [1,4],
//]

#include "../headers/global.hpp"

void print_result(vector<vector<int> >& r);

void dfsHelper(int start,int end,int k,vector<int>&iv,vector<int>& cv,vector<vector<int> >& result) {
    if(k == 0) {
      result.push_back(cv);
      return;
    }
    for(int i=start;i<end-k+1;i++) {
        cv.push_back(iv[i]);
        dfsHelper(i+1,end,k-1,iv,cv,result);
        cv.pop_back();
    }
}

vector<vector<int>> combine(int n, int k) {
    vector<int> iv;
    for(int i=1;i<=n;i++) {
      iv.push_back(i);
    }
    vector<vector<int> > result;
    vector<int> cv;
    int start = 0;
    int end = n;
    dfsHelper(start,end,k,iv,cv,result);
    print_result(result);
    return result;
}

void print_result(vector<vector<int> >& r) {
  for(auto& v:r) {
    for(auto& i:v) {
      cout << i << ",";
    }
    cout << endl;
  }
}

int main() {
  combine(4,2);
}



