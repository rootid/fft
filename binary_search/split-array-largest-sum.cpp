//Split Array Largest Sum
//Given an array which consists of non-negative integers and an integer m, you can split the array into m non-empty continuous subarrays. Write an algorithm to minimize the largest sum among these m subarrays.
//Note:
//If n is the length of array, assume the following constraints are satisfied:
//1 ≤ n ≤ 1000
//1 ≤ m ≤ min(50, n)
//Examples:
//Input:
//nums = [7,2,5,10,8]
//m = 2
//Output:
//18
//Explanation:
//There are four ways to split nums into two subarrays.
//The best way is to split it into [7,2,5] and [10,8],
//where the largest sum among the two subarrays is only 18
//
//################################################### Binary Search ################################################### 
//The answer is between maximum value of input array numbers and sum of those numbers.
//Use binary search to approach the correct answer. We have l = max number of array; r = sum of all numbers in the array;Every time we do mid = (l + r) / 2;
//Use greedy to narrow down left and right boundaries in binary search.
//3.1 Cut the array from left.
//3.2 Try our best to make sure that the sum of numbers between each two cuts (inclusive) is large enough but still less than mid.
//3.3 We'll end up with two results: either we can divide the array into more than m subarrays or we cannot.
//If we can, it means that the mid value we pick is too small because we've already tried our best to make sure each part holds as many non-negative numbers as we can but we still have numbers left. So, it is impossible to cut the array into m parts and make sure each parts is no larger than mid. We should increase m. This leads to l = mid + 1;
//If we can't, it is either we successfully divide the array into m parts and the sum of each part is less than mid, or we used up all numbers before we reach m. Both of them mean that we should lower mid because we need to find the minimum one. This leads to r = mid - 1;
class Solution {
private :
  bool valid(long target, vector<int>& nums, int m) { 
    int count = 1;
    long total = 0;
    for(auto num : nums) {
        total += num;
        if (total > target) {
            total = num;
            count++;
            if (count > m) {
                return false;
            }
        }
    }
    return true;
  }
public:
  int splitArray(vector<int>& nums, int m) {
          int maxsum = 0; long sum = 0;
          for (auto num : nums) {
              maxsum = max(num, maxsum);
              sum += num;
          }
          if (m == 1) return (int)sum;
          //binary search
          long l = maxsum; long r = sum;
          while (l <= r) {
              long mid = (l + r)/ 2;
              if (valid(mid, nums, m)) {
                  r = mid - 1;
              } else {
                  l = mid + 1;
              }
          }
          return (int)l;
  }

};

//################################################### Binary Search ################################################### 
//Final result is in the interval [left, right] (where left is the maximal number in the array, right is sum of all numbers).
//So, what we need to do is to find out the first element in [left, right], which exactly 
//we cannot split the array into m subarrays whose sum is no greater than that element. Then its previous one is the final result. The progress is much similar to lower_bound in C+
class Solution {
public:
    using ll = long long;
    bool canSplit(vector<int>& nums, int m, ll sum) {
        int c = 1;
        ll s = 0;
        for (auto& num : nums) {
            s += num;
            if (s > sum) {
                s = num;
                ++c;
            }
        }
        return c <= m;
    }
    //get left (max element from L-R),  right (accumulated sum)
    int splitArray(vector<int>& nums, int m) {
        ll left = 0, right = 0;
        for (auto& num : nums) {
            left = max(left, (ll)num);
            right += num;
        }
        while (left <= right) {
            ll mid = left + (right-left)/2;
            if (canSplit(nums, m, mid))
                right = mid-1;
            else
                left = mid+1;
        }
        return left;
    }
};

//############################ pytonic ############################ 
//class Solution(object):
//    def splitArray(self, nums, m):
//        lo, hi = max(nums), sum(nums)
//        while lo < hi:
//            mid, s, cnt = (lo+hi)//2, 0, 1
//            for n in nums:
//                s, cnt = [(s+n,cnt),(n,cnt+1)][s+n>mid]
//            lo, hi = [(lo,mid),(mid+1,hi)][cnt>m]
//        return lo
