//Reverse Words in a String III
//Given a string, you need to reverse the order of characters in each word within a sentence while still preserving
//whitespace and initial word order.
//Example 1:
//Input: "Let's take LeetCode contest"
//Output: "s'teL ekat edoCteeL tsetnoc"
//Note: In the string, each word is separated by single space and there will not be any extra space in the string.

//######################################## traversal O(n) ########################################
private void swapBetween(int start,int end, char[] str) {
      while(start < end) {
        char tmp = str[start];
        str[start] = str[end];
        str[end] = tmp;
        start++; end--;
    }
}

public String reverseWords(String s1) {
  char[] s = s1.toCharArray();
  int len = s.length;

  for(int i=0,j=0; i<=s.length;i++) {
        if(i == len || s[i] == ' ') {
          swapBetween(j,i-1,s);
          j = i+1;
      }
    }
    return new String(s);
}

//######################################## istream + copy semantics ########################################
string reverseWords(string s) {
    istringstream iss{s};
    auto iter = s.begin(); //Let's
    for (string word; iss >> word;) {
            iter = copy(word.rbegin(), word.rend(), iter); //Let's
            if (iter != s.end()) {
                    ++iter; //increment by space
     }
    }
    return s;
}

//######################################## simple traversal ########################################
string reverseWords(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != ' ') {   // when i is a non-space
            int j = i;
            for (; j < s.length() && s[j] != ' '; j++) { } // move j to the next space
            reverse(s.begin() + i, s.begin() + j);
            i = j - 1;
        }
    }
    return s;
}
//def reverseWords(self, s):
//    return ' '.join(s.split()[::-1])[::-1]
//
//def reverseWords(self, s):
//    return ' '.join(x[::-1] for x in s.split())
//
//>>> from timeit import timeit
//>>> setup = 's = "Let\'s take LeetCode contest"'
//>>> statements = ("' '.join(s.split()[::-1])[::-1]",
//              "' '.join(x[::-1] for x in s.split())",
//              "' '.join([x[::-1] for x in s.split()])")
//>>> for stmt in statements:
//        print ' '.join('%.2f' % timeit(stmt, setup) for _ in range(5)), 'seconds for:', stmt
//0.79 0.78 0.80 0.82 0.79 seconds for: ' '.join(s.split()[::-1])[::-1]
//2.10 2.14 2.08 2.06 2.13 seconds for: ' '.join(x[::-1] for x in s.split())
//1.27 1.26 1.28 1.28 1.26 seconds for: ' '.join([x[::-1] for x in s.split()])
//double reversal with advantage
//>>> setup = 's = "Let\'s take LeetCode contest" * 1000'
//>>> for stmt in statements:
//        print ' '.join('%.2f' % timeit(stmt, setup, number=1000) for _ in range(5)), 'seconds for:', stmt
//
//0.16 0.14 0.13 0.14 0.14 seconds for: ' '.join(s.split()[::-1])[::-1]
//0.69 0.71 0.69 0.70 0.70 seconds for: ' '.join(x[::-1] for x in s.split())
//0.63 0.68 0.63 0.64 0.64 seconds for: ' '.join([x[::-1] for x in s.split()])

// vim: set sw=2 sts=2 tw=120 et nospell :
