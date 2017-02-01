//Longest Palindromic Substring
//Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.
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
