//##  First Missing Positive
//### Given an unsorted integer array, find the first missing positive integer.
//For example,
//Given [1,2,0] return 3,
//and [3,4,-1,1] return 2.
//Your algorithm should run in O(n) time and uses constant space.
//Assumption : A[i] <= n
//
//Idea : put 1 to A[0]
int firstMissingPositive(vector<int>& nums) {
       int res = 0;
       int ln = nums.size();
       for(int i=0;i<ln;i++) {
           int c_idx = nums[i];
           if(c_idx < 0 || nums[i] == i+1 || c_idx > ln) {
           //if(c_idx < 0 || c_idx == i+1 || c_idx > ln) {
               continue;
           }
           swap(nums[c_idx - 1],nums[i]);
           if(nums[c_idx -1] != nums[i]) { //current # is not at correct location
               i--;  //reset i/ backtrack with i
           }
       }
       for(int i=0;i<ln;i++) {
           if(nums[i] != i+1) {
               return i+1;
           }
       }
       return ln+1;
}

int main() {
}
