//Majority Element I
//Given an integer array of size n, find all elements that appear more than ⌊
//n/2 ⌋ times. The algorithm should run in linear time and in O(1) space.
#include<iostream>
#include<vector>
using namespace std;

//######################################### Voting algorithm #########################################
public int majorityElement(int[] nums) {
    int m = nums.length;
    int majElm = nums[0];
    int freqCount = 1;
    for(int i=1;i<m;i++) {
        //update freq Count
        if(majElm != nums[i]) freqCount--;
        else freqCount++;
        if(freqCount == 0)  { //2,2,1,1,1,2,2 : o/p : 2
            freqCount = 1;
            majElm = nums[i];
        }
    }
    return majElm;
}

//######################################### Voting algorithm #########################################
int majorityElement(vector<int>& nums) {
  int majorityEle = nums[0];
  int count = 1;
  int len = nums.size();
  for(int i=1;i<len;i++) {
    if(majorityEle == nums[i]) {
      count += 1;
    } else {
      count -= 1;
      if(count == 0) {
        majorityEle = nums[i];
        count = 1;
      }
    }
  }
  return majorityEle;
}



int main(int argc, char *argv[])
{

  int a[] = {1,1,1,2,2};
  vector<int> av(a,a+sizeof(a)/sizeof(a[0]));
  int ans = majorityElement(av);
  cout << "ans " << ans << endl;

  return 0;
}
