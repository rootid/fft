import java.util.*;
// Given a String that represents the digits pressed on a classic cell phone
// keypad - return all possible letter combinations that the numbers could
// represent in an ArrayList of Strings. Check out the keypad and mapping below
// for reference.
// Note:
// a) You can assume that the input String contains only numbers between 2 and
// 9.
// b) The order of the combinations in the output does not matter.
// Mapping:
// 2 -> "abc"
// 3 -> "def"
// 4 -> "ghi"
// 5 -> "jkl"
// 6 -> "mno"
// 7 -> "pqrs"
// 8 -> "tuv"
// 9 -> "wxyz"
// Example:
// Input  : "34"
// Output : [dg, dh, di, eg, eh, ei, fg, fh, fi]
public class Problem1800 {
  // Recursive solution
  public static ArrayList<String> getStringsFromNums(String digits) {
    // Phone # idx starts from 2 while mapper idx starts from 0
    String[] mapper = {"abc", "def",  "ghi", "jkl",
                       "mno", "pqrs", "tuv", "wxyz"};
    char[] input = digits.toCharArray();
    ArrayList<String> result = new ArrayList<>();
    StringBuilder sb = new StringBuilder();
    getStringsFromNumsHelper(mapper, input, 0, 0, sb, result);
    return result;
  }

  private static void getStringsFromNumsHelper(String[] mapper, char[] input,
                                               int j, int k,
                                               StringBuilder localSb,
                                               ArrayList<String> result) {
    int m = input.length;
    if (k > m) return;
    if (m == localSb.length()) {
      result.add(localSb.toString());
      return;
    }
    // mapper idx always > 2
    int cIdx = input[k] - '0' - 2;
    for (int vidx = 0; vidx < mapper[cIdx].length(); vidx++) {
      localSb.append(mapper[cIdx].charAt(vidx));
      getStringsFromNumsHelper(mapper, input, vidx, k + 1, localSb, result);
      localSb.setLength(localSb.length() - 1);
    }
  }
}
