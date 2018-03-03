//Longest Palindromic Substring
//Given a string s, find the longest palindromic substring in s. You may assume
//that the maximum length of s is 1000.
//Example:
//Input: "babad"
//Output: "bab"
//Note: "aba" is also a valid answer.
//Example:
//Input: "cbbd"
//Output: "bb"
//
//Naive O(n^2)
string longestPalindrome(string s) {
	if (s.length() <= 1) {
		return s;
	}
	string longest = s.substr(0,1);
	for (int i = 0; i < s.length(); i++) {
		// get longest palindrome with center of i
		string tmp = helper(s, i, i);
		if (tmp.length() > longest.length()) {
			longest = tmp;
		}
		// get longest palindrome with center of i, i+1
		tmp = helper(s, i, i + 1);
		if (tmp.length() > longest.length()) {
			longest = tmp;
		}
	}
	return longest;
}

// Given a center, either one letter or two letter,
// Find longest palindrome
string helper(string s, int begin, int end) {
	while (begin >= 0 && end <= s.length() - 1 && s[begin] == s[end]) {
		begin--;
		end++;
	}
	int len = end - begin - 1;
	return s.substr(begin+1,len);
}

//##################### O(n^2) #####################
public String longestPalindrome(String s) {
    int curLen = 0;
    int start = -1;
    char[] array = s.toCharArray();
    for(int i = 0; i < array.length; i++) {
        if(isPalindrome(array, i - curLen - 1, i)) {
            start = i - curLen - 1;
            curLen += 2;
        } else if (isPalindrome(array, i - curLen, i)) {
            start = i - curLen;
            curLen += 1;
        }
    }
    return new String(array, start, curLen);
}
private boolean isPalindrome(char[] array, int start, int end) {
    if(start < 0) {
        return false;
    }
    while(start < end) {
        if(array[start++] != array[end--]) {
            return false;
        }
    }
    return true;
}

//######################################### O(n^2) #########################################
def longestPalindrome(self, s):
    res = ""
    for i in xrange(len(s)):
        # odd case, like "aba"
        tmp = self.helper(s, i, i)
        if len(tmp) > len(res):
            res = tmp
        # even case, like "abba"
        tmp = self.helper(s, i, i+1)
        if len(tmp) > len(res):
            res = tmp
    return res

# get the longest palindrome, l, r are the middle indexes
# from inner to outer
def helper(self, s, l, r):
    while l >= 0 and r < len(s) and s[l] == s[r]:
        l -= 1; r += 1
    return s[l+1:r]
