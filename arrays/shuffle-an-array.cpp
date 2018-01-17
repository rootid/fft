//Shuffle an Array
//Shuffle a set of numbers without duplicates.
//Example:
//// Init an array with set 1, 2, and 3.
//int[] nums = {1,2,3};
//Solution solution = new Solution(nums);
//// Shuffle the array [1,2,3] and return its result. Any permutation of [1,2,3] must equally likely to be returned.
//solution.shuffle();
//// Resets the array back to its original configuration [1,2,3].
//solution.reset();
//// Returns the random shuffling of array [1,2,3].
//solution.shuffle();


class Solution {
    private:
    vector<int> vi, vo;
    public:
    Solution(vector<int> nums) {
        vi = vo = nums;
    }

    vector<int> reset() {
        return vi = vo;
    }

    vector<int> shuffle() {
        int i = 0, j = 0;
        for (i = vi.size() - 1; i > 0; --i) {
            j = rand() % (i + 1);
            swap(vi[i], vi[j]);
        }
        return vi;
    }
};


class Solution {
public:
    Solution(vector<int> nums) {
      this->vi = nums;
    }
    
    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        return this->vi;
    }
    /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
        vector<int> res(vi);
        for(int i=0;i<res.size();i++) {
           //int pos = rand()%(res.size()-i);
           //swap(res[i],res[i+pos]);
            int pos = rand()%(res.size());
            swap(res[i],res[pos]);
        }
        return res;
    }
private :
    vector<int> vi;
    
};
/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * vector<int> param_1 = obj.reset();
 * vector<int> param_2 = obj.shuffle();
 */
