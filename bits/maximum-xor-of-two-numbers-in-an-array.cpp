//Maximum XOR of Two Numbers in an Array
//Given a non-empty array of numbers, a0, a1, a2, … , an-1, where 0 ≤ ai < 231.
//Find the maximum result of ai XOR aj, where 0 ≤ i, j < n.
//Could you do this in O(n) runtime?
//Example:
//Input: [3, 10, 5, 25, 2, 8]
//Output: 28
//Explanation: The maximum result is 5 ^ 25 = 28.
//
//Please note : it might contain duplicate elements

//https://discuss.leetcode.com/topic/64431/a-solution-based-on-bartoszkp-s-with-missing-test-cases

//example: Given [14, 11, 7, 2], which in binary are [1110, 1011, 0111, 0010].
//Since the MSB is 3, I'll start from i = 3 to make it simplify.
//i = 3, prefix = {1000, 0000}, max = 1000
//i = 2, prefix = {1100, 1000, 0100, 0000}, max = 1100
//i = 1, prefix = {1110, 1010, 0110, 0010}, max = 1100
//i = 0, prefix = {1110, 1011, 0111, 0010}, max = 1100
//The mask is 1000, 1100, 1110, 1111.
//
//Idea : Instead of choosing 2 from n, we verify if we can achieve maximum value 
//
//To iteratively determine what would be each bit of the final result from left to right. 
//i.e. Find the maximum XOR
//And it narrows down the candidate group iteration by iteration. e
//.g. assume input are a,b,c,d,...z, 26 integers in total. 
//In first iteration, if you found that (a, d, e, h, u) differs on the MSB(most significant bit)
//so you are sure your final result's MSB is set. 
//Now in second iteration, you try to see if among (a, d, e, h, u) there are 
//at least two numbers make the 2nd MSB differs, 
//if yes, then definitely, the 2nd MSB will be set in the final result. 
//And maybe at this point the candidate group shinks from (a,d,e,h,u) to (a, e, h). 
//Implicitly, every iteration, you are narrowing down the candidate group, 
//but you don't need to track how the group is shrinking, you only cares about the final result.

int findMaximumXOR(vector<int>& nums) {
        int max = 0, mask = 0;
        unordered_set<int> prefix;
        for (int i = 31; i >= 0; i--){
            mask |= (1 << i);
            prefix.clear();
            for (int n: nums){
                prefix.insert(mask & n);
            }
            int candidate = max | (1<<i);
            for (int p : prefix) {          
                //NOTE : This step makes sure that we pick only 2 elements
                if (prefix.find(p ^ candidate) != prefix.end()) {  //if a^b=c, then a^c=b, b^c=a.
                    max = candidate;
                    break;
                }

            // check if "a" exist in the set
            // prefix is already in the set
            // if a ^ prefix = candidate then a ^ candidate  = prefix, prefix ^ candidate = a (we use this one)
            }
        }
        return max;
}   


//######################## Wtih Trie ######################## 
//
    public int findMaximumXOR(int[] nums) {
        if(nums == null || nums.length == 0) {
            return 0;
        }
        // Init Trie.
        Object[] root = {null, null};
        for(int num: nums) {
            Object[] curNode = root;
            for(int i = 31; i >= 0; i --) {
                int curBit = (num >>> i) & 1;
                if(curNode[curBit] == null) {
                    curNode[curBit] = new Object[]{null, null};
                }
                curNode = (Object[]) curNode[curBit];
            }
        }
        int max = Integer.MIN_VALUE;
        for(int num: nums) {
            Object[] curNode = root;
            int curSum = 0;
            for(int i = 31; i >= 0; i --) {
                int curBit = (num >>> i) & 1;
                if(curNode[curBit ^ 1] != null) {
                    curSum += (1 << i);
                    curNode = (Object[]) curNode[curBit ^ 1];
                }else {
                    curNode = (Object[]) curNode[curBit];
                }
            }
            max = Math.max(curSum, max);
        }
        return max;
    }
