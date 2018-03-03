//Split Array Largest Sum
//Given an array which consists of non-negative integers and an integer m, you can split the array into m non-empty
//continuous subarrays. Write an algorithm to minimize the largest sum among these m subarrays.
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
//Use binary search to approach the correct answer. We have l = max number of array; r = sum of all numbers in the
//array;Every time we do mid = (l + r) / 2;
//Use greedy to narrow down left and right boundaries in binary search.
//3.1 Cut the array from left.
//3.2 Try our best to make sure that the sum of numbers between each two cuts (inclusive) is large enough but still less
//than mid.
//3.3 We'll end up with two results: either we can divide the array into more than m subarrays or we cannot.
//If we can, it means that the mid value we pick is too small because we've already tried our best to make sure each
//part holds as many non-negative numbers as we can but we still have numbers left. So, it is impossible to cut the
//array into m parts and make sure each parts is no larger than mid. We should increase m. This leads to l = mid + 1;
//If we can't, it is either we successfully divide the array into m parts and the sum of each part is less than mid, or
//we used up all numbers before we reach m. Both of them mean that we should lower mid because we need to find the
//minimum one. This leads to r = mid - 1;


//Why we will return l as our final result?
//Is it guaranteed to be a valid answer?
//First, I think it's important to know why we choose (l <= r) as the condition in our while loop. It's because we can't
//decide if the mid is our expectation. So that we need to check it when l meets r.
//Secondly, let's talk about the case when we break the loop. It will always be the situation l > r. You may want to ask
//yourself, how did we came to this case? It must be the case r - l = 1 and then valid is true or the case when l == r.
//Let's talk about the former one first.
//r - l = 1 and valid function returns true
//Think about the case when l = 5, r =6. Now, mid = 5, right? If valid returns true, r should be mid - 1, which is 4.
//If valid returns true, it means we may find a possible solution for splitting the array. Probably you may ask how do
//we know l is the right answer. It could be the case that we used up all numbers before we reach m so that valid
//returns true.
//Please keep in mind when l = 4, the valid function should return false (we find more than m parts). That's how we get
//l = 5. But with l == mid == 5, we find a valid solution. It's guaranteed to be the minimized largest sum.
//l == r
//Probably you have noticed that how we came to this situation. It must be the case r - l = 1 and valid function returns
//false. So the second situation come from the first one.
//We could still use the example when l = 5, r = 6, mid = (5 + 6) / 2 = 5. You know valid returns false , so now l = 5 +
//1 = 6, r = 6, mid = 6. Also, it's important to know 7 is a possible answer since this is how we get r = 6 (r = mid -
//1).
//If valid returns true, so now l = 6 must be the right answer since we we will find more than m parts if the largest
//sum is 5
//If valid returns false, which means we will find more than m parts if sun is 6. But we already know we could find a
//valid solution when sum is 7, and now l = mid + 1 = 6 + 1 = 7.

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
//Final result is in the interval [left, right] (where left is the maximal number in the array, right is sum of all
//numbers).
//So, what we need to do is to find out the first element in [left, right], which exactly
//we cannot split the array into m subarrays whose sum is no greater than that element. Then its previous one is the
//final result. The progress is much similar to lower_bound in C+
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

// vim: set sw=2 sts=2 tw=120 et nospell :
