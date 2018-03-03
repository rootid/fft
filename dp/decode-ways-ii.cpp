//Decode Ways II
//A message containing letters from A-Z is being encoded to numbers using the
//following mapping way:
//'A' -> 1
//'B' -> 2
//...
//'Z' -> 26
//Beyond that, now the encoded string can also contain the character '*', which
//can be treated as one of the numbers from 1 to 9.
//Given the encoded message containing digits and the character '*', return the
//total number of ways to decode it.
//Also, since the answer may be very large, you should return the output mod
//10^9 + 7.
//Example 1:
//Input: "*"
//Output: 9
//Explanation: The encoded message can be decoded to the string: "A", "B", "C",
//"D", "E", "F", "G", "H", "I".
//Example 2:
//Input: "1*"
//Output: 9 + 9 = 18
//Note:
//The length of the input string will fit in range [1, 105].
//The input string will only contain the character '*' and digits '0' - '9'.


//######################################### DP #########################################
//Take "1*" as an example. It can be "11"-"19".
//You can read it into "A" and "A" to "A" and "I" or you can treat it as a two
//digit number as "K" to "S". That is the way you decode the code.
//So if you treat the current character s.charAt(i) as a single character, the
//dp result of the index i should be the number of
//choices of current character times dp[i-1].
//If you put the s.charAt(i) together with s.charAt(i-1) as a two digit number
//(if possible, something like "29" is not a possible pair), dp[i] should add the choices of the current pair times dp[i-2].
//That is basic thinking of dp for this problem. Then what should be done is to
//find what kind of pairs or single numbers are valid.
//Like a single "0" is not valid, and there is no answer for something like
//"30".
public int numDecodings(String s) {
    int len = s.length();
    int mod = 1000000007;
    long [] dp = new long[len + 1];
    dp[0] = 1;
    if (s.charAt(0) == '0') return 0;
    if (s.charAt(0) == '*') dp[1] = 9;
    else dp[1] = 1;
    for (int i = 2; i<=len; i++) { // i-1 the index of current character in s.
        if (s.charAt(i-1) == '0') {
            if (s.charAt(i-2) == '1' || s.charAt(i-2) == '2') {
                dp[i] = dp[i-2];
            } else if(s.charAt(i-2) == '*'){
                dp[i] = 2*dp[i-2];
            } else {
                return 0;
            }
        } else if(s.charAt(i-1) >= '1' && s.charAt(i-1) <= '9') {
            dp[i] = dp[i-1];
            if (s.charAt(i-2) == '1' || (s.charAt(i-2) == '2' && s.charAt(i-1) <= '6') ){
                dp[i] = (dp[i] + dp[i-2]) % mod;
            }
            else if (s.charAt(i-2) == '*') {
                if (s.charAt (i-1) <= '6') {
                    dp[i] = (dp[i] + dp[i-2] * 2) % mod;
                }
                else {
                    dp[i] = (dp[i] + dp[i-2]) % mod;
                }
            }
        } else { //s.charAt(i-1) == '*'
            dp[i] = (9*dp[i-1]) % mod;
            if ( s.charAt(i-2) == '1' ){ // 11 - 19
                dp[i] = ( dp[i] + 9 * dp[i-2] ) % mod;
            }
            else if (s.charAt(i-2) == '2') { // 21 - 26
                dp[i] = ( dp[i] + 6 * dp[i-2] ) % mod;
            }
            else if (s.charAt(i - 2) == '*') {
                dp[i] = ( dp[i] + 15 * dp[i-2] ) % mod;
            }
        }
    }
    return (int)dp[len];
}

//######################################### DP  /#########################################
//The idea for DP is simple when using two helper functions
//ways(i) -> that gives the number of ways of decoding a single character
//and
//ways(i, j) -> that gives the number of ways of decoding the two character
//string formed by i and j.
//The actual recursion then boils down to :
//f(i) = (ways(i) * f(i+1)) + (ways(i, i+1) * f(i+2))
//The solution to a string f(i), where i represents the starting index,
//f(i) = no.of ways to decode the character at i, which is ways(i) + solve for
//remainder of the string using recursion f(i+1)
//and
//no.of ways to decode the characters at i and i+1, which is ways(i, i+1) +
//solve for remainder of the string using recursion f(i+2)
//The base case is ,
//return ways(s.charAt(i)) if(i == j)
//The above recursion when implemented with a cache, is a viable DP solution,
//but it leads to stack overflow error, due to the depth of the recursion. So
//its better to convert to memoized version.
//For the memoized version, the equation changes to
//f(i) = ( f(i-1) * ways(i) ) + ( f(i-2) *ways(i-1, i) )
//This is exactly the same as the previous recursive version in reverse,
//The solution to a string f(i), where i represents the ending index of the
//string,
//f(i) = solution to the prefix of the string f(i-1) + no.of ways to decode the
//character at i, which is ways(i)
//and
//solution to the prefix f(i-2) + no.of ways to decode the characters at i - 1
//and i, which is ways(i-1, i)
public class Solution {
    public static int numDecodings(String s) {
        long[] res = new long[2];
        res[0] = ways(s.charAt(0));
        if(s.length() < 2) return (int)res[0];

        res[1] = res[0] * ways(s.charAt(1)) + ways(s.charAt(0), s.charAt(1));
        for(int j = 2; j < s.length(); j++) {
            long temp = res[1];
            res[1] = (res[1] * ways(s.charAt(j)) + res[0] * ways(s.charAt(j-1), s.charAt(j))) % 1000000007;
            res[0] = temp;
        }
        return  (int)res[1];
    }
    private static int ways(int ch) {
        if(ch == '*') return 9;
        if(ch == '0') return 0;
        return 1;
    }
    private static int ways(char ch1, char ch2) {
        String str = "" + ch1 + "" + ch2;
        if(ch1 != '*' && ch2 != '*') {
            if(Integer.parseInt(str) >= 10 && Integer.parseInt(str) <= 26)
                return 1;
        } else if(ch1 == '*' && ch2 == '*') {
            return 15;
        } else if(ch1 == '*') {
            if(Integer.parseInt(""+ch2) >= 0 && Integer.parseInt(""+ch2) <= 6)
                return 2;
            else
                return 1;
        } else {
            if(Integer.parseInt(""+ch1) == 1 ) {
                return 9;
            } else if(Integer.parseInt(""+ch1) == 2 ) {
                return 6;
            }
        }
        return 0;
    }
}


//#########################################  DP O(1) space #########################################
def numDecodings(self, S):
    MOD = 10**9 + 7
    e0, e1, e2 = 1, 0, 0
    for c in S:
        if c == '*':
            f0 = 9*e0 + 9*e1 + 6*e2
            f1 = e0
            f2 = e0
        else:
            f0 = (c > '0') * e0 + e1 + (c <= '6') * e2
            f1 = (c == '1') * e0
            f2 = (c == '2') * e0
        e0, e1, e2 = f0 % MOD, f1, f2
    return e0

//e0 = current number of ways we could decode, ending on any number;
//e1 = current number of ways we could decode, ending on an open 1;
//e2 = current number of ways we could decode, ending on an open 2;
//(Here, an "open 1" means a 1 that may later be used as the first digit of a 2 digit number, because it has not been used in a previous 2 digit number.)

//Say we see some character c. We want to calculate f0, f1, f2, the
//corresponding versions of e0, e1, e2 after parsing character c.
//1. If c == '*', then the number of ways to finish in total is: we could put *
//as a single digit number (9*e0), or we could pair * as a 2 digit number 1* in
//9*e1 ways, or we could pair * as a 2 digit number 2* in 6*e2 ways. The number
//of ways to finish with an open 1 (or 2) is just e0.
//2. If c != '*', then the number of ways to finish in total is: we could put c
//as a single digit if it is not zero ((c>'0')*e0), or we could pair c with our
//open 1, or we could pair c with our open 2 if it is 6 or less ((c<='6')*e2).
//The number of ways to finish with an open 1 (or 2) is e0 iff c == '1' (or c
//== '2').
//

//#########################################  DP O(1) space #########################################
class Solution {
public:
    int numDecodings(string s) {
        long e0 = 1, e1 = 0, e2 = 0, f0, f1, f2;
        for ( char c : s ) {
            if ( '*' == c ) {
                f0 = 9 * e0 + 9 * e1 + 6 * e2;
                f1 = f2 = e0;
            } else {
                f0 = int(c > '0') * e0 + e1 + int(c < '7') * e2;
                f1 = '1' == c ? e0 : 0;
                f2 = '2' == c ? e0 : 0;
            }
            e0 = f0 % 1000000007;
            e1 = f1;
            e2 = f2;
        }
        return int(e0);
    }
};
