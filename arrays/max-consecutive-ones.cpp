//Max Consecutive Ones
//Given a binary array, find the maximum number of consecutive 1s in this
//array.
//Example 1:
//Input: [1,1,0,1,1,1]
//Output: 3
//Explanation: The first two digits or the last three digits are consecutive
//1s.
//    The maximum number of consecutive 1s is 3.
//Note:
//The input array will only contain 0 and 1.
//The length of input array is a positive integer and will not exceed 10,000

//################################################### O(n) + append 0 to array ###################################################
int findMaxConsecutiveOnes(vector<int>& nums) {
  int maxLen = 0;
  int last_idx = 0;
  int c_idx =0;
  nums.push_back(0);
  for(auto &i:nums) {
      c_idx += 1;
      if(i == 0) {
          if( (c_idx - last_idx) > maxLen) {
              maxLen = c_idx - last_idx - 1;
          }
          last_idx = c_idx;
      }
  }
  return maxLen;
}

//################################################### Python  ###################################################
//################################################### O(n) + append 0 to array ###################################################
class Solution(object):
    def findMaxConsecutiveOnes(self, nums):
        nums.append(0)
        lo = 0
        ret = 0
        for hi,n in enumerate(nums):
            if n==0:
                ret = max(ret, hi-lo)
                lo = hi+1
        return ret


