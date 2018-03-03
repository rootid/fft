//longest increasing subsequence
//Given an unsorted array of integers, find the length of longest increasing
//subsequence.
//For example,
//Given [10, 9, 2, 5, 3, 7, 101, 18],
//The longest increasing subsequence is [2, 3, 7, 101], therefore the length is
//4. Note that there may be more than one LIS combination, it is only necessary
//for you to return the length.
//Your algorithm should run in O(n2) complexity.
//Follow up: Could you improve it to O(n log n) time complexity?
//

//############################################  (n log n)############################################
//Idea : Create an array with increasing values.
//1. Use binary search to determine whether to replace(< currentVal) or append
//(> currentVal) the value
public int lengthOfLIS(int[] nums) {
    int[] dp = new int[nums.length];
    int len = 0;
    for(int x : nums) {
        int i = Arrays.binarySearch(dp, 0, len, x); //dp = [S....E]
        if(i < 0) i = -(i + 1); //element not found 10,9,2->3
        //Element can be at left or right when it is at left just replace the existing value else append the value.
        dp[i] = x; //
        //System.out.println(  "(i = " + i + " x = " + x + ")");
        if(i == len) len++;
    }
    return len;
}

//############################################  DP ############################################
//Find the max length of suffix where nextElement > currentElement
//and keep track of max Length at each position
public int lengthOfLIS(int[] nums) {
    if(nums == null || nums.length == 0) return 0;
    int m = nums.length;
    int[] maxLenArr = new int[m];
    Arrays.fill(maxLenArr, 1);
    int maxLen = 1;
    //Suffix
    for(int i=m-2;i>=0;i--)
    for(int j=i+1;j<m;j++) {
      if(nums[j] > nums[i]) maxLenArr[i] = Math.max(maxLenArr[j]+1, maxLenArr[i]);
      maxLen = Math.max(maxLen, maxLenArr[i]);
    }
    return maxLen;
}

//############################################  DP ############################################
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

//######################################### Pythonic  #########################################
//#########################################  O(N^2) #########################################
class Solution(object):
    def lengthOfLIS(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if nums == []:
            return 0
        N = len(nums)
        LIS, max_so_far = [1]*N, 0
        for i in range(N):
            for j in range(i):
                if nums[i] > nums[j]:
                    LIS[i] = max(LIS[i], LIS[j]+1)
            max_so_far = max(max_so_far, LIS[i])
        return max_so_far


//#########################################  Binary search O(n log n) #########################################
//tails[i] stores the smallest tail value for all increasing subsequences of
//length i+1
//Example: nums = [4,5,19,3].
//Increasing subsequence of length 1: [4].[5],[19],[3]. Smallest value: 3
//Increasing subsequence of length 2: [4,5], [5,19], [4,19]: Smallest value: 5
//Increasing subsequence of length 3: [4,5,19]: Smallest value: 19
//tails = [3,5,19]. Clearly tails will be sorted since tails[i+1] increases the
//subsequence by 1 by adding a number larger than tails[i].
//Imagine the next number is 9. [4,5,19,3,9]. There are now two sequences of
//length 3: [4,5,19] and [4,5,9]. tails[2] should be updated to 9. We do this
//so that later we can get say 11,12,13 and any of these can increase the
//sequence. The new tails array will now be [3,5,9]
//Imagine the next number is 28. [4,5,19,3,28]. There are now two sequences of
//length 3: [4,5,28] and [4,5,19]. tails[2] should not be updated since 19 is
//smaller than 28. But we now have a subsequence of 4 [4,5,19,28]. So we add 28
//to the tails array to indicate that subsequence of length 4 ends at 28.
from bisect import bisect_left
class Solution(object):
    def lengthOfLIS(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        tails = []
        for num in nums:
            idx = bisect_left(tails, num)
            if idx == len(tails):
                tails.append(num)
            else:
                tails[idx] = num
        return len(tails)
