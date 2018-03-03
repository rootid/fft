//Reverse String II
//Given a string and an integer k, you need to reverse the first k characters
//for every 2k characters counting from the start of the string. If there are
//less than k characters left, reverse all of them. If there are less than 2k
//but greater than or equal to k characters, then reverse the first k
//characters and left the other as original.
//Example:
//Input: s = "abcdefg", k = 2
//Output: "bacdfeg"
//Restrictions:
//The string consists of lower English letters only.
//Length of the given string and k will in the range [1, 10000]
//

//######################### 2 Pointer #########################
    public String reverseStr(String s, int k) {
        int m = s.length();
        char[] charArr = s.toCharArray();
        for(int start=0; start <m; start+= 2*k) {
            for(int i=start,j= Math.min(start+k-1, m-1); i < j ;i++,j--) {
                swap(charArr,i,j);
            }
        }
        return new String(charArr);
    }

    private void swap(char[] nums, int i, int j) {
     nums[i] ^= nums[j];
     nums[j] ^= nums[i];
     nums[i] ^= nums[j];
    }


//######################### Move 2k distance and reverse K chars #########################
string reverseStr(string s, int k) {
      for (int i = 0; i < s.size(); i += 2*k) reverse(s.begin()+i, min(s.begin()+i+k, s.end()));
      return s;
}

//######################### Move 2k distance and reverse K chars #########################
/**
   * 0            k           2k          3k
   * |-----------|-----------|-----------|---
   * +--reverse--+           +--reverse--+
   */
string reverseStr(string s, int k) {
  for (int left = 0; left < s.size(); left += 2 * k) {
    for (int i = left, j = min(left + k - 1, (int)s.size() - 1); i < j; i++, j--) {
      swap(s[i], s[j]);
    }
  }
  return s;
}


//For every block of 2k characters starting with position i, we want to replace
//S[i:i+k] with it's reverse.
def reverseStr(self, s, k):
    s = list(s)
    for i in xrange(0, len(s), 2*k):
        s[i:i+k] = reversed(s[i:i+k])
    return "".join(s)
