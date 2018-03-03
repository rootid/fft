//Palindromic Substrings
//Given a string, your task is to count how many palindromic substrings in this
//string.
//The substrings with different start indexes or end indexes are counted as
//different substrings even they consist of same characters.
//Example 1:
//Input: "abc"
//Output: 3
//Explanation: Three palindromic strings: "a", "b", "c".
//Example 2:
//Input: "aaa"
//Output: 6
//Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".
//Note:
//1. The input string length won't exceed 1000.

//############################### Time: O(N^2) + Space: O(1) ###############################
//Idea : count the number of different palindromic substrings from their
//respective middle.
//when we consider the substring s[i-j, ..., i+j], i is the middle index of the
//substring;
//When we consider the substring s[i-1-j, ..., i+j], (i-1, i) is the middle
//index of the substring.
int countSubstrings(string s) {
    int res = 0, n = s.length();
    for(int i = 0; i < n; i++) {
        for(int j = 0; i-j >= 0 && i+j < n && s[i-j] == s[i+j]; j++) {
			res++; //substring s[i-j, ..., i+j]
		}
        for(int j = 0; i-1-j >= 0 && i+j < n && s[i-1-j] == s[i+j]; j++) {
			res++; //substring s[i-1-j, ..., i+j]
		}
    }
    return res;
}


//############################### DP + Time : O(N^2) ###############################
int countSubstrings(string s) {
     int cnt = 0;
     int n = s.size();
     vector<vector<bool>> isp(n, vector<bool>(n, false));
     for (int i = n - 1; i >= 0; i--) {
         for (int j = i; j < n; j++) {
             cnt += isp[i][j] = i == j || s[i] == s[j] && (i + 1 == j || isp[i + 1][j - 1]);
         }
     }
     return cnt;
}

//############################### O(n) ###############################
def countSubstrings(self, s):
    return sum(s[i:j] == s[i:j][::-1] for j in range(len(s) + 1) for i in range(j))


//############################### DP Space : O(n) ###############################
class Solution(object):
    def countSubstrings(self, s):
        """
        :type s: str
        :rtype: int
        """
        dp = [False] * (len(s))
        res = 0

        for i in range(len(s)):
            res += 1
            dp[i] = True
            for j in range(i):
                if s[j] == s[i] and dp[j+1]:
                    dp[j] = True
                    res+=1
                else:
                    dp[j] = False

        return res

//############################### : O(n) ###############################
//Let N = len(S).
//There are 2N-1 possible centers for the palindrome:
//we could have a center at S[0],
//   between S[0] and S[1],
//   at S[1], between S[1] and S[2],
//   at S[2], .
//To iterate over each of the 2N-1 centers, we will move the left pointer every
//2 times, and the right pointer every 2 times starting with the second (index
//1). Hence, left = center / 2, right = center / 2 + center % 2.
//From here, finding every palindrome starting with that center is
//straightforward:
//while the ends are valid and have equal characters, record the answer and
//expand.

def countSubstrings(self, S):
    N = len(S)
    ans = 0
    for center in xrange(2*N - 1):
        left = center / 2
        right = left + center % 2
        while left >= 0 and right < N and S[left] == S[right]:
            ans += 1
            left -= 1
            right += 1
    return ans


//############################### T : O(n) : Manchester's algo ###############################
//
//Each integer in manachers(S) represents the maximum half-length of a
//palindrome at some center.
//For example, if the center is at the capital letter, 'A' will be 1, 'bAb'
//will be 3, 'cbAbc' will be 5. If the center is between two letters, say at |,
//then 'a|a' will be 2, 'ba|ab' will be 4, etc. From these numbers, (v+1)/2 is
//the correct count of the number of palindromes with this center.
def countSubstrings(self, S):
    def manachers(S):
        A = '@#' + '#'.join(S) + '#$'
        Z = [0] * len(A)
        center = right = 0
        for i in xrange(1, len(A) - 1):
            if i < right:
                Z[i] = min(right - i, Z[2 * center - i])
            while A[i + Z[i] + 1] == A[i - Z[i] - 1]:
                Z[i] += 1
            if i + Z[i] > right:
                center, right = i, i + Z[i]
        return Z

    return sum((v+1)/2 for v in manachers(S))
