//Word Break
//Given a string s and a dictionary of words dict, determine if s can be segmented into a space-separated sequence of one or more dictionary words.
//For example, given
//s = "leetcode",
//dict = ["leet", "code"].
//Return true because "leetcode" can be segmented as "leet code".
//
//
//
//######################################### BFS ######################################### 
//T : O(n^2) 
//S : O(n)

//0123456789
//nightmare, [ "night","mare", "nightmare"]
//0-->5-->9
//
//|__ __ _^
public boolean wordBreak(String s, List<String> dict) {
    if (dict.contains(s)) return true;
    Set<Integer> visitedIdx = new HashSet<>();
    Queue<Integer> pathQ = new LinkedList<>();
    int n = s.length();
    pathQ.offer(0);
    while(!pathQ.isEmpty()) {
        int startIdx = pathQ.poll();
        if(!visitedIdx.contains(startIdx)) {
            for(int i= startIdx+1;i<= s.length();i++) {
                 if(dict.contains(s.substring(startIdx,i))) {
                     visitedIdx.add(startIdx);
                     if(i == n) return true;
                     pathQ.offer(i);
                 }
            }
        }
    }
    return false;
}

//######################################### Backtrack ######################################### 
private boolean dfs(String s, int k, List<String> wordDict) {
    if(k == s.length()) return true;
    for(int i=k;i<s.length();i++)  {
        if(wordDict.contains(s.substring(k, i+1)) && (i ==  s.length() -1 || dfs(s,i+1,wordDict))) return true; 
    }
    return false;
}

public boolean wordBreak(String s, List<String> wordDict) {
    return dfs(s, 0, wordDict);
}
//#################################################### TOP-DOWN APPROACH ###################################################### 
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

//######################################################## Backtrack/DFS ######################################################## 
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

//#################################################### DP ###################################################### 
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

//#################################################### BFS ###################################################### 
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
