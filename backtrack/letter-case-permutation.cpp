//Letter Case Permutation
//Given a string S, we can transform every letter individually to be lowercase
//or uppercase to create another string.  Return a list of all possible strings
//we could create.
//Examples:
//Input: S = "a1b2"
//Output: ["a1b2", "a1B2", "A1b2", "A1B2"]
//Input: S = "3z4"
//Output: ["3z4", "3Z4"]
//Input: S = "12345"
//Output: ["12345"]
//Note:
//    S will be a string with length at most 12.
//    S will consist only of letters or digits.

//#########################################  DFS + Avoid duplicates #########################################
//It is just simply two states and if you add at the end of recursion…
//definitely no duplication
class Solution {
    public List<String> letterCasePermutation(String S) {
        List<String> ans=new ArrayList<>();
        compute(ans,S.toCharArray(),0);
        return ans;
    }

    public void compute(List<String> ans, char[] chars, int index)
    {
        if(index==chars.length)
            ans.add(new String(chars));
        else
        {
            if(Character.isLetter(chars[index]))
            {
                chars[index]=Character.toLowerCase(chars[index]);
                compute(ans,chars,index+1);
                chars[index]=Character.toUpperCase(chars[index]);
            }
            compute(ans,chars,index+1);
        }
    }
}

//#########################################  #########################################
//cnstrnt - >
//100x - lowercase? numbers.
//How to Remove duplicates? use hashset
class Solution {
    //cnstrnt - >
    //100x - lowercase? numbers.
    List<String> result = new ArrayList<>();

    public List<String> letterCasePermutation(String S) {
        char[] stpRslt = new char[S.length()];
        for(int i=0;i<S.length();i++) stpRslt[i] = S.charAt(i);

        letterCasePermutationHelper(S, 0, stpRslt);
        return result;
    }

    private void letterCasePermutationHelper(String s, int k ,char[] stpRslt) {
        //System.out.println( "k = " + k + " s " + s.length());
        if( k+1 == s.length())
            result.add(new String(stpRslt));

        for(int i=k;i<s.length();i++) {
            stpRslt[i] = s.charAt(i);
            if(Character.isLetter(stpRslt[i])) {
                letterCasePermutationHelper(s,i+1,stpRslt);
                stpRslt[i] =  Character.toUpperCase(stpRslt[i]);
                letterCasePermutationHelper(s,i+1,stpRslt);
                stpRslt[i] = Character.toLowerCase(stpRslt[i]);
            }
        }

    }
}

//#########################################  #########################################
 public List<String> letterCasePermutation(String S) {
        List<String> ans = new ArrayList<>(Arrays.asList(S));
        for (int i = 0; i < S.length(); ++i) { // Traverse string S.
            for (int j = 0, sz = ans.size(); S.charAt(i) > '9' && j < sz; ++j) { // S.charAt(i) > '9': letter, not digit.
                char[] ch = ans.get(j).toCharArray(); // transform to char[] the string @ j of ans.
                ch[i] ^= (1 << 5); // toggle case of charAt(i).
                ans.add(String.valueOf(ch)); // append to the end of ans.
            }
        }
        return ans;
    }

//#########################################  #########################################
class Solution {
  List<String> res = new ArrayList<>();

  public List<String> letterCasePermutation(String S) {
    dfs("", S, 0);
    return res;
  }

  public void dfs(String temp, String S, int k) {

      if(k == S.length()) {
        res.add(temp);
        return;
      }

      char c = S.charAt(i);
      if (Character.isLetter(c)) {
        dfs(temp + Character.toUpperCase(c), S, k + 1);
        dfs(temp + Character.toLowerCase(c), S, k + 1);
      } else {
        dfs(temp + c, S, k + 1);
      }
  }
}

//#########################################  #########################################
class Solution {
    public List<String> letterCasePermutation(String S) {
        List<StringBuilder> ans = new ArrayList();
        ans.add(new StringBuilder());

        for (char c: S.toCharArray()) {
            int n = ans.size();
            if (Character.isLetter(c)) {
                for (int i = 0; i < n; ++i) {
                    ans.add(new StringBuilder(ans.get(i)));
                    ans.get(i).append(Character.toLowerCase(c));
                    ans.get(n+i).append(Character.toUpperCase(c));
                }
            } else {
                for (int i = 0; i < n; ++i)
                    ans.get(i).append(c);
            }
        }

        List<String> finalans = new ArrayList();
        for (StringBuilder sb: ans)
            finalans.add(sb.toString());
        return finalans;
    }
}


//#########################################  #########################################
def letterCasePermutation(self, S):
        """
        :type S: str
        :rtype: List[str]
        """
        ret = set()
        l = len(S)
        def dfs(current_idx, temp):
            ret.add(temp)
            for i in range(current_idx, l):
                if S[i].isalpha():
                    dfs(i + 1, temp[:i] + S[i].lower() + temp[i + 1:])
                    dfs(i + 1, temp[:i] + S[i].upper() + temp[i + 1:])
        dfs(0, S)
        return list(ret)



//#########################################  #########################################
//Time Complexity: O(2^{N} * N), where N is the length of S. This reflects the
//cost of writing the answer.
//Space Complexity:O(2^N * N).
//
class Solution {
    public List<String> letterCasePermutation(String S) {
        List<StringBuilder> ans = new ArrayList();
        ans.add(new StringBuilder());

        for (char c: S.toCharArray()) {
            int n = ans.size();
            if (Character.isLetter(c)) {
                for (int i = 0; i < n; ++i) {
                    ans.add(new StringBuilder(ans.get(i)));
                    ans.get(i).append(Character.toLowerCase(c));
                    ans.get(n+i).append(Character.toUpperCase(c));
                }
            } else {
                for (int i = 0; i < n; ++i)
                    ans.get(i).append(c);
            }
        }

        List<String> finalans = new ArrayList();
        for (StringBuilder sb: ans)
            finalans.add(sb.toString());
        return finalans;
    }
}

