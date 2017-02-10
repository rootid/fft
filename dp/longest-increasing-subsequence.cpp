//longest increasing subsequence
//Given an unsorted array of integers, find the length of longest increasing subsequence.
//For example,
//Given [10, 9, 2, 5, 3, 7, 101, 18],
//The longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4. Note that there may be more than one LIS combination, it is only necessary for you to return the length.
//Your algorithm should run in O(n2) complexity.
//Follow up: Could you improve it to O(n log n) time complexity?
//
//###################### DP
//
// There's a typical DP solution with O(N^2) Time and O(N) space 
// DP[i] means the result ends at i
// So for dp[i], dp[i] is max(dp[j]+1), for all j < i and nums[j] < nums[i]
int lengthOfLIS(vector<int>& nums) {
        const int size = nums.size();
        if (size == 0) { return 0; } 
        vector<int> dp(size, 1);
        int res = 1;
        for (int i = 1; i < size; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) {
                    dp[i] = max(dp[i], dp[j]+1);
                }
            }
            res = max (res, dp[i]);
        }
        return res;
}
//############### O(n log n) lower_bound as lvalue ############### 
int lengthOfLIS(vector<int>& nums) {
    vector<int> ans;
    for (int a : nums) {
        if (ans.size() == 0 || a > ans.back()) {
          ans.push_back(a);
        } else {
          *lower_bound(ans.begin(), ans.end(), a) = a;
        }
    }
    return ans.size();
}
//########################## same above w/o lower_bound ########################## 
int lengthOfLIS(vector<int>& nums) {
     if (nums.empty()) {
       return 0;
     }
     vector<int> ends{nums[0]};
     for (int num : nums) {
         if (num > ends.back()) {
           ends.push_back(num);
         } else {
             //current element < last element
             int l = 0, r = ends.size() - 1;
             while (l < r) {
                 int m = l + (r - l) / 2;
                 if (ends[m] < num) {
                   l = m + 1;
                 } else {
                   r = m;
                 }
             }
             ends[r] = num;
         }
     }
     return ends.size();
}
///######### change get index with lower_Bound
//
int lengthOfLIS(vector<int>& nums) {
    ///Here is the explanation of the idea https://www.cs.princeton.edu/courses/archive/spring13/cos423/lectures/LongestIncreasingSubsequence.pdf
    // Binary search for the stack where the nums[i] should be pushed, according the tops of the stacks
    // nums[i] cannot be push to any stack whose top is less than nums[i].
    // The number of stacks is the Length of LIS.
    int n = nums.size();
    if( n==0 ){
        return 0;
    }
    int end = 0;
    vector<int> tops(n, INT_MIN);
    tops[0] = nums[0];
    for(int i=1; i<n; i++){
        int idx = getIndex( tops, end, nums[i] );
        tops[idx] = nums[i];
        end = max( idx, end );
    }
    return end+1;
}
int getIndex( vector<int>& tops, int end, int x ){
    int l = 0;
    int r = end;
    while( l<=r ){
        int mid = (l+r)/2;
        if( tops[mid] == x ){
            return mid;
        }
        else if( tops[mid] > x ){
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }
    return l;
}
