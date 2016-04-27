//Majority Element II
//Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times. The algorithm should run in linear time and in O(1) space.

#include<iostream>
#include<vector>
using namespace std;


vector<int> majorityElement(vector<int>& nums) {

  int len = nums.size();
  int cnt1 = 0;
  int cnt2 = 0;
  int ele1 = 0;
  int ele2 = 0;
  vector<int> result;
  for(int i=0;i<len;i++) {
    if(ele1 == nums[i]) {
      cnt1 += 1;
    } else if(ele2 == nums[i]) {
      cnt2 +=1;
    } else {
      if(cnt1 && cnt2) {
        cnt1 -=1;
        cnt2 -=1;
      }
      else if(cnt1 == 0) {
        cnt1 = 1;
        ele1 = nums[i];
      } else if(cnt2 == 0 )  {
        cnt2 = 1;
        ele2 = nums[i];
      }
    }
  }
  vector<int> candidate;
  //cout << "( " << cnt1 << "," << cnt2 << " ) = " << ele1 << "," << ele2 << endl;
  //Checks are present to avoid duplicates , this can be eliminated iff we
  //choose 2 distinct element
  //eg. ele1 = 1,ele2 = 2
  if(cnt1 > 0) {
    candidate.push_back(ele1);
  }
  if(cnt2 > 0) {
   candidate.push_back(ele2);
  }
  for(int i = 0; i < candidate.size(); i++){
      int count = 0;
      for(int j = 0; j < len; j++){
          if(nums[j] == candidate[i]) {
            count++;
          }
      }
      if(count > len/3) { 
        result.push_back(candidate[i]);
      }
  }
  return result;
}



int main(int argc, char *argv[])
{

  //int a[] = {1,1,1,2,2};
  int a[] = {0,0,0};
  vector<int> av(a,a+sizeof(a)/sizeof(a[0]));
  vector<int> bv= majorityElement(av);

  return 0;
}
