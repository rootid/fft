//Binary Number with Alternating Bits/
//Given a positive integer, check whether it has alternating bits: namely, if two adjacent bits will always have different values.
//Example 1:
//Input: 5
//Output: True
//Explanation:
//The binary representation of 5 is: 101
//Example 2:
//Input: 7
//Output: False
//Explanation:
//The binary representation of 7 is: 111.
//Example 3:
//Input: 11
//Output: False
//Explanation:
//The binary representation of 11 is: 1011.
//Example 4:
//Input: 10
//Output: True
//Explanation:
//The binary representation of 10 is: 1010.
//

//############################### only get last bit ###############################
class Solution {
    public boolean hasAlternatingBits(int n) { //pass by value so no need to create copy
        int lastBit = n & 1;
        while( (n&1) == lastBit ) {
            lastBit = 1 - lastBit;
            n >>= 1;
        }
        return n == 0;
    }
}

//############################### python ###############################
class Solution:
    def hasAlternatingBits(self, n):
        if not n:
            return False
        num = n ^ (n >> 1)
        return not (num & (num + 1))
