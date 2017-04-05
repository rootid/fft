//Word Break II
//Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, add spaces in s to construct a sentence where each word is a valid dictionary word. You may assume the dictionary does not contain duplicate words.
//Return all such possible sentences.
//For example, given
//s = "catsanddog",
//dict = ["cat", "cats", "and", "sand", "dog"].
//A solution is ["cats and dog", "cat sand dog"].
//

//########################################### 
vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
    unordered_map<int, vector<string>> memo {{s.size(), {""}}};
    function<vector<string>(int)> sentences = [&](int i) {
        if (!memo.count(i))
            for (int j=i+1; j<=s.size(); j++)
                if (wordDict.count(s.substr(i, j-i)))
                    for (string tail : sentences(j))
                        memo[i].push_back(s.substr(i, j-i) + (tail=="" ? "" : ' ' + tail));
        return memo[i];
    };
    return sentences(0);
}

//########################################## Backtracking ############################################# 
vector<string> combine(string word, vector<string> prev){
    for(int i=0;i<prev.size();++i){
        prev[i]+=" "+word;
    }
    return prev;
}
vector<string> dfs_helper(string s, unordered_set<string>& dict,unordered_map<string, vector<string>>& m) {
    if(m.count(s)) { 
      return m[s]; //take from memory
    }
    vector<string> result;
    if(dict.count(s)){ //a whole string is a word
        result.push_back(s);
    }
    for(int i=1;i<s.size();++i){
        string word = s.substr(i); //last string
        if(dict.count(word)) {
            string rem =s.substr(0,i); // first string /get all strings of len i
            vector<string> prev = combine(word,dfs_helper(rem,dict,m));
            //add prev to result
            result.insert(result.end(),prev.begin(), prev.end());
        }
    }
    m[s] = result; //memorize
    return result;
}
vector<string> wordBreak(string s, vector<string>& words) {
  unordered_map<string, vector<string>> m;
  unordered_set<string> dict(words.begin(),words.end());
  return dfs_helper(s,dict,m);
}


//######################################### Iterative  ######################################### 
vector<string> wordBreakHelper(string s, unordered_set<string> &dict) {
	vector<string> res;
  if(s.empty()) {
    return res;
  }
	int len = s.length();
	vector<vector<int> > map(len);
	for (int i = 0; i<len; i++){
		for (int j = 0; j <= i; j++){
			string s1 = s.substr(j, i - j + 1);
			if ((j == 0 || map[j - 1].size() > 0) && dict.find(s1) != dict.end()){
				// can be cut before s[j]
				map[i].push_back(j - 1);
			}
		}
	}
	// build up result strings
	// DFS
	stack<int> sk; //first half 
	stack<string> ssk; //second half
	// init sk
	for (int i = 0; i < map[len - 1].size(); i++){
		sk.push(map[len - 1][i]);
		ssk.push(s.substr(map[len - 1][i] + 1));
	}
	
	int top;
	while (!sk.empty()){
		top = sk.top();
		sk.pop();
		string stop = ssk.top();
		ssk.pop();
		if (top == -1){
			res.push_back(stop);
			continue;
		}
		for (int i = 0; i < map[top].size(); i++){
			sk.push(map[top][i]);
			ssk.push(s.substr(map[top][i]+1, top - map[top][i]) + " " + stop);
		}    
	}
	return res;
}
vector<string> wordBreak(string s, vector<string>& words) {
  unordered_set<string> dict(words.begin(),words.end());
  return wordBreakHelper(s,dict);
}

//################################################# TLE ################################################# 
vector<string> wordBreakHelper(string s, unordered_set<string> &dict) {
        vector<string> sentences;
        vector<string> sol;
        findWordBreak(s, dict, 0, sol, sentences);
        return sentences;
    }
    
void findWordBreak(string &s, unordered_set<string> &dict, int start, vector<string> &sol, vector<string> &sentences) {
    if(start==s.size() && !sol.empty()) {   // find word break
        string temp = sol[0];
        for(int i=1; i<sol.size(); i++) 
            temp.append(" "+sol[i]);
        sentences.push_back(temp);
    }
    string word;
    for(int i=start; i<s.size(); i++) {
        word.push_back(s[i]);
        if(dict.count(word)!=0) {
            sol.push_back(word);
            findWordBreak(s, dict, i+1, sol, sentences);
            sol.pop_back();
        }
    }
}
vector<string> wordBreak(string s, vector<string>& words) {
  unordered_set<string> dict(words.begin(),words.end());
  return wordBreakHelper(s,dict);
}

//########################################## Backtracking OPT - 1############################################# 
//precompute min Length
vector<string> combine(string word, vector<string> prev){
    for(int i=0;i<prev.size();++i){
        prev[i]+=" "+word;
    }
    return prev;
}
vector<string> dfs_helper(string s, unordered_set<string>& dict,unordered_map<string, vector<string>>& m,int& minLen) {
    if(m.count(s)) { 
      return m[s]; //take from memory
    }
    vector<string> result;
    if(dict.count(s)){ //a whole string is a word
        result.push_back(s);
    }
    for(int i=minLen-1;i<s.size();++i){
        string word = s.substr(i); //last string
        if(dict.count(word)) {
            string rem =s.substr(0,i); // first string /get all strings of len i
            vector<string> prev = combine(word,dfs_helper(rem,dict,m,minLen));
            //add prev to result
            result.insert(result.end(),prev.begin(), prev.end());
        }
    }
    m[s] = result; //memorize
    return result;
}
vector<string> wordBreak(string s, vector<string>& words) {
  unordered_map<string, vector<string>> m;
  unordered_set<string> dict(words.begin(),words.end());
  int len = words.size();
  int minLen = INT_MAX;
  for(string& word:words) {
    int l = word.length();
    minLen = min(minLen,l);
  }
  return dfs_helper(s,dict,m,minLen);
}

//##########################################################################################################################################################
//DP + DFS. Very similar to Word Break I, but instead of using a boolean dp array, I used an array of Lists to maintain all of the valid start positions for every end position. Then just do classic backtracking to find all solutions. The time complexity is O(n*m) + O(n * number of solutions), where n is the length of the input string, m is the length of the longest word in the dictionary. The run time was 6ms. It is very efficient because DP is used to find out all the valid answers, and no time is wasted on doing the backtracking.
vector<string> wordBreak(string s, Set<string> wordDict) {
    vector<Integer>[] starts = new vector[s.length() + 1]; // valid start positions
    starts[0] = new Arrayvector<Integer>();
    
    int maxLen = getMaxLen(wordDict);
    for (int i = 1; i <= s.length(); i++) {
        for (int j = i - 1; j >= i - maxLen && j >= 0; j--) {
            if (starts[j] == null) continue;
            string word = s.substring(j, i);
            if (wordDict.contains(word)) {
                if (starts[i] == null) {
                    starts[i] = new Arrayvector<Integer>();
                }
                starts[i].add(j);
            }
        }
    }
    
    vector<string> rst = new Arrayvector<>();
    if (starts[s.length()] == null) {
        return rst;
    }
    
    dfs(rst, "", s, starts, s.length());
    return rst;
}


void dfs(vector<string> rst, string path, string s, vector<Integer>[] starts, int end) {
    if (end == 0) {
        rst.add(path.substring(1));
        return;
    }
    for (Integer start: starts[end]) {
        string word = s.substring(start, end);
        dfs(rst, " " + word + path, s, starts, start);
    }
}

int getMaxLen(Set<string> wordDict) {
    int max = 0;
    for (string s : wordDict) {
        max = Math.max(max, s.length());
    }
    return max;
}


//Method 2: Memoization + Backtracking
//HashMap to memoize all the possible strings that can be formed starting from index i. 
//The time complexity is O(len(wordDict) ^ len(s / minWordLenInDict)) . The space complexity would be larger than other methods though. 
public List<String> wordBreak(String s, Set<String> wordDict) {
    HashMap<Integer, List<String>> memo = new HashMap<>(); // <Starting index, rst list>
    return dfs(s, 0, wordDict, memo);
}

private List<String> dfs(String s, int start, Set<String> dict, HashMap<Integer, List<String>> memo) {
    if (memo.containsKey(start)) {
        return memo.get(start);
    }
    
    List<String> rst = new ArrayList<>();
    if (start == s.length()) {
        rst.add("");
        return rst;
    }
    
    String curr = s.substring(start);
    for (String word: dict) {
        if (curr.startsWith(word)) {
            List<String> sublist = dfs(s, start + word.length(), dict, memo);
            for (String sub : sublist) {
                rst.add(word + (sub.isEmpty() ? "" : " ") + sub);
            }
        }
    }
    memo.put(start, rst);
    return rst;
}

//#########################################################################################################################
//Method 3: DP Prunning + Backtracking. My very first solution is like this: using a boolean array to memoize whether a substring starting from position i to the end is breakable. This works well for worst cases like: s = "aaaaaaaaaaaab", dict = ["a", "aa", "aaa", "aaaa"]. However, for cases like: s = "aaaaaaaaaaaaa", dict = ["a", "aa", "aaa", "aaaa"], the time complexity is still O(2^n). Here is the code:

public List<String> wordBreak(String s, Set<String> wordDict) {
    List<String> rst = new ArrayList<>();
    if (s == null || s.length() == 0 || wordDict == null) {
        return rst;
    }
    
    boolean[] canBreak = new boolean[s.length()];
    Arrays.fill(canBreak, true);
    StringBuilder sb = new StringBuilder();
    dfs(rst, sb, s, wordDict, canBreak, 0);
    return rst;
}

private void dfs(List<String> rst, StringBuilder sb, String s, Set<String> dict, 
    boolean[] canBreak, int start) {
    if (start == s.length()) {
        rst.add(sb.substring(1));
        return;
    }
    if (!canBreak[start]) {
        return;
    }
    
    for (int i = start + 1; i <= s.length(); i++) {
        String word = s.substring(start, i);
        if (!dict.contains(word)) continue;
        
        int sbBeforeAdd = sb.length();
        sb.append(" " + word);
        
        int rstBeforeDFS = rst.size();
        dfs(rst, sb, s, dict, canBreak, i);
        if (rst.size() == rstBeforeDFS) {
            canBreak[i] = false;
        }
        sb.delete(sbBeforeAdd, sb.length());
    }
}

private int getMaxLen(Set<String> wordDict) {
    int max = 0;
    for (String s : wordDict) {
        max = Math.max(max, s.length());
    }
    return max;
}
