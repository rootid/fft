//Maximum Product of Three Numbers
//Given an integer array, find three numbers whose product is maximum and output the maximum product.
//Example 1:
//Input: [1,2,3]
//Output: 6
//Example 2:
//Input: [1,2,3,4]
//Output: 24
//Note:
//The length of the given array will be in range [3,104] and all elements are in the range [-1000, 1000].
//Multiplication of any three numbers in the input won't exceed the range of 32-bit signed integer.
//

//############################ pick always 2 (- * - = +) ############################
//Either product of 3 biggest positive values will be maxProduct
//or if there are negative values then pick the 2 biggest negative values and multiply with biggest positive value
int maximumProduct(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    int temp1 = nums[n-1]*nums[n-2]*nums[n-3];
    int temp2 = nums[0]*nums[1]*nums[n-1];
    return temp1>temp2?temp1:temp2;
}

/**
 * when there are no negative, use top 3
 * when there are 1 negative, use top 3
 *   -1, 0, 1
 *   -1, 0, 1, 2
 *   -1, 0, 1, 2, 3
 * when there are 2 negative, still use top 3, but the top 2 * bottom 1 might be bigger
 *   -4, -3, 0, 1, 2, 3
 *   -4, -3, 0
 */
class Solution {
public:
    int maximumProduct(vector<int>& a) {
        sort(a.begin(), a.end());
        int n = a.size();
        int res = a[n - 3] * a[n - 2] * a[n - 1];
        if (a[0] < 0 && a[1] < 0) {
            res = max(res, a[0] * a[1] * a[n - 1]);
        }
        return res;
    }
};

//############################ pytonic ############################
//
//class Solution(object):
//    def maximumProduct(self, nums):
//        """
//        :type nums: List[int]
//        :rtype: int
//        """
//        nums.sort()
//        return max(nums[-1]*nums[-2]*nums[-3], nums[0]*nums[1]*nums[-1])

//Sort the array. Any "middle" numbers not in the first 3 or last 3 cannot be used in the final answer.
//If we are using a middle number, it must have both a left-neighbor and a right-neighbor, and switching to one of these
//neighbors will increase the product.
//def maximumProduct(self, A):
//    A.sort()
//    if len(A) > 6:
//        A = A[:3] + A[-3:]
//
//    return max(A[i] * A[j] * A[k]
//    	       for i in xrange(len(A))
//    	       for j in xrange(i+1, len(A))
//    	       for k in xrange(j+1, len(A)))
//
//
//def maximumProduct(self, A):
//    A.sort()
//    del A[3:-3]
//    return max(a * b * c for a, b, c in itertools.combinations(A, 3))

// vim: set sw=2 sts=2 tw=120 et nospell :
