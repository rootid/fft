//Given a collection of distinct numbers, return all possible permutations.
//For example,
//[1,2,3] have the following permutations:
//[
//  [1,2,3],
//  [1,3,2],
//  [2,1,3],
//  [2,3,1],
//  [3,1,2],
//  [3,2,1]
//]


vector<vector<int>> permute(vector<int>& nums) {

#include<iostream>
#include<vector>
using namespace std;

//1,2,3
//Iterative version
vector<vector<int> > permute(vector<int>& nums) {

  vector< vector<int> > result;
  int len = nums.size();
  if(len == 0) {
    return result;
  }
  vector<int> l0;
  l0.push_back(nums[0]);
  result.push_back(l0);
  //iterate over elements
  for(int i=1;i<len;i++) {
    vector< vector<int> > tmp;
    //list of candidates/positions
    for(int j=0;j<=i;j++) {
      for(auto itr = result.begin();itr!=result.end();itr++) {
        vector<int> curr1(*itr); // copy the list into new vector
        curr1.insert(curr1.begin()+j,nums[i]); // insert num[i] at pos j
        tmp.push_back(curr1); // insert new list into tmp

      }
    }
    result = tmp;
  }
  return result;
}

int main() {

  vector<int> input( {1,2,3} );
  permute(input);
}
    

}


//Move semantics
//
vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> v(1,vector<int>());
    for (int i = 0; i < nums.size(); ++i) {
        vector<vector<int>> tv(move(v));
        for (int j = 0; j < tv.size(); ++j) {
            for (int k = 0; k <= tv[0].size(); ++k) {
                vector<int> tmp(tv[j]);
                tmp.insert(tmp.begin()+k,nums[i]);
                v.push_back(move(tmp));
            }
        }
    }
    return v;
}


private:
vector<vector<int> > v;
vector<int> save;
vector<bool> visit;

public:
vector<vector<int> > permute(vector<int> &num) {
    v.clear();
    int size = num.size();
    
    visit.resize(size);
    save.resize(size);
    
    fill(visit.begin(), visit.end(), false);

    dfs(num, 0, size);
    return v;
}
void dfs(vector<int> num, int k,int size,vector<bool>& visit,vector<vector<int> >&result){
    if(k == size){
       result.push_back(save);
        return;
    }
    
    for(int i = 0; i < size; i++){
        if(!visit[i]){
            visit[i] = true;
            save[k] = num[i];
            dfs(num, k + 1, size);
            visit[i] = false;
        }
    }
}

    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ret;
        int n = nums.size();
        if (n == 0)
            return ret;
        
        if (n == 1)
        {
            ret.push_back(nums);
            return ret;
        }
        
        int i = 0, j = 0, len = 0;
        vector<int> curNums;
        vector<int> per;
        vector<vector<int>> temp;
        
        for (i = 0; i < n; i++)
        {
            curNums = nums;
            curNums.erase(curNums.begin()+i);
            temp = permute(curNums);
            len = temp.size();
            
            for (j = 0; j < len; j++)
            {
                per = temp[j];
                per.push_back(nums[i]);
                ret.push_back(per);
            }
        }
            
        return ret;
    }



