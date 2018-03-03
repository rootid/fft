//Non-negative Integers without Consecutive Ones
//Given a positive integer n, find the number of non-negative integers less
//than or equal to n, whose binary representations do NOT contain consecutive
//ones.
//Example 1:
//Input: 5
//Output: 5
//Explanation:
//Here are the non-negative integers <= 5 with their corresponding binary
//representations:
//0 : 0
//1 : 1
//2 : 10
//3 : 11
//4 : 100
//5 : 101
//Among them, only integer 3 disobeys the rule (two consecutive ones) and the
//other 5 satisfy the rule.
//Note: 1 <= n <= 10^9
//

//######################################### T: O(32) #########################################
//num = (10110)2
//
//prefix = 1
//smallerPrefixEnding0 = 1, it consists of candidates {0}
//smallerPrefixEnding1 = 0,
//isPrefixValid = true, it consists of candidates {1}
//
//prefix = 10
//smallerPrefixEnding0 = 1, it consists of candidates {00}
//smallerPrefixEnding1 = 1, it consists of candidates {01}
//isPrefixValid = true, it consists of candidates {10}
//
//prefix = 101
//smallerPrefixEnding0 = 3, it consists of candidates {000,010,100}
//smallerPrefixEnding1 = 1, it consists of candidates {001}
//isPrefixValid = true, it consists of candidates {101}
//
//prefix = 1011
//smallerPrefixEnding0 = 5, it consists of candidates
//{0000,0100,1000,0010,1010}
//smallerPrefixEnding1 = 3, it consists of candidates {0001,0101,1001}
//isPrefixValid = false, it consists of candidates {}
//
//prefix = 10110
//smallerPrefixEnding0 = 8, it consists of candidates
//{00000,01000,10000,00100,10100,00010,01010,10010}
//smallerPrefixEnding1 = 5, it consists of candidates
//{00001,01001,10001,00101,10101}
//isPrefixValid = false, it consists of candidates {}
//
//At the end, we return 8 + 5 = 13.

public class Solution {
    public int findIntegers(int num) {
        char[] str = Integer.toBinaryString(num).toCharArray();
        int len = str.length;
        // smallerPrefixEnding0 = num of even valid integers (binary representation ending in 0) smaller than current prefix
        // smallerPrefixEnding1 = num of odd  valid integers (binary representation ending in 1) smaller than current prefix
        int smallerPrefixEnding0 = 0, smallerPrefixEnding1 = 0;
        // if current prefix is a valid integer
        boolean isPrefixValid = true;
        for (int i = 0; i < len; i++) {
            int tmp = smallerPrefixEnding0 + smallerPrefixEnding1;
            smallerPrefixEnding1 = smallerPrefixEnding0;
            smallerPrefixEnding0 = tmp;
            if (isPrefixValid) { // current prefix is still valid, keep adding new candidates
                if (str[i] == '1') {
                    smallerPrefixEnding0++; // str[0...i-1] + '0' is smaller than str[0...i], ending in 0;
                    if (i > 0 && str[i - 1] == '1') { // two consecutive '1'
                        isPrefixValid = false;
                    }
                }
            }
            //System.out.println(smallerPrefixEnding0 + " " + smallerPrefixEnding1 + " " + isPrefixValid);
        }
        return smallerPrefixEnding0 + smallerPrefixEnding1 + (isPrefixValid ? 1 : 0);
    }
//######################################### T: O(32) #########################################
//Build a tree to consider all possible number.
//1. Let 1.and 0 for each bit be tree node
//compress to 4 possible result for each bit:
//1. all bit before cur is less than num and no continues 1 and cur bit is at
//one.
//2. all bit before cur is less than num and no continues 1 and cur bit is at
//zero.
//3. cur and prev bit is equal to num.
//4. larger than num or has contiunes '1'.
//then run through the tree.
public class Solution {
    public int findIntegers(int num) {
        //one:all bit before cur is less than num and no continues 1 and cur bit is at one;
        //zero:all bit before cur is less than num and no continues 1 and cur bit is at zero;
        int one=0,zero=0,temp;
        boolean isNum=true;
        for(int i=31;i>=0;i--) {
            temp=zero;
            zero+=one;
            one=temp;
            if(isNum&&((num>>i)&1)==1){
                zero+=1;
            }
            if(((num>>i)&1)==1&&((num>>i+1)&1)==1){
                isNum=false;
            }

        }
        return one+zero+(isNum?1:0);
    }
}


//######################################### T = O (32), No-DP  #########################################
//The solution is based on 2 facts:
//1. the number of length k string without consecutive 1 is Fibonacci sequence
//f(k);
//For example, if k = 5, the range is 00000-11111. We can consider it as two
//ranges, which are 00000-01111 and 10000-10111. Any number >= 11000 is not
//allowed due to consecutive 1. The first case is actually f(4), and the second
//case is f(3), so f(5)= f(4)+f(3).
//2. Scan the number from most significant digit, i.e. left to right, in binary
//format. If we find a '1' with k digits to the right, count increases by f(k)
//because we can put a '0' at this digit and any valid length k string behind;
//After that, we continue the loop to consider the remaining cases, i.e., we
//put a '1' at this digit. If consecutive 1s are found, we exit the loop and
//return the answer. By the end of the loop, we return count+1 to include the
//number n itself.
//For example, if n is 10010110,
//we find first '1' at 7 digits to the right, we add range 00000000-01111111,
//which is f(7);
//second '1' at 4 digits to the right, add range 10000000-10001111, f(4);
//third '1' at 2 digits to the right, add range 10010000-10010011, f(2);
//fourth '1' at 1 digits to the right, add range 10010100-10010101, f(1);
//Those ranges are continuous from 00000000 to 10010101. And any greater number
//<= n will have consecutive 1.

//######################################### T = O (32), No-DP  #########################################
class Solution {
public:
    int findIntegers(int num) {
        int f[32];
        f[0] = 1;
        f[1] = 2;
        for (int i = 2; i < 32; ++i)
            f[i] = f[i-1]+f[i-2];
        int ans = 0, k = 30, pre_bit = 0;
        while (k >= 0) {
            if (num&(1<<k)) {
                ans += f[k];
                if (pre_bit) return ans;
                pre_bit = 1;
            }
            else
                pre_bit = 0;
            --k;
        }
        return ans+1;
    }
};

//######################################### DP #########################################
//http://www.geeksforgeeks.org/count-number-binary-strings-without-consecutive-1s/
public class Solution {
    public int findIntegers(int num) {
        StringBuilder sb = new StringBuilder(Integer.toBinaryString(num)).reverse();
        int n = sb.length();

        int a[] = new int[n];
        int b[] = new int[n];
        a[0] = b[0] = 1;
        for (int i = 1; i < n; i++) {
            a[i] = a[i - 1] + b[i - 1];
            b[i] = a[i - 1];
        }

        int result = a[n - 1] + b[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            if (sb.charAt(i) == '1' && sb.charAt(i + 1) == '1') break;
            if (sb.charAt(i) == '0' && sb.charAt(i + 1) == '0') result -= b[i];
        }

        return result;
    }
}

//First, I know we need to do the subtraction only for the highest effective
//bit as the problem requires less than or equal to n.
//Second. I understand that when there are two consecutive ones, other integers
//will be less than it, stop!
//Third, if we met 01, according to the dp formula, the number of qualified
//integers for first 0 should be 00 and 01, both of them are less than or equal
//to 01. The same for 10.
//Finally, for 00, the number of qualified integers for first 0 should be 00
//and 01, but 01 is greater than 00, we should subtract it.
//Why break the loop when seeing a pair of 11, and minus b[i] when seeing a
//pair of 00? I list out the n=5 sequence. X means containing 11.
//0 00000
//1 00001
//2 00010
//3 00011 X
//4 00100
//5 00101
//6 00110 X
//7 00111 X
//8 01000
//9 01001
//10 01010
//11 01100 X
//12 01100 X
//13 01101 X
//14 01110 X
//15 01111 X
//16 10000
//17 10001
//18 10010
//19 10011 X
//20 10100
//21 10101
//22 10110 X
//23 10111 X
//24 11000 X
//25 11001 X
//26 11010 X
//27 11011 X
//28 11100 X
//29 11101 X
//30 11110 X
//31 11111 X
//Now, say num = 16 (i.e. 10000)
//From the most significant digit onward, look at each pair of the digits (i.e.
//10, 00, 00, 00)
//The first pair of 00 ==> delete 10100 & 10101
//The second pair of 00 ==> delete 10010
//The third pair of 00 ==> delete 10001


//we want to exclude numbers greater than num, we check the ith and the (i+1)th
//bit and
//b[i] represents numbers with (ith) bit set without consecutive ones.
//When n = 4, result = b[3]+a[3]
//Here is one observation:
//result = b[3] + a[3]
//	     = b[3] + b[2] + a[2]
//	     = b[3] + b[2] + b[1] + a[1]
//	     = b[3] + b[2] + b[1] + b[0] + a[0]
//Thus, we can conclude that result = \sigma_{i<n} b[i] + a[0].
//The string corresponding to a[0] is 0000 when n = 4 and is the only one. For
//other strings, at least one bit is set. The number of strings with the ith
//bit set is b[i].


//######################################### DP  #########################################
//Say X is the given number, and A = a list of that number in binary. For
//example, if X = 1234 = 0b10011010010, A = [1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0].
//We will perform a 'flag-dp': let dp[i][flag] = the answer for the number
//corresponding to A[i:], where flag = 1 if we have written a lower number than
//A[i] at some point in our writing process (and can now freely write higher
//numbers), else flag = 0.
//1234 has bitlength 11. With that example, we would try to write 11 binary
//digits (without writing consecutive 1s) from left to right, such that the
//number it represents is less than or equal to 1234.
//If our flag is down (flag = 0), then we cannot write a higher number than
//A[i]. If A[i] = 1, then we can write '10' or '0'. If A[i] = 0, we can only
//write '0'. We should check as we write a zero, to lower our flag if we wrote
//a lower number. This is what dp[.][A[i]] and dp[.][A[i+1]] do.
//If our flag is up, then we can freely write '10' or '0'.

def findIntegers(self, X):
    A = map(int, bin(X)[2:])
    N = len(A)
    dp = [[0, 0] for _ in xrange(N+2)]
    dp[N] = dp[N+1] = [1, 1]

    for i in xrange(N-1, -1, -1):
        dp[i][0] = dp[i+1][A[i]] + A[i] * dp[i+2][i+1 < N and A[i+1]]
        dp[i][1] = dp[i+1][1] + dp[i+2][1]

    return dp[0][0]
