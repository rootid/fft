//Maximum Length of Pair Chain
//You are given n pairs of numbers. In every pair, the first number is always
//smaller than the second number.
//Now, we define a pair (c, d) can follow another pair (a, b) if and only if b
//< c. Chain of pairs can be formed in this fashion.
//Given a set of pairs, find the length longest chain which can be formed. You
//needn't use up all the given pairs. You can select pairs in any order.
//Example 1:
//Input: [[1,2], [2,3], [3,4]]
//Output: 2
//Explanation: The longest chain is [1,2] -> [3,4]
//Note:
//The number of given pairs will be in the range [1, 1000].

//############################### O(n log n) ###############################
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end(), cmp);
        int cnt = 0;
        vector<int>& pair = pairs[0];
        for (int i = 0; i < pairs.size(); i++) {
            if (i == 0 || pairs[i][0] > pair[1]) { //first element || current first eleme > prev second ele
                pair = pairs[i];
                cnt++;
            }
        }
        return cnt;
    }

private:
	//[1,2], [3,4]  = a[1] < b[1], a[0] < b[0]
    static bool cmp(vector<int>& a, vector<int>&b) {
        return a[1] < b[1] || a[1] == b[1] && a[0] < b[0];
    }
};


//############################### O(n log n) ###############################
public int findLongestChain(int[][] pairs) {
    Arrays.sort(pairs, (p1,p2)->p1[1]-p2[1] );
    int count = 0, end = Integer.MIN_VALUE;
    for (int[] pair : pairs) {
        if (pair[0] > end) {
            count++;
            end = pair[1];
        }
    }
    return count;
}


//######################################### Pythonic  #########################################
//######################################### DP + O(n log n) /#########################################
//Let's remember dp[k] = the lowest right-coordinate of the chain of length k.
//Now, let's process elements (x, y) of A in ascending order of
//right-coordinate.
//The best way to explain the following code is a worked example on
//[[1,2],[2,3],[3,4]].
//After [1, 2], dp = [-inf, 2]
//After [2, 3], dp = [-inf, 2] : we cannot extend [2, 3] onto [1, 2],
//	  and the length-1 chain ending in 2 dominates the chain [[2,3]] ending in 3.
//After [3, 4], dp = [-inf, 2, 4] : we can extend the chain ending in 2 to be a
//chain one larger ending in 4.
def findLongestChain(self, A):
    dp = [float('-inf')]
    for x, y in sorted(A, key = lambda z: z[1]):
        ix = bisect.bisect_left(dp, x)
        if ix == len(dp):
            dp.append(y)
        elif y < dp[ix]:
            dp[ix] = y
    return len(dp) - 1

//############################### DP ################################
//T : O(N^2) S : O(N)
//sort the array and apply LIS algorithm over it.
class Solution:
    def findLongestChain(self, pairs):
        """
        :type pairs: List[List[int]]
        :rtype: int
        """
        pairs.sort(key = lambda x:(x[0], x[1]))
        LIS = [1]*len(pairs)
        for i in range(1, len(pairs)):
            for j in range(i):
                LIS[i] = max(LIS[i], LIS[j]+1) if pairs[j][1] < pairs[i][0] else LIS[i]
        return LIS[-1]

