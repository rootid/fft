import java.util.*;
// Given a String, write a method - longestPalSubstr that finds and returns the
// longest substring which is also a Palindrome. Try and accomplish this in at
// most O(n2) runtime.
// Examples :
//"bccb" => "bccb"
//"bccd" => "cc"
//"bccc" => "ccc"
//

public class LongestPalindromicSubstring {
  public String longestPalSubstr(String str) {
    if (str == null || str.length() <= 1) return str;
    int len = str.length();
    int startIdx = -1;
    int maxLen = 0;
    char[] arr = str.toCharArray();
    // abba, aba
    for (int i = 0; i < len; i++) {
      if (isPalindrome(arr, i - maxLen - 1, i)) {
        startIdx = i - maxLen - 1;
        maxLen += 2;
      } else if (isPalindrome(arr, i - maxLen, i)) {
        startIdx = i - maxLen;
        maxLen += 1;
      }
    }
    return str.substring(
        startIdx, startIdx + maxLen);  // expects endIdx as a last paramenter
    // or return new String(array, start, curLen); // expects length as a last
    // paramenter
  }

  boolean isPalindrome(char[] charArr, int start, int end) {
    if (start < 0) return false;
    while (start < end) {
      if (charArr[start++] != charArr[end--]) return false;
    }
    return true;
  }
}
