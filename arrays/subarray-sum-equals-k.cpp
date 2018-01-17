//Subarray Sum Equals K
//Given an array of integers and an integer k, you need to find the total number of continuous subarrays whose sum equals to k.
//Example 1:
//Input:nums = [1,1,1], k = 2
//Output: 2
//Note:
//The length of the array is in range [1, 20,000].
//The range of numbers in the array is [-1000, 1000] and the range of the integer k is [-1e7, 1e7].

//########################## Prefix sum + cumulative sum ########################## 
//[0,0,0,0,0,0,0,0,0,0]
//0
//o/p : 55 
//Reason to use the map is because we might get same sum so we cannot use set
int subarraySum(vector<int>& nums, int k) {
  int cum=0; // cumulated sum
  map<int,int> rec; // prefix sum recorder or cumulative sum recorder
  int cnt = 0; // number of found subarray
  rec[0]++; // to take into account those subarrays that begin with index 0
  for(int i=0;i<nums.size();i++){
      cum += nums[i]; 
      cnt += rec[cum-k]; //get the value from map if value exists out 1 else 0
      rec[cum]++;
  }
  return cnt;
}

//############################ pytonic  ########################################################
//def subarraySum(self, nums, k):
//        sums = {0:1} # prefix sum array
//        res = s = 0
//        for n in nums:
//            s += n # increment current sum
//            res += sums.get(s - k, 0) # check if there is a prefix subarray we can take out to reach k
//            sums[s] = sums.get(s, 0) + 1 # add current sum to sum count
//        return res
