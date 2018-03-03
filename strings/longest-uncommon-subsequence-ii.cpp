//Longest Uncommon Subsequence II
//Given a list of strings, you need to find the longest uncommon subsequence
//among them. The longest uncommon subsequence is defined as the longest
//subsequence of one of these strings and this subsequence should not be any
//subsequence of the other strings.
//A subsequence is a sequence that can be derived from one sequence by deleting
//some characters without changing the order of the remaining elements.
//Trivially, any string is a subsequence of itself and an empty string is a
//subsequence of any string.
//The input will be a list of strings, and the output needs to be the length of
//the longest uncommon subsequence. If the longest uncommon subsequence doesn't
//exist, return -1.
//Example 1:
//Input: "aba", "cdc", "eae"
//Output: 3
//Note:
//All the given strings' lengths will not exceed 10.
//The length of the given list will be in the range of [2, 50].

//############################## O(n^2) #########################
//LUS is one of the string
int findLUSlength(vector<string>& strs) {
  int n = strs.size();
  int maxlen = -1;
  for (int i = 0; i < n; i++) {
    bool uniq = true;
    for (int j = 0; j < n; j++) {
      //iterate over all string and check if find LCS
      if (i != j && isSubsequence(strs[i], strs[j], 0, 0)) {
        uniq = false;
        break;
      }
    }
    if (uniq) {
      maxlen = max(maxlen, (int)strs[i].length());
    }
  }
  return maxlen;
}
private:
    //s : given string
    //t : other strings
    bool isSubsequence(string s, string t, size_t si, size_t ti) {
        if (si == s.length()) {
            return true;
        }
        if (ti == t.length()) {
            return false;
        }
        return (s[si] == t[ti]) && isSubsequence(s, t, si + 1, ti + 1) || isSubsequence(s, t, si, ti + 1);
    }


//############################## sorting + O(n^2) #########################
//LUS is one of the string
class Solution {
public:
static bool cmp(string &a, string &b){
    return a.size() > b.size();
}
int findLUSlength(vector<string>& strs) {
      // Sort by length in descending order to ensure first uncommon subseq is longest
      sort(strs.begin(),strs.end(),cmp);
      // Compare each str if it's subseq of any other except itself
      int n = strs.size();
      for (int i = 0; i < n; i++) {
          int subseq = n;
          for (int j = 0; j < n; j++, subseq--) {
              if (i != j && isSubseq(strs[i], strs[j])) break;
          }
          if (subseq == 0) return strs[i].size();
      }
      return -1;
  }
private:
  // Leetcode-392 Is Subsequence: O(M+N), binary search, DP...
bool isSubseq(string s1, string s2) {
      int i = 0, m = s1.size(), n = s2.size();
      for (int j = 0; i < m && j < n; j++) {
          if (s1[i] == s2[j]) i++;
      }
      return i == m;
  }
};

//####################################  pytonic ####################################
//def subseq(w1, w2):
//    #True iff word1 is a subsequence of word2.
//    i = 0
//    for c in w2:
//        if i < len(w1) and w1[i] == c:
//            i += 1
//    return i == len(w1)
//
//A.sort(key = len, reverse = True)
//for i, word1 in enumerate(A):
//    if all(not subseq(word1, word2)
//            for j, word2 in enumerate(A) if i != j):
//        return len(word1)
//return -1
//
//
//def findLUSlength(self, strs):
//    def issubsequence(s, t):
//        t = iter(t)
//        return all(c in t for c in s)
//    for s in sorted(strs, key=len, reverse=True):
//        if sum(issubsequence(s, t) for t in strs) == 1:
//            return len(s)
//    return -1
//
