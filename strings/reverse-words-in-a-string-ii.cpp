//Reverse Words in a String II
//Given an input string, reverse the string word by word. A word is defined as a sequence of non-space characters.
//The input string does not contain leading or trailing spaces and the words are always separated by a single space.
//For example,
//Given s = "the sky is blue",
//return "blue is sky the".
//Could you do it in-place without allocating extra space?

//################################################### CPP ################################################### 
void reverseWords(string &s) {
     reverse(s.begin(), s.end());
     int n = s.length(), l = 0, r = 0;
     while (r < n) {
         while (r < n && !isspace(s[r])) r++;
         reverse(s.begin() + l, s.begin() + r); 
         l = ++r;
     }
 } 

//################################################### JAVA ################################################### 
public void reverseWords(char[] s) {
    // Three step to reverse
    // 1, reverse the whole sentence
    reverse(s, 0, s.length - 1);
    // 2, reverse each word
    int start = 0;
    int end = -1;
    for (int i = 0; i < s.length; i++) {
        if (s[i] == ' ') {
            reverse(s, start, i - 1);
            start = i + 1;
        }
    }
    // 3, reverse the last word, if there is only one word this will solve the corner case
    reverse(s, start, s.length - 1);

	//################################################### To handle everything in loop ################################################### 
	//for(int i = 0, j = 0;i <= s.length;i++){ 
	//	if(i == s.length || s[i] == ' ') { 
	//		reverse(s,j,i-1); 
	//		j = i+1; 
	//	} 
	//}
}

public void reverse(char[] s, int start, int end) {
    while (start < end) {
        char temp = s[start];
        s[start] = s[end];
        s[end] = temp;
        start++;
        end--;
    }
}

//################################################### python  ################################################### 
//################################################### TC : O(n) SC : O(1) ################################################### 
class Solution(object):
    def reverseWords(self, s):
        def reverse(i, j):
            while 0 <= i < j < len(s):
                s[i], s[j] = s[j], s[i]
                i, j = i + 1, j - 1
    
        s.append(" ")
        start = 0
        for i, v in enumerate(s):
            if v == " ":
            	reverse(start, i - 1)
            	start = i + 1
        s.pop()
        reverse(0, len(s) - 1)
