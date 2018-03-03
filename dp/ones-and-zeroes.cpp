//Ones and Zeroes
//In the computer world, use restricted resource you have to generate maximum
//benefit is what we always want to pursue.
//For now, suppose you are a dominator of m 0s and n 1s respectively. On the
//other hand, there is an array with strings consisting of only 0s and 1s.
//Now your task is to find the maximum number of strings that you can form with
//given m 0s and n 1s. Each 0 and 1 can be used at most once.
//Note:
//The given numbers of 0s and 1s will both not exceed 100
//The size of given string array won't exceed 600.
//Example 1:
//Input: Array = {"10", "0001", "111001", "1", "0"}, m = 5, n = 3
//Output: 4
//Explanation: This are totally 4 strings can be formed by the using of 5 0s
//and 3 1s, which are “10,”0001”,”1”,”0”
//Example 2:
//Input: Array = {"10", "0", "1"}, m = 1, n = 1
//Output: 2
//Explanation: You could form "10", but then you'd have nothing left. Better
//form "0" and "1".
//

//#########################################  Bottom-up  #########################################
int findMaxForm(vector<string>& strs, int m, int n) {
  vector<vector<int>> memo(m+1, vector<int>(n+1, 0));
  int numZeroes, numOnes;
  for (auto &s : strs) {
    numZeroes = numOnes = 0;
    // count number of zeroes and ones in current string
    for (auto c : s) {
      if (c == '0') {
        numZeroes++;
      } else if (c == '1') {
        numOnes++;
      }
    }
    // memo[i][j] = the max number of strings that can be formed with i 0's and j 1's
    // from the first few strings up to the current string s
    // Catch: have to go from bottom right to top left
    // Why? If a cell in the memo is updated(because s is selected),
    // we should be adding 1 to memo[i][j] from the previous iteration (when we were not considering s)
    // If we go from top left to bottom right, we would be using results from this iteration => overcounting
    for (int i = m; i >= numZeroes; i--) {
    for (int j = n; j >= numOnes; j--) {
          memo[i][j] = max(memo[i][j], memo[i - numZeroes][j - numOnes] + 1);
    }
    }
  }
  return memo[m][n];
}
//#########################################  Bottom-up  #########################################
int findMaxForm(vector<string>& strs, int m, int n) {
    vector<vector<int>> dp(m+1,vector<int>(n+1,0));
    for (auto &s: strs) {
        int ones = count(s.begin(), s.end(), '1');
        int zeros= s.size()-ones;
        for (int i=m; i>=zeros; i--)
            for (int j=n; j>=ones; j--)
                dp[i][j] = max(dp[i][j], dp[i-zeros][j-ones]+1);
    }
    return dp[m][n];
}

//###################################### BFS  ######################################
int findMaxForm(vector<string>& strs, int m, int n) {
      uint max = 0;
      unordered_map<short, uint> cand, pool, tmp; // Put {zeros, ones} into one short
      pool.reserve(m * n);
      tmp.reserve(m * n);
      for (auto& s : strs) { // Combine similar candidates since only the counts of 0/1 matter
          short zero = 0, one = 0;
          for (auto& c : s) {
              if (c == '0') zero++;
              else one++;
          }
          if (zero <= m && one <= n) cand[zero << 8 | one]++;
      }
      pool.emplace(m << 8 | n, 0);
      for (auto& c : cand) { // BFS, try to add each candidate into already built results
          short zero = c.first >> 8, one = c.first & 0xFF;
          tmp = pool;
          for (auto& p : pool) {
              short zero_left = p.first >> 8, one_left = p.first & 0xFF;
              for (uint i = 1, ii = c.second; i <= ii; i++) { // Each candidate represents several similar strings
                  if ((zero_left -= zero) >= 0 && (one_left -= one) >= 0) {
                      auto it = tmp.find(zero_left << 8 | one_left);
                      if (it == tmp.end()) tmp[zero_left << 8 | one_left] = p.second + i;
                      else if (p.second + i > it->second) it->second = p.second + i;
                  } else break;
              }
          }
          pool.clear();
          pool.swap(tmp);
      }
      for (auto& p : pool) {
          if (p.second > max) max = p.second;
      }
      return max;
  }
//###################################### pytonic ######################################
// #### top-down
//dp(k, x, y) is the maximum strs we can include when we have x zeros, y ones
//and only the first k strs are considered.
//dp(len(strs), M, N) is the answer we are looking for
//dp(k, x, y) = max(dp(k-1, x-z, y-o) + 1, dp(k-1, x, y))   (z is zeroes in
//strs[k], o is ones in strs[k])

//With bottom up, we can use something called "rolling array" to optimize space
//complexity from O(KMN) to O(MN)
//class Solution(object):
//    def findMaxForm(self, strs, m, n):
//        dp = [[0] * (n+1) for _ in range(m+1)]
//        def count(s):
//            return sum(1 for c in s if c == '0'), sum(1 for c in s if c == '1')
//        for z, o in [count(s) for s in strs]:
//            for x in range(m, -1, -1):
//                for y in range(n, -1, -1):
//                    if x >= z and y >= o:
//                        dp[x][y] = max(1 + dp[x-z][y-o], dp[x][y])
//
//        return dp[m][n]
