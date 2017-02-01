#include<iostream>
#include<vector>
using namespace std;
//1,2,3
//backtrack version
void permuteHelper(vector<int>& input,int k,vector<vector <int> >& result) {
    if (k == input.size() ){
        result.push_back(input);
        return;
    } 
    for (int i=k;i<input.size();i++) {            
        swap(input[i],input[k]);
        permuteHelper(input,k+1,result);
        swap(input[k],input[i]);
    }
}
void dfs(vector<int>& num, int k,int size,vector<bool>& visit,vector<int> tmp,vector<vector<int> >&result){
    if(k == size){
       result.push_back(tmp);
        return;
    }
    for(int i = 0; i < size; i++){
        if(!visit[i]){
            visit[i] = true;
            tmp[k] = num[i];
            dfs(num, k + 1, size,visit,tmp,result);
            visit[i] = false;
        }
    }
}

vector<vector<int> > permute(vector<int>& nums) {
  vector< vector<int> > result;
  int len = nums.size();
  if(len == 0) {
    return result;
  }
  //permuteHelper(nums,0,result);
  vector<bool> visit;
  visit.resize(len);
  fill(visit.begin(), visit.end(), false);
  vector<int> tmp;
  tmp.resize(len);
  dfs(nums,0,len,visit,tmp,result);
  return result;
}

int main() {
  vector<int> input( {1,2,3} );
  permute(input);
}
