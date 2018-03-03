//Random Pick Index
//Given an array of integers with possible duplicates, randomly output the
//index of a given target number. You can assume that the given target number
//must exist in the array.
//Note:
//The array size can be very large. Solution that uses too much extra space
//will not pass the judge.
//Example:
//int[] nums = new int[] {1,2,3,3,3};
//Solution solution = new Solution(nums);
//// pick(3) should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
//solution.pick(3);
//// pick(1) should return 0. Since in the array only nums[0] is equal to 1.
//solution.pick(1);
//
//############## binary search: O(N) memory, O(N lg N) init, O(lg N) pick. ##############
class Solution {
  typedef pair<int, int> pp; // <value, index>
  static bool comp(const pp& i, const pp& j) {
    return (i.first < j.first);
  }
  vector<pp> mNums;
  Solution(vector<int> nums) {
      for(int i = 0; i < nums.size(); i++) {
          mNums.push_back(pp({nums[i], i}));
      }
      sort(mNums.begin(), mNums.end(), comp);
  }
  int pick(int target) {
      pair<vector<pp>::iterator, vector<pp>::iterator> bounds = equal_range(mNums.begin(), mNums.end(), pp({target,0}), comp);
      int s = bounds.first - mNums.begin();
      int e = bounds.second - mNums.begin();
      int r = e - s;
      //auto N = distance(bounds.first, bounds.second);
      //if(N == 1) {
      //    return bounds.first->second;
      //}
      //return bounds.first[rand() % N].second;
      return mNums[s + (rand() % r)].second;
  }
}
//O(N) memory, O(N) init, O(1) pick.

//############## Reservoir Sampling. O(1) init, O(1) memory, but O(N) to pick. ##############
class Solution {
    vector<int> v;
    vector<int>& vect = v;
    int n;
    public:

    Solution(vector<int> nums){
        vect = nums;
        n = nums.size();
    }

    int pick(int t) {
        int count = 0, res = -1;
        for(int i = 0; i < n; i++) {
            if (vect[i] == t) {
                count += 1;
                if (rand() % count == 0) {
                    res = i;
                }
            }
        }
        return res;
    }
};
/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * int param_1 = obj.pick(target);
 */
