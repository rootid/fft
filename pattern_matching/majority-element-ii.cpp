//Majority Element II
//Given an integer array of size n, find all elements that appear more than ⌊
//n/3 ⌋ times. The algorithm should run in linear time and in O(1) space.

#include<iostream>
#include<vector>
using namespace std;


//# 3 cases
//1. there are no elements that appears more than n/3 times, then whatever the
//algorithm
// got from 1st round wound be rejected in the second round.
//2. there are only one elements that appears more than n/3 times, after 1st
//round one of
// the candicate must be that appears more than n/3 times(<2n/3 other elements could only
// pair out for <n/3 times), the other candicate is not necessarily be the second most frequent
// but it would be rejected in 2nd round.
//3. there are two elments appears more than n/3 times, candicates would
//contain both of
// them. (<n/3 other elements couldn't pair out any of the majorities.)
//#########################################  #########################################
public List<Integer> majorityElement(int[] nums) {
     Integer major1 = null, major2 = null, cnt1 = 0, cnt2 = 0;
     for (Integer num : nums) {
         if (num.equals(major1)) {
             cnt1++;
         } else if (num.equals(major2)) {
             cnt2++;
         } else if (cnt1 == 0) {
             major1 = num;
             cnt1 = 1;
         } else if (cnt2 == 0) {
             major2 = num;
             cnt2 = 1;
         } else {
             cnt1--;
             cnt2--;
         }
     }

     cnt1 = cnt2 = 0;
     for (Integer num : nums) {
         if (num.equals(major1)) cnt1++;
         else if (num.equals(major2)) cnt2++;
     }

     List<Integer> result = new ArrayList<>();
     if (cnt1 > nums.length / 3) result.add(major1);
     if (cnt2 > nums.length / 3) result.add(major2);
     return result;
 }
//######################################### Boyer-Moore Majority  #########################################
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
