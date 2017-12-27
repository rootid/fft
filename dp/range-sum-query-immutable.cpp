//Range Sum Query - Immutable
//Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.
//Example:
//Given nums = [-2, 0, 3, -5, 2, -1]
//sumRange(0, 2) -> 1
//sumRange(2, 5) -> -1
//sumRange(0, 5) -> -3
//Note:
//You may assume that the array does not change.
//There are many calls to sumRange function.

//############################### Running sum  ############################### 
class NumArray {
    int[] runningSumArr;
    
    public NumArray(int[] nums) {
        for(int i=1;i<nums.length;i++) nums[i] += nums[i - 1]; 
        runningSumArr = nums; //Just copy the referene
    }
    
    public int sumRange(int i, int j) {
        if(i == 0) return runningSumArr[j];
        return runningSumArr[j] - runningSumArr[i-1];
    }
}


//############################### Running sum  ############################### 
class NumArray {
  public:
    vector<int> accu;
    NumArray(vector<int> nums) {
       accu.push_back(0);
      for(auto num:nums) {
        accu.push_back(accu.back() + num);
      }
    }
    
    int sumRange(int i, int j) {
       return accu[j+1] - accu[i];
    }
};
/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * int param_1 = obj.sumRange(i,j);
 */
// vim: set sw=2 sts=2 tw=120 et nospell : 
