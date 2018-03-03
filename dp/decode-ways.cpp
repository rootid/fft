//Decode ways
//A message containing letters from A-Z is being encoded to numbers using the
//following mapping:
//'A' -> 1
//'B' -> 2
//...
//'Z' -> 26
//Given an encoded message containing digits, determine the total number of
//ways to decode it.
//For example,
//Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).
//The number of ways decoding "12" is 2.

//######################################### Lmabda  #########################################
def numDecodings(self, s):
    return reduce(lambda(v,w,p),d:(w,(d>'0')*w+(9<int(p+d)<27)*v,d),s,(0,s>'',''))[1]*1

//######################################### Iteration #########################################
def numDecodings(self, s):
    v, w, p = 0, int(s>''), ''
    for d in s:
        v, w, p = w, (d>'0')*w + (9<int(p+d)<27)*v, d
    return w
//w tells the number of ways
//v tells the previous number of ways
//d is the current digit
//p is the previous digit

//############################### DP with Array S : O(n) ###############################
//Fibonacci series type memomization
//used a dp array of size n + 1 to save subproblem solutions.
//dp[0] means an empty string will have one way to decode,
//dp[1] means the way to decode a string of size 1.
//Then check one digit and two digit combination and save the results along the
//way.
//In the end, dp[n] will be the end result.
public class Solution {
    public int numDecodings(String s) {
        if(s == null || s.length() == 0) {
            return 0;
        }
        int n = s.length();
        int[] dp = new int[n+1];
        dp[0] = 1;
        dp[1] = s.charAt(0) != '0' ? 1 : 0;
        for(int i = 2; i <= n; i++) {
            int first = Integer.valueOf(s.substring(i-1, i));
            int second = Integer.valueOf(s.substring(i-2, i));

            if(first >= 1 && first <= 9) {
               dp[i] += dp[i-1];
            }
            if(second >= 10 && second <= 26) {
                dp[i] += dp[i-2];
            }
        }
        return dp[n];
    }
}

//############################### DP with 2 Vars S : O(1) ###############################
int numDecodings(string s) {
    if (!s.size() || s.front() == '0') return 0;
    // r2: decode ways of s[i-2] , r1: decode ways of s[i-1]
    int r1 = 1, r2 = 1;
    for (int i = 1; i < s.size(); i++) {
        // zero voids ways of the last because zero cannot be used separately
        if (s[i] == '0') r1 = 0;
        // possible two-digit letter, so new r1 is sum of both while new r2 is the old r1
        if (s[i - 1] == '1' || s[i - 1] == '2' && s[i] <= '6') {
            r1 = r2 + r1;
            r2 = r1 - r2;
        }
        // one-digit letter, no new way added
        else {
            r2 = r1;
        }
    }

    return r1;
}

//######################################### Recursion #########################################
int numDecodings(string s) {
    return s.empty() ? 0: numDecodings(0,s);
}
int numDecodings(int p, string& s) {
    int n = s.size();
    if(p == n) return 1;
    if(s[p] == '0') return 0;
    int res = numDecodings(p+1,s);
    if( p < n-1 && (s[p]=='1'|| (s[p]=='2'&& s[p+1]<'7'))) res += numDecodings(p+2,s);
    return res;
}
