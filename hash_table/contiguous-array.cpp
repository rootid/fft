//Contiguous Array
//Given a binary array, find the maximum length of a contiguous subarray with equal number of 0 and 1.
//Example 1:
//Input: [0,1]
//Output: 2
//Explanation: [0, 1] is the longest contiguous subarray with equal number of 0 and 1.
//Example 2:
//Input: [0,1,0]
//Output: 2
//Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.
//Note: The length of the given binary array will not exceed 50,000.

//######################## Reduction to Maximum Size Subarray Sum Equals k ########################33
//where zeros are -1, ones are ones, and k is zero. 
//Since in this problem the range of possible sums is 
//[-size...size], we can use an array instead of unordered_map. 
//We can consider size as the zero point, so the array indexes will be [0... 2 * size].

int findMaxLength(vector<int>& nums) {
    int size = nums.size(), ballance = size, max_len = 0;
    int newNums[size * 2 + 1] = {};
    for (auto i = 0; i < size; ++i) {
        if(nums[i] == 1) { 
          ballance += nums[i];
        } else {
          ballance += -1;
        }
        if (ballance == size) {
          max_len = i + 1;
        } else {
            if (newNums[ballance] != 0) {
              max_len = max(max_len, i - newNums[ballance] + 1);
            } else {
              newNums[ballance] = i + 1;
            }
        }
    }
    return max_len;
}



//len(A) + len(B) = len
//sum(A) + sum(B) = (sum(A) + len(B)) / 2 = sum
//// so we have
//2 * sum - len = 2 * sum(A) - len(A)
//You can see A and C have the same value = 2 * sum - len.
//if two prefix subarrays A and C of nums have the same 2 * sum - len, we can get len(B) = len(C) - len(A)
int findMaxLength(vector<int>& nums) {
    int sum = 0, max_len = 0;
    unordered_map<int, int> m;
    m[0] = -1;
    for (int i = 0; i < nums.size(); ++i) {
        sum += nums[i];
        int k = 2 * sum - i - 1; //idx starts from 0 so substract 1, i = len of 
        if (m.count(k)) { 
          max_len = max(max_len, i - m[k]); //actual_len = len - stored len
        } else { 
          m[k] = i; //store the length of prefix sum at k
        }
    }
    return max_len;
}


