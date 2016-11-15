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

void dfsHelper(vector<int> iv,vector<int> cv,vector<bool> visited,int start_level,int k,vector<vector<int> >& result) {
    if(k == start_level) {
      result.push_back(cv);
      return;
    }
    for(int i=start_level;i<k;i++) {
      if(visited[i] == false) {
        visited[i] = true;
        cv.push_back(iv[i]);
        dfsHelper(iv,cv,start_level,k,result);
        cv.pop_back();
      }
        
    }

    }
vector<vector<int>> combine(int n, int k) {
    for(auto i:n) {
      cv.push_back(i);
    }
    vector<vector<int> > result;
    vector<bool> visited(n+1,false);
    int start_level = 0;
    dfsHelper(iv,cv,visited,start_level,k,result);
    return result;
}

vector<vector<int> > genHelper(int n,int k) {

  if(n == k) {
    return helper;
  }
}


