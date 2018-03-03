//Reverse Words in a String II
//Given an input string, reverse the string word by word. A word is defined as
//a sequence of non-space characters.
//The input string does not contain leading or trailing spaces and the words
//are always separated by a single space.
//For example,
//Given s = "the sky is blue",
//return "blue is sky the".
//Could you do it in-place without allocating extra space?

//################################################### JAVA ###################################################
private void swapBetween(int start,int end, char[] str) {
  while(start < end) {
        char tmp = str[start];
        str[start] = str[end];
        str[end] = tmp;
        start++; end--;
    }
}

public void reverseWords(char[] str) {
    int len = str.length;
    int start = 0;
    int end = len -1;
    swapBetween(start, end, str);
    start = 0;
    for(int i=0;i<len;i++) {
        if(str[i] == ' ') {
            end = i-1;
            swapBetween(start, end, str);
            start = i+1;
        }
    }
    swapBetween(start, len-1, str);
}
//################################################### To handle everything in loop ###################################################
//for(int i = 0, j = 0;i <= s.length;i++){
//    if(i == s.length || s[i] == ' ') {
//        reverse(s,j,i-1);
//        j = i+1;
//    }
//}
}


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
