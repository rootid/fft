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
//Recursive
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
