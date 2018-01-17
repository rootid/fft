import java.util.*;
// LLongest Non-Repeating Substring
// Given a String input, find the length of the longest substring that is made
// up of non-repeating characters. For ex, the longest substrings without
// repeated characters in “BCEFGHBCFG” are “CEFGHB” and “EFGHBC”, with length =
// 6. In the case of "FFFFF", the longest substring is "F" with a length of 1.
// Example:
// Input : aaabbbabcde
// Output: 5

public class LongestNonRepeatingSubstring {
  public static int longestNRSubstringLen(String input) {
    char[] cArr = input.toCharArray();
    int[] store = new int[256];
    // NOTE : idx start from 1 LN#20 : condition checks for non zero idx.
    int start = 1;
    int len = 0;
    int m = cArr.length;
    for (int i = 0; i < m; i++) {
      if (store[cArr[i]] != 0) {
        // sub : results how many chars are present no matter where idx start
        len = Math.max(i - start, len);
        start = store[cArr[i]] + 1;
      }
      store[cArr[i]] = i + 1;
    }
    len = Math.max(m - start + 1, len);
    return len;
  }
}
