//Word Break
//Given a string s and a dictionary of words dict, determine if s can be segmented into a space-separated sequence of one or more dictionary words.
//For example, given
//s = "leetcode",
//dict = ["leet", "code"].
//Return true because "leetcode" can be segmented as "leet code".
//
//
//

bool dfs_helper(string s, int start, unordered_set<string> &dict){
  if (start == s.length()) {
    return true;
  }
  for (int i=start,len = s.length();i<len;i++){
      if (dict.find(s.substr(start,i-start+1)) != dict.end() 
          && (i==len-1 || dfs_helper(s,i+1,dict))) {
        return true;
      }
  }
  return false;
}

bool wordBreak(string s, unordered_set<string> &dict){
  return dfs_helper(s,0,dict);
}
