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
#include "../headers/global.hpp"

//C(n,k)=C(n-1,k-1)+C(n-1,k).
//################################################ Recursion  ################################################ 
public List<List<Integer>> combine(int n, int k) {
    List<Integer> soFar = new LinkedList<>();
    List<List<Integer>> result = new ArrayList<>();
    combineHelper(n,k,1,soFar,result);
    return result;
}

public void combineHelper(int n,int k, int start,List<Integer>soFar, List<List<Integer>> result) {
    if(k == soFar.size()) {
        result.add(new ArrayList(soFar));
    }
    for(int i=start;i<=n;i++) {
        soFar.add(i);
        combineHelper(n,k,i+1,soFar,result); //NOTE : i increamented not start To avoid duplicates (2,3) and (3,2)
        soFar.remove(soFar.size() - 1);
    }
}

//################################################ Combine ################################################ 
//C(n,k)=C(n-1,k-1)+C(n-1,k).
public class Solution {
	public List<List<Integer>> combine(int n, int k) {
    	if (k > n || k == 0) return new LinkedList<>();
    	List<List<Integer>> ans = combine(n - 1, k - 1);
    	if (ans.size() == 0) ans.add(new LinkedList<>(Arrays.asList(n))); //asList is needed to create a list with a single list in it.
																		  //return new LinkedList<List<Integer>>(Arrays.<List<Integer>>asList((List<Integer>)row));
    	else ans.forEach(e-> e.add(n));
    	ans.addAll(combine(n - 1, k)); 
    	return ans;
	}
}



//################################################ So Far way ################################################ 
void combine_helper(int n,int k,vector<vector<int> >&result, vector<int> so_far,int state) {
      if(so_far.size() == k) {
          result.push_back(so_far);
      }
      for(int i=state;i<=n;i++) {
          so_far.push_back(i);
          combine_helper(n,k,result,so_far,++state);
          so_far.pop_back();
      }
}
  
vector<vector<int>> combine(int n, int k) {
      vector< vector<int> > result;
      vector<int> so_far;
      int state = 1;
      combine_helper(n,k,result,so_far,state);
      return result;
}
//################################################ Iterative  ################################################ 
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
//################################################ DFS ################################################ 
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
//################################################ Bit manipulation ################################################ 
vector<vector<int> > combine(int n, int k) {
         vector<vector<int> >res;
         vector<int>tmpres;
         //Maximum value of bit = (1<<n) - (1<<(n-k))
         for(int bit = (1<<k) - 1; bit <= (1<<n) - (1<<(n-k)); bit = NextN(bit))
         {
             tmpres.clear();
             for(int i = 0; i < n; i++)
             {
                 if(bit & (1<<i))
                     tmpres.push_back(i+1);
             }
             res.push_back(tmpres);
         }
         return res;
}
//Returns the smallest integer M that is greater than N, so that the binary representation of M and N has the same number 1
int NextN(int N) 
{ 
     int x = N&(-N);      
     int t = N+x; 
     return t | ((N^t)/x)>>2; 
 }
int main() {
  //vector< vector<int> > lv(1);
  //print_result(lv);
  combine(6,3);
}
