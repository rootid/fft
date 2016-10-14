//Given a string s and a dictionary of words dict, determine if s can be segmented into a space-separated sequence of one or more dictionary words.
//For example, given
//s = "leetcode",
//dict = ["leet", "code"].
//Return true because "leetcode" can be segmented as "leet code".

#include<string>
#include<iostream>
#include<vector>

//We use a boolean vector dp[]. dp[i] is set to true if a valid word (word sequence) ends there. The optimization is to look from current position i back and only substring and do dictionary look up in case the preceding position j with dp[j] == true is found.

bool wordBreak(string s, unordered_set<string>& wordDict) {

  int len = s.size();
  vector<bool> dp(len+1,false);
  int minLen = INT_MAX;
  if(len == 0) {
    return false;
  }
  //for(auto tmp:wordDict) {
  //  if (minLen > tmp.size()) {
  //      minLen = tmp.size();
  //  }
  //}
  //leetcode
  //iterative over the length
  for(int i=1;i<len;i++) {
    //iterateve over backward
    for(int j=i-1;j>=0;j--) {
      if(dp[j]) {
        if(wordDict.find(s.substr(j,i-j))) {
          dp[i] = true;
          break;
        }
      }
    }
  }
  return dp[s.size()];

}

//BFS approach
//0123456789
//nightmare : 
//0-->5-->9
//
//|__ __ _^
//

//Go sequentially from left to right to identify wheather all strings has
//covered or not
bool wordBreak(string s, unordered_set<string> &dict) {
    // BFS
    queue<int> BFS;
    unordered_set<int> visited;
    
    BFS.push(0);
    while(BFS.size() > 0)
    {
        int start = BFS.front();
        BFS.pop();
        if(visited.find(start) == visited.end())
        { //nothing found in the stack
            visited.insert(start);
            for(int j=start; j<s.size(); j++)

              //s , start = 0, (len)
                string word(s, start, j-start+1);
                if(dict.find(word) != dict.end())
                {
                    BFS.push(j+1);  //save the succesful search
                    if(j+1 == s.size())
                        return true;
                }
            }
        }
    }
    return false;
}

int main() {
  string s= "leetcode";
  unordered_set<string> wordDict;
  wordDict.insert("leet");
  wordDict.insert("code");
}
