//Minimum Size Subarray Sum
//Given an array of n positive integers and a positive integer s, find the minimal length of a contiguous subarray of which the sum ≥ s. If there isn't one, return 0 instead.
//For example, given the array [2,3,1,2,4,3] and s = 7,
//the subarray [4,3] has the minimal length under the problem constraint.
//click to show more practice.
//More practice:
//If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log n).


//############################################ O(n) + sliding window ############################################ 
int minSubArrayLen(int s, vector<int>& nums) {
    int num_len= nums.size();
    int left=0, right=0, total=0, min_len= num_len+1;
    while (right < num_len) {
        // move right silder forward till total >= s
        do { 
          total += nums[right++]; 
        } while (right<num_len && total< s);
        // move left slider forward while maintaining total >= s
        while (left<right && total-nums[left]>=s) {
          total -= nums[left++];
        }
        // record if it's the minimum
        if (total>=s && min_len> right- left) 
            min_len= right- left;
    }
    return min_len<=num_len ? min_len: 0;
}
//############################################ O(n) + cumulative sum ############################################ 
int minSubArrayLen(int s, vector<int>& nums) {
  int start = 0, sum = 0, minLength = INT_MAX;
  for(int i = 0; i<nums.size(); i++) {
      sum += nums[i]; //adds sum [2,5,6,8] 
      //while loops at most N times during looping for-loop from 1 to N. So, N + N = O(N).
      //[6,1,6,1,6,1,6,1,6,1] s= 7
      //this loop runs at most n times so O(n)
      while(sum >= s) {
          minLength = min(minLength, i - start + 1); //found sum update the minLen
          sum -= nums[start++]; //update sum
      }
  }
  return minLength == INT_MAX? 0 : minLength;
}

//############################################ O(n) + 2 pointers  ############################################ 
int minSubArrayLen(int s, vector<int>& nums) {
    int n = nums.size(), left = 0, right = 0, sum = 0, minlen = INT_MAX;
    while (right < n) {
        do sum += nums[right++];
        while (right < n && sum < s);
        while (left < right && sum - nums[left] >= s)
            sum -= nums[left++];
        if (sum >= s) minlen = min(minlen, right - left);
    }
    return minlen == INT_MAX ? 0 : minlen;
}

//############################################ O(n log n) + in built partial_sum + upper_bound  #################################### 
int minSubArrayLen(int s, vector<int>& nums) {
    vector<int> sums(nums.size() + 1, 0);
    partial_sum(nums.begin(),nums.end(), sums.begin()+1);
    int n = nums.size(), minlen = INT_MAX;
    for (int i = 1; i <= n; i++) { 
        if (sums[i] >= s) {
            auto p = upper_bound(sums.begin(), sums.begin()+i, sums[i] - s);
            if (p != sums.end()) 
                minlen = min(minlen, i - (int)(p-sums.begin()) + 1);
        }
    }
    return minlen == INT_MAX ? 0 : minlen;
}

//############################################ O(n log n) + binary search #################################### 

int minSubArrayLen(int s, vector<int>& nums) {
        vector<int> sums = accumulate(nums);
        int n = nums.size(), minlen = INT_MAX;
        for (int i = 1; i <= n; i++) { 
            if (sums[i] >= s) {
                int p = upper_bound(sums, 0, i, sums[i] - s);
                if (p != -1) minlen = min(minlen, i - p + 1);
            }
        }
        return minlen == INT_MAX ? 0 : minlen;
    }
private:
    vector<int> accumulate(vector<int>& nums) {
        int n = nums.size();
        vector<int> sums(n + 1, 0);
        for (int i = 1; i <= n; i++) 
            sums[i] = nums[i - 1] + sums[i - 1];
        return sums;
    }
    int upper_bound(vector<int>& sums, int left, int right, int target) {
        int l = left, r = right;
        while (l < r) {
            int m = l + ((r - l) >> 1);
            if (sums[m] <= target) l = m + 1;
            else r = m;
        }
        return sums[r] > target ? r : -1;
    }
