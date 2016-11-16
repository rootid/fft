#include "../headers/global.hpp"

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
//
//Iterative :  1 ( k times)  4(k times)
//             2 ( k-1 times) 3(k-1)
//             3 ( k-2 )      2(k-2)
void print_result(vector<vector<int> >& r);


vector<vector<int>> combine(int n, int k) {
    
    vector<vector<int> > result;
    vector<vector<int> > cv(1);
    vector<int> tmp;
    for(int i=1;i<=n;i++) {
      int len = cv.size();
      for(int j=0;j<len;j++) {
        tmp = cv[j];
        tmp.push_back(i);
        if(k == tmp.size()) {
          result.push_back(tmp);
        } else {
          cv.push_back(tmp);
        }
      }
    }
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
  //vector< vector<int> > lv(1);
  //print_result(lv);

  combine(6,3);
}
