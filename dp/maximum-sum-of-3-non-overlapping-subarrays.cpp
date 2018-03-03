//Maximum Sum of 3 Non-Overlapping Subarrays
//In a given array nums of positive integers, find three non-overlapping
//subarrays with maximum sum.
//Each subarray will be of size k, and we want to maximize the sum of all 3*k
//entries.
//Return the result as a list of indices representing the starting position of
//each interval (0-indexed). If there are multiple answers, return the
//lexicographically smallest one.
//Example:
//Input: [1,2,1,2,6,7,5,1], 2
//Output: [0, 3, 5]
//Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting
//indices [0, 3, 5].
//We could have also taken [2, 1], but an answer of [1, 3, 5] would be
//lexicographically larger.
//Note:
//nums.length will be between 1 and 20000.
//nums[i] will be between 1 and 65535.
//k will be between 1 and floor(nums.length / 3).


//######################################### DP #########################################
//This is a more general DP solution, and it is similar to that buy and sell
//stock problem.
//dp[i][j] stands for in i th sum, the max non-overlap sum we can have from 0
//to j
//id[i][j] stands for in i th sum, the first starting index for that sum.
class Solution {
    public int[] maxSumOfThreeSubarrays(int[] nums, int k) {
        int[][] dp = new int[4][nums.length + 1];
        int sum = 0;
        int[] accu = new int[nums.length + 1];
        for(int i = 0; i < nums.length; i++) {
            sum += nums[i];
            accu[i] = sum;
        }
        int[][] id = new int[4][nums.length + 1];
        int max = 0, inId = 0;
        for(int i = 1; i < 4; i++) {
            for(int j = k-1 ; j < nums.length; j++) {
                int tmpmax = j - k < 0 ? accu[j] : accu[j] - accu[j-k] + dp[i-1][j-k];
                if(j - k >= 0) {
                    dp[i][j] = dp[i][j-1];
                    id[i][j] = id[i][j-1];
                }
                if(j > 0 && tmpmax > dp[i][j-1]) {
                    dp[i][j] = tmpmax;
                    id[i][j] = j-k+1;
                }
            }
        }
        int[] res = new int[3];
        res[2] = id[3][nums.length-1];
        res[1] = id[2][res[2] - 1];
        res[0] = id[1][res[1] - 1];
        return res;
    }
}
//######################################### Backtrack  #########################################
//The index in my pos[i][j] array means ending in position j - 1, the starting
//position of ith element we should take.
//We first check the last element we should take using pos[3][n], where n is
//the length of array, aka the last element in the array. From there, we get
//the starting position of our 3rd element, let's call it p3. Then we backtrack
//to get the 2nd element by visiting pos[2][p3] (ending in p3 -1). Let's call
//it p2. Last, we visit pos[1][p2] to get the 1st element.
    public int[] maxSumOfThreeSubarrays(int[] nums, int k) {
        int[] res = new int[3];
        if (nums == null || k <= 0 || nums.length < 3 * k) {
            return res;
        }
        int n = nums.length;
        int[] sums = new int[n + 1];
        for (int i = 1; i <= n; i++) {
            sums[i] = sums[i - 1] + nums[i - 1];
        }

        int[][] dp = new int[4][n + 1];
        int[][] pos = new int[4][n + 1];

        for (int i = 1; i <= 3; i++) {
            // Notice, here position is off by 1
            for (int j = k * i; j <= n; j++) {
                int curSum = sums[j] - sums[j - k] + dp[i - 1][j - k];
                if (curSum > dp[i][j - 1]) {
                    dp[i][j] = curSum;
                    pos[i][j] = j - k;
                } else {
                    dp[i][j] = dp[i][j - 1];
                    pos[i][j] = pos[i][j - 1];
                }
            }
        }
        int index = n;
        for (int i = 2; i >= 0; i--) {
            res[i] = pos[i + 1][index];
            index = res[i];
        }
        return res;
    }
//######################################### DP #########################################
// [0, i-1] - [i, i+k-1] - [i+k, n-1]
//The question asks for three non-overlapping intervals with maximum sum of all
//3 intervals. If the middle interval is [i, i+k-1], where k <= i <= n-2k, the
//left interval has to be in subrange [0, i-1], and the right interval is from
//subrange [i+k, n-1].
//So the following solution is based on DP.
//posLeft[i] is the starting index for the left interval in range [0, i];
//posRight[i] is the starting index for the right interval in range [i, n-1];
//Then we test every possible starting index of middle interval, i.e. k <= i <=
//n-2k, and we can get the corresponding left and right max sum intervals
//easily from DP. And the run time is O(n).
//Caution. In order to get lexicographical smallest order, when there are two
//intervals with equal max sum, always select the left most one. So in the
//code, the if condition is ">= tot" for right interval due to backward
//searching, and "> tot" for left interval. Thanks to @lee215 for pointing this
//out!

//######################################### DP  #########################################
class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size();

        // sum[i] means nums[0] + nums[1] + ... + nums[i-1]
        vector<int> sum = {0};
        for (int& num:nums) {
            sum.push_back(sum.back() + num);
        }

        // posLeft[i] means if the middle interval start index is i, what's the index for left interval
        // such that left interval has the maximum sum.
        // initial value is 0 because if middle interval start index is k, then left interval start index is 0.
        vector<int> posLeft(n, 0);
        int leftMaxSum = sum[k] - sum[0]; // if left interval start index is 0, what's the sum of the left interval
        int leftMaxSumIndex = 0;
        // middle interval start index can only be k, k + 1, ... , n - 2*k and we start from k + 1
        // since i = k is our initial value.
        for (int i = k + 1; i <= n - 2*k; i++) {
            if (sum[i]-sum[i-k] > leftMaxSum) {
                posLeft[i] = i-k;
                leftMaxSum = sum[i]-sum[i-k];
                leftMaxSumIndex = i-k; // if left interval start index is i - k, the sum of the left interval is bigger.
            } else {
                posLeft[i] = leftMaxSumIndex;
            }
        }


        // posRight[i] means if the middle interval start index is i, what's the index for right interval
        // such that right interval has the maximum sum.
        // initial value is n-k because if middle interval start index is n - 2*k, then right interval start index is n-k.
        vector<int> posRight(n,n-k);
        int rightMaxSum = sum[n] - sum[n-k];
        int rightMaxSumIndex = n-k;
        // caution: the condition is ">= tot" for right interval, and "> tot" for left interval
        // middle interval start index can only be n - 2*k, n - 2*k - 1, ... , k and we start from n - 2*k - 1
        // since i = n - 2*k is our initial value
        for (int i = n - 2*k - 1; i >= k; i--) {
            if (sum[i+2*k]-sum[i+k] >= rightMaxSum) {
                posRight[i] = i + k;
                rightMaxSum = sum[i+2*k]-sum[i+k];
                rightMaxSumIndex = i + k;
            } else {
                posRight[i] = rightMaxSumIndex;
            }
        }
        int maxSum = 0;
        vector<int> ans(3,0);
        // test all possible middle interval
        for (int i = k; i <= n-2*k; i++) {
            int l = posLeft[i], r = posRight[i];
            int totalSum = (sum[i+k]-sum[i]) + (sum[l+k]-sum[l]) + (sum[r+k]-sum[r]);
            if (totalSum > maxSum) {
                maxSum = totalSum;
                ans = {l, i, r};
            }
        }
        return ans;
    }
};
//######################################### DP  #########################################
class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size(), maxsum = 0;
        vector<int> sum = {0}, posLeft(n, 0), posRight(n, n-k), ans(3, 0);
        for (int i:nums) sum.push_back(sum.back()+i);
       // DP for starting index of the left max sum interval
        for (int i = k, tot = sum[k]-sum[0]; i < n; i++) {
            if (sum[i+1]-sum[i+1-k] > tot) {
                posLeft[i] = i+1-k;
                tot = sum[i+1]-sum[i+1-k];
            }
            else
                posLeft[i] = posLeft[i-1];
        }
        // DP for starting index of the right max sum interval
        // caution: the condition is ">= tot" for right interval, and "> tot" for left interval
        for (int i = n-k-1, tot = sum[n]-sum[n-k]; i >= 0; i--) {
            if (sum[i+k]-sum[i] >= tot) {
                posRight[i] = i;
                tot = sum[i+k]-sum[i];
            }
            else
                posRight[i] = posRight[i+1];
        }
        // test all possible middle interval
        for (int i = k; i <= n-2*k; i++) {
            int l = posLeft[i-1], r = posRight[i+k];
            int tot = (sum[i+k]-sum[i]) + (sum[l+k]-sum[l]) + (sum[r+k]-sum[r]);
            if (tot > maxsum) {
                maxsum = tot;
                ans = {l, i, r};
            }
        }
        return ans;
    }
};

//######################################### DP  #########################################
class Solution {
    public int[] maxSumOfThreeSubarrays(int[] nums, int k) {
        int n = nums.length, maxsum = 0;
        int[] sum = new int[n+1], posLeft = new int[n], posRight = new int[n], ans = new int[3];
        for (int i = 0; i < n; i++) sum[i+1] = sum[i]+nums[i];
        // DP for starting index of the left max sum interval
        for (int i = k, tot = sum[k]-sum[0]; i < n; i++) {
            if (sum[i+1]-sum[i+1-k] > tot) {
                posLeft[i] = i+1-k;
                tot = sum[i+1]-sum[i+1-k];
            }
            else
                posLeft[i] = posLeft[i-1];
        }
        // DP for starting index of the right max sum interval
       // caution: the condition is ">= tot" for right interval, and "> tot" for left interval
        posRight[n-k] = n-k;
        for (int i = n-k-1, tot = sum[n]-sum[n-k]; i >= 0; i--) {
            if (sum[i+k]-sum[i] >= tot) {
                posRight[i] = i;
                tot = sum[i+k]-sum[i];
            }
            else
                posRight[i] = posRight[i+1];
        }
        // test all possible middle interval
        for (int i = k; i <= n-2*k; i++) {
            int l = posLeft[i-1], r = posRight[i+k];
            int tot = (sum[i+k]-sum[i]) + (sum[l+k]-sum[l]) + (sum[r+k]-sum[r]);
            if (tot > maxsum) {
                maxsum = tot;
                ans[0] = l; ans[1] = i; ans[2] = r;
            }
        }
        return ans;
    }
}
