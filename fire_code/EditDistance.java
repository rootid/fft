import java.util.*;
// Edit distance is a classic algorithm that is used in many applications,
// including Spell Correction, DNA Sequencing and Natural Language Processing.
// Given two Strings, a and b, write a method - editDistance that returns the
// minimum number of operations needed to transform a into b. The following
// character operations are allowed :
// a) Replace character
// b) Insert character
// c) Delete character
// Examples :
// editDistance("sale", "sales") => 1
// Operations :
// 1) Insert "s"
// editDistance("sale", "sold") => 2
// Operations :
// 1) Replace "a" with "o"
// 2) Replace "e" with "d"
// editDistance("sa", "s") => 1
// Operations :
// 1) Delete "a"

public class EditDistance {
  // 1D
  // pre,       cur[i]
  // cur[i-1]   cur[i](waiting for the update)
  // cur[i] = min(pre, cur[i], cur[i - 1]) + 1
  // Iteration  -> Bottom-Up approach
  public int editDistance1D(String a, String b) {
    int m = a.length();
    int n = b.length();
    if (m == 0 || n == 0) {
      return m + n;
    }
    char[] aArr = a.toCharArray();
    char[] bArr = b.toCharArray();
    int[] cur = new int[m + 1];
    for (int i = 1; i <= m; i++) cur[i] = i;
    for (int j = 1; j <= n; j++) {
      int pre = cur[0];
      cur[0] = j;
      for (int i = 1; i <= m; i++) {
        int temp = cur[i];
        if (aArr[i - 1] == bArr[j - 1])
          cur[i] = pre;
        else
          cur[i] = Math.min(pre + 1, Math.min(cur[i] + 1, cur[i - 1] + 1));
        pre = temp;
      }
    }
    return cur[m];
  }

  // 2D
  // dp[i-1][j-1],  dp[i-1][j]
  // dp[i][j-1],    dp[i][j]
  // dp[i][j] = min(dp[i - 1][j - 1] , dp[i][j - 1] , dp[i - 1][j] ) + 1

  //Ø a b c d
  //Ø 0 1 2 3 4
  // b 1 1 1 2 3
  // b 2 2 1 2 3
  // c 3 3 2 1 2
  // 1.dp[i][0] = i;
  // 2.dp[0][j] = j;
  // 3.dp[i][j] = dp[i - 1][j - 1], if word1[i - 1] = word2[j - 1];
  // 4.dp[i][j] = min(dp[i - 1][j - 1] + 1, dp[i - 1][j] + 1, dp[i][j - 1] + 1)

  // Iteration  -> Bottom-Up approach
  public int editDistance(String a, String b) {
    int m = a.length();
    int n = b.length();
    if (m == 0 || n == 0) {
      return m + n;
    }
    char[] aArr = a.toCharArray();
    char[] bArr = b.toCharArray();
    int[][] dp = new int[m + 1][n + 1];
    for (int i = 1; i <= m; i++) dp[i][0] = i;
    for (int j = 1; j <= n; j++) dp[0][j] = j;
    for (int i = 1; i <= m; i++) {
      for (int j = 1; j <= n; j++) {
        if (aArr[i - 1] == bArr[j - 1])
          dp[i][j] = dp[i - 1][j - 1];
        else
          dp[i][j] = Math.min(dp[i - 1][j - 1] + 1,
                              Math.min(dp[i][j - 1] + 1, dp[i - 1][j] + 1));
      }
    }
    return dp[m][n];
  }

  // Recursion -> Top-Down approach
  public int editDistanceRec(String a, String b) {
    if (a.length() == 0 || b.length() == 0) {
      return a.length() + b.length();
    }
    char[] aArr = a.toCharArray();
    char[] bArr = b.toCharArray();
    return editDistanceHelper(aArr, bArr, aArr.length - 1, bArr.length - 1);
  }

  private int editDistanceHelper(char[] aArr, char[] bArr, int i, int j) {
    if (i < 0 || j < 0) {
      if (i < 0) return Math.max(j, 0);
      if (j < 0) return Math.max(i, 0);
    }
    if (aArr[i] == bArr[j]) {
      return editDistanceHelper(aArr, bArr, i - 1, j - 1);
    }
    int iCost = 1 + editDistanceHelper(aArr, bArr, i - 1, j);
    int dCost = 1 + editDistanceHelper(aArr, bArr, i, j - 1);
    int sCost = 1 + editDistanceHelper(aArr, bArr, i - 1, j - 1);
    return Math.min(sCost, Math.min(dCost, iCost));
  }
}
