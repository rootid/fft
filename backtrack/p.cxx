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

/**            [  1 , 2  ]
                 ^  ^  ^
insert 3:        |  |  |    there are 3 positions to insert

**/
vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> result;
    vector<vector<int>> buffer;
    result.push_back(vector<int>());

    for(int i=0; i<nums.size(); ++i){
        int vec_n = result.size();
        for(int j=0; j<vec_n; ++j){
            int vec_size = result[j].size();
            for(int k=0; k<=vec_size; ++k){
                vector<int> tmp(result[j]);
                tmp.insert(tmp.begin()+k, nums[i]);
                buffer.push_back(tmp);
            }
        }
        result=buffer;
        buffer.clear();
    }

    return result;
}


int main() {

  vector<int> input( {1,2,3} );
  permute(input);
}
