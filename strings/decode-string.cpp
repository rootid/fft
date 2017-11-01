//Given an encoded string, return it's decoded string.
//The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.
//You may assume that the input string is always valid; No extra white spaces, square brackets are well-formed, etc.
//Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there won't be input like 3a or 2[4].
//Examples:
//s = "3[a]2[bc]", return "aaabcbc".
//s = "3[a2[c]]", return "accaccacc".
//s = "2[abc]3[cd]ef", return "abcabccdcdcdef".
//
//

//######################################### Recursive ######################################### 
class Solution {
    int k = 0;
    private String decodeStringHelper(String s) {
        int n = s.length();
        String result = "";
        int freq = 0;
        while(k < n) {
            if(Character.isDigit(s.charAt(k))) freq = freq * 10 +  (s.charAt(k) - '0');
            else if(s.charAt(k) == '[') {
                k++;
                String last = decodeStringHelper(s);
                for(int i=0;i<freq;i++) result += last;
                freq = 0;
            } else if(s.charAt(k) == ']') {
                return result;
            } else result += s.charAt(k);
            k++;
        }
        return result;        
    }
    
    public String decodeString(String s) {
        return decodeStringHelper(s);
    }
}
//######################################### Recursive ######################################### 
string dfs(string s,int &k) {
  int cnt = 0;
  string res;
  while(k < s.size()) {
    if(isdigit(s[k])) { 
      cnt = (10 * cnt) + (s[k++] - '0'); //15
    } else if(s[k] == '[') {
      string rem = dfs(s,++k);
      for(int i=0;i<cnt;i++) {
        res += rem;
      }
      cnt = 0;
    } else if(s[k] == ']') {
      k++;
      return res;
    } else {
      res += s[k++];
    }
  }
  return res;
}

string decodeString(string s) {
  int k = 0; 
  return dfs(s,k);
}

//######################################### Iterative ######################################### 
string decodeString(string s) {
      string ans, tmp;
      stack<int> numStack;
      stack<string> strStack;
      int n = 0;
      for (int i = 0; i < s.size(); i++) {
          if (isdigit(s[i]))
              n = n * 10 + s[i] - '0';
          else if (s[i] == '[') {
              numStack.push(n);
              n = 0;
              strStack.push(tmp);
              tmp.clear();
          }
          else if (s[i] == ']') {
              int k = numStack.top();
              numStack.pop();
              for (; k > 0; k--)
                  strStack.top() += tmp;
              tmp = strStack.top();
              strStack.pop();
          }
          else
              tmp += s[i];
      }
     if (strStack.size() == 0) {
        return tmp;
     }
     return strStack.top();
}

