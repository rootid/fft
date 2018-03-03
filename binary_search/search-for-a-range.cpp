//Search for a Range
//Given an array of integers sorted in ascending order, find the starting and
//ending position of a given target value.
//Your algorithm's runtime complexity must be in the order of O(log n).
//If the target is not found in the array, return [-1, -1].
//For example,
//Given [5, 7, 7, 8, 8, 10] and target value 8,
//return [3, 4].
//
//###################################### In-built binary search with (2 binary searches) ######################################
vector<int> searchRange(vector<int>& nums, int target) {
    auto low_iter = lower_bound(nums.begin(),nums.end(),target);
    auto high_iter = upper_bound(nums.begin(),nums.end(),target);
    int lo = low_iter - nums.begin();
    int hi = high_iter - nums.begin() - 1;
    if (lo == nums.size() || nums[lo] != target) {
      return {-1, -1};
    }
    return {lo, hi};
}

//###################################### binary search ######################################
vector<int> searchRange(vector<int>& nums, int target) {
  int n = nums.size();
  return search(nums, 0, n - 1, target);
}

vector<int> search(vector<int>& nums, int l, int r, int target) {
    if(nums.empty()) {
        return {-1,-1};
    }
    if (nums[l] == target && nums[r] == target) {
      return {l, r};
    }
    if (nums[l] <= target && target <= nums[r]) {
        int mid = l + ((r - l) >> 1);
        //int mid = l + ((r - l) /2);
        vector<int> left = search(nums, l, mid, target);
        vector<int> right = search(nums, mid  +1, r, target);
        if (left[0] == -1) return right;
        if (right[0] == -1) return left;
        return {left[0], right[1]};
    }
    return {-1, -1};
}

//Binary search with [ A-B] <left>  [ C-D ] <right>
//class Solution:
//# @param A, a list of integers
//# @param target, an integer to be searched
//# @return a list of length 2, [index1, index2]
//def searchRange(self, A, target):
//    if not A:
//        return [-1, -1]
//    return self.search(A, 0, len(A)-1, target)
//
//def search(self, A, start, end, target):
//    if A[start]>target or A[end]<target:
//        return [-1, -1]
//    if A[start] == target and A[end] == target:
//        return [start, end]
//    m = start+(end-start)/2
//    l = self.search(A, start, m, target)
//    r = self.search(A, m+1, end, target)
//    if l == [-1, -1] and r == [-1, -1]:
//        return [-1, -1]
//    if l == [-1, -1]:
//        return r
//    if r == [-1, -1]:
//        return l
//    return [l[0], r[1]]
