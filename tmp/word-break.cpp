//Word Break
//Given a string s and a dictionary of words dict, determine if s can be segmented into a space-separated sequence of one or more dictionary words.
//For example, given
//s = "leetcode",
//dict = ["leet", "code"].
//Return true because "leetcode" can be segmented as "leet code".
//
//
//TOP-DOWN APPROACH
bool wordBreak(string s, unordered_set<string>& dict) {
  int len = s.size();
  vector<bool> dp(len+1,false);
  dp[0] = true;
  for (int i = 1; i <= len;  ++i)  //string length
  {
      for (int j = 0; j <i; ++j)  //cut points  
      {
          if(dict.find(s.substr(j, i-j)) != dict.end() & dp[j]) //check the string which starts j & what was the cut value for j-1
          {
              dp[i] = true;
              break;
          }
      }
  }             
  return dp[len];
}
