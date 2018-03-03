//Encode String with Shortest Length
//Given a non-empty string, encode the string such that its encoded length is
//the shortest.
//The encoding rule is: k[encoded_string], where the encoded_string inside the
//square brackets is being repeated exactly k times.
//Note:
//k will be a positive integer and encoded string will not be empty or have
//extra space.
//You may assume that the input string contains only lowercase English letters.
//The string's length is at most 160.
//If an encoding process does not make the string shorter, then do not encode
//it. If there are several solutions, return any of them is fine.
//Example 1:
//Input: "aaa"
//Output: "aaa"
//Explanation: There is no way to encode it such that it is shorter than the
//input string, so we do not encode it.
//Example 2:
//Input: "aaaaa"
//Output: "5[a]"
//Explanation: "5[a]" is shorter than "aaaaa" by 1 character.
//Example 3:
//Input: "aaaaaaaaaa"
//Output: "10[a]"
//Explanation: "a9[a]" or "9[a]a" are also valid solutions, both of them have
//the same length = 5, which is the same as "10[a]".
//Example 4:
//Input: "aabcaabcd"
//Output: "2[aabc]d"
//Explanation: "aabc" occurs twice, so one answer can be "2[aabc]d".
//Example 5:
//Input: "abbbabbbcabbbabbbc"
//Output: "2[2[abbb]c]"
//Explanation: "abbbabbbc" occurs twice, but "abbbabbbc" can also be encoded to
//"2[abbb]c", so one answer can be "2[2[abbb]c]".
//

//######################################### TCO : O(N^3) #########################################
class Solution {
private:
	vector<vector<string>> dp;
public:

	//The collapse function is trying to find whether the string has repeated substring pattern, the example "abab" can be encoded as "2[ab]" but may be not a good example since the encoded lenght is longer, but you get the idea. If "aabbaabb" then "2[aabb]" is shorter and.
	//You can refer to that post, my understanding is, if the string has repeated substring, then the repeated substring is at least appear 2 times, like "aabbaabb" (2times), "aabbaabbaabb"(3 times), if you concatenate the string with iteself ("aabbaabbaabbaabb"), and get rid of the first character and last character("abbaabbaabbaab"), then if you can still find the original string ("aabbaabb"), that means part of the string matching is in the first part, and part is in the second part.

	string collapse(string& s, int i, int j) {
	    string temp = s.substr(i, j - i + 1);
		auto pos = (temp+temp).find(temp, 1); //if repeated string not found
		if (pos >= temp.size()) {
		    return temp;
		}
		return to_string(temp.size()/pos) + '['+ dp[i][i+pos-1]+']';
	}
	//same looping technique. solution for burst ballons
	//i is the start index(inclusiv), j is the ending index(inclusive), k is scan through from i to j,for example
	//"abab"
	//step = 1, (i, j) = (0,0), (i,j) = (1,1), (i.j) = (2,2), (i, j) = (3,3). So it calculates all substrings with length=1
	//step = 2, (i,j) = (0, 1), (i,j) = (1,2), (i,j) = (2,3). So it calculates all substring with length = 2
	//step = 3, (i, j) = (0,2), (i,j) = (1,3)
	//step = 4, (i, j) = (0,3), so this is the final result
	//The reason to have 3 loops is that each substring's optimal answer depends on right half and left half. That is the functionality of k, to find each break point within i, j.

	string encode(string s) {
		int n = s.size();
		//stores all strings as [start_idx][length]
		dp = vector<vector<string>>(n, vector<string>(n, ""));
		//counter to count # of repeated chars
		for (int step = 1; step <= n; step++) {
			for (int i = 0; i + step - 1 < n; i++) {
				int j = i + step - 1;
				dp[i][j] = s.substr(i, step);
				for (int k = i; k < j; k++) {
					auto left = dp[i][k];
					auto right = dp[k + 1][j];
					if (left.size() + right.size() < dp[i][j].size()) {
						dp[i][j] = left + right;
					}
				}
				string replace = collapse(s, i, j);
				if (replace.size() < dp[i][j].size()) {
					dp[i][j] = replace;
				}
			}
		}
		return dp[0][n - 1];
	}
};

public String encode(String s) {
    String[][] dp = new String[s.length()][s.length()];

    for (int len = 1; len <= s.length(); len++) {
        for (int i = 0; i + len - 1 < s.length(); i++) {
            int j = i + len - 1;
            dp[i][j] = s.substring(i, i + len);

            // try left and right
            for (int k = i; k < j; k++) {
                String l = dp[i][k], r = dp[k + 1][j];
                dp[i][j] = isLeftPlusRightShorter(l, r, dp[i][j]) ? l + r : dp[i][j];
            }

            // try collapsing
            String collapsed = collapse(dp, s.substring(i, i + len), i);
            dp[i][j] = isCollapsedShorter(collapsed, dp[i][j]) ? collapsed : dp[i][j];
        }
    }

    return dp[0][s.length() - 1];
}

private boolean isLeftPlusRightShorter(String left, String right, String curr) {
    return left.length() + right.length() < curr.length();
}

private boolean isCollapsedShorter(String collapsed, String curr) {
    return collapsed.length() < curr.length();
}

private String collapse(String[][] dp, String s, int i) {
    int pos = (s + s).indexOf(s, 1);
    if (pos >= s.length()) return s;
    return (s.length() / pos) + "[" + dp[i][i + pos - 1] + "]";
}

//Repeated string
//Basic idea:
//First char of input string is first char of repeated substring
//Last char of input string is last char of repeated substring
//Let S1 = S + S (where S in input string)
//Remove 1 and last char of S1. Let this be S2
//If S exists in S2 then return true else false
//Let i be index in S2 where S starts then repeated substring length i + 1 and
//repeated substring S[0: i+1]
//def repeatedSubstringPattern(self, str):
//
//        """
//        :type str: str
//        :rtype: bool
//        """
//        if not str:
//            return False
//
//        ss = (str + str)[1:-1]
//        return ss.find(str) != -1

//Either don't encode s at all, or encode it as one part k[...] or encode it as
//multiple parts (in which case we can somewhere split it into two
//subproblems). Whatever is shortest. Uses @rsrs3's nice trick of searching s
//in s + s.
//def encode(self, s, memo={}):
//    if s not in memo:
//        n = len(s)
//        i = (s + s).find(s, 1)
//        one = '%d[%s]' % (n / i, self.encode(s[:i])) if i < n else s
//        multi = [self.encode(s[:i]) + self.encode(s[i:]) for i in xrange(1, n)]
//        memo[s] = min([s, one] + multi, key=len)
//    return memo[s]
//
//(L = (s + s).find(s, 1)) < s.size() is equivalent to s has the shortest repetitive substring of length L. (let N = s.size())
//Basically, if you consider function f(i) = s[i%N] from int to char which
//obviously has a positive period N, then the key is that L = (s + s).find(s,
//1)) actually indicates L is the minimum positive period of f. Note that we
//always have i = L*(i/L) + i%L for any i, so
//f(i) = f(i%L) since L*(i/L) is an integral multiple of L.
//Also, N = L*(N/L)+N%L, so f(i) = f(i+N) = f(i+N%L), which means N%L (<L) is
//also a period of f. But L is the minimum by string::find(s,1) definition
//(i.e., first occurrence of match after 0), so we must have
//N%L = 0.
//Combining equations 1 and 2 proves that s.subtr(0,L) must be the shortest
//repetitive substring of s.
////
//Even though many of us use the following smart condition in code to check for
//substring repetition, I didn't see a rigorous proof. So here is one.
//Why condition (s+s).find(s,1) < s.size() is equivalent to substring
//repetition?
//Proof: Let N = s.size() and L := (s+s).find(s,1), actually we can prove that
//the following 2 statements are equivalent:
//0 < L < N;
//N%L == 0 and s[i] == s[i%L] is true for any i in [0, N). (which means
//s.substr(0,L) is the repetitive substring)
//Consider function char f(int i) { return s[i%N]; }, obviously it has a period
//N.
//"1 => 2": From condition 1, we have for any i in [0,N)
//s[i] == (s+s)[i+L] == s[(i+L)%N],
//which means L is also a positive period of function f. Note that N ==
//L*(N/L)+N%L, so we have
//f(i) == f(i+N) == f(i+L*(N/L)+N%L) == f(i+N%L),
//which means N%L is also a period of f. Note that N%L < L but L :=
//(s+s).find(s,1) is the minimum positive period of function f, so we must have
//N%L == 0. Note that i == L*(i/L)+i%L, so we have
//s[i] == f(i) == f(L*(i/L)+i%L) == f(i%L) == s[i%L],
//so condition 2 is obtained.
//"2=>1": If condition 2 holds, for any i in [0,N), note that N%L == 0, we have
//(s+s)[i+L] == s[(i+L)%N] == s[((i+L)%N)%L] == s[(i+L)%L] == s[i],
//which means (s+s).substr(L,N) == s, so condition 1 is obtained.
