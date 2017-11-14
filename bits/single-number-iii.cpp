//Single Number III
//Given an array of numbers nums, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once.
//For example:
//Given nums = [1, 2, 1, 3, 2, 5], return [3, 5].
//Note:
//The order of the result is not important. So in the above example, [5, 3] is also correct.
//Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?

public int[] singleNumber(int[] nums) {
    int diff = 0;
    for (int num : nums) 
        diff ^= num;
    // Get its last set bit
    diff &= -diff;
    // Pass 2 :
    int[] rets = {0, 0}; // this array stores the two numbers we will return
    for (int num : nums) {
        if ((num & diff) == 0) // the bit is not set (order matters)
            rets[0] ^= num;
        else // the bit is set
            rets[1] ^= num;
    }
    return rets;
}


class Solution
{
public:
    vector<int> singleNumber(vector<int>& nums) {
        // Pass 1 : 
        // Get the XOR of the two numbers we need to find
        int diff = accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());
        // Get its last set bit
        diff &= -diff;
        // Pass 2 :
        vector<int> rets = {0, 0}; // this vector stores the two numbers we will return
        for (int num : nums) {
            if ((num & diff) == 0) {  // the bit is not set
                rets[0] ^= num;
            }
            else {
                rets[1] ^= num;
            }
        }
        return rets;
    }
};


//This problem is an extension of the other two problems Single Number and Single Number II. As we know that for an integer N:
//0 ^ N = N
//N ^ N = 0
//where ^ is XOR bit operator.
//If we call the two numbers that we need to find is A and B. We all know that if we XOR all the elements in the provided array, we will get A ^ B. This is a lot of information!
//Now, we notice that A and B must be different at some bit at position t in their binary representations. So if we divide the set of numbers into 2 set, one is the set of all the numbers that have the same bit at position t as A, the other is the set of all numbers that have the same bit at position t as B. These 2 sub-sets have a special characteristic: all numbers appear 2 times, except 1. This bring us to the Single Number problem.
