//Range Sum Query - Mutable
//Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.
//The update(i, val) function modifies nums by updating the element at index i to val.
//Example:
//Given nums = [1, 3, 5]
//sumRange(0, 2) -> 9
//update(1, 2)
//sumRange(0, 2) -> 8
//Note:
//The array is only modifiable by the update function.
//You may assume the number of calls to update and sumRange function is distributed evenly.

//######################################### ############################################################
class NumArray {
public:
    NumArray(vector<int> nums) {
    }
    void update(int i, int val) {
    }
    int sumRange(int i, int j) {
    }
};
/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * obj.update(i,val);
 * int param_2 = obj.sumRange(i,j);
 */


//####################################################### pytonic ##############################################
//class NumArray(object):
//    def __init__(self, nums):
//        """
//        :type nums: List[int]
//        """
//        self.update = nums.__setitem__
//        self.sumRange = lambda i, j: sum(nums[i:j+1])
//
//    def update(self, i, val):
//        """
//        :type i: int
//        :type val: int
//        :rtype: void
//        """
//    def sumRange(self, i, j):
//        """
//        :type i: int
//        :type j: int
//        :rtype: int
//        """
//# Your NumArray object will be instantiated and called as such:
//# obj = NumArray(nums)
//# obj.update(i,val)
//# param_2 = obj.sumRange(i,j)

// vim: set sw=2 sts=2 tw=120 et nospell : 
