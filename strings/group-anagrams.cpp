//Group Anagrams
//Given an array of strings, group anagrams together.
//For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"], 
//Return:
//[
//  ["ate", "eat","tea"],
//  ["nat","tan"],
//  ["bat"]
//]
//Note: All inputs will be in lower-case.


//######################################### O(N * K) ######################################### 
    public List<List<String>> groupAnagrams(String[] strs) {
        if (strs.length == 0) return new ArrayList();
        Map<String, List> ans = new HashMap<String, List>();
        int[] count = new int[26];
        for (String s : strs) {
            Arrays.fill(count, 0);
            for (char c : s.toCharArray()) count[c - 'a']++;
            
            StringBuilder sb = new StringBuilder("");
            for (int i = 0; i < 26; i++) {
                sb.append('#');
                sb.append(count[i]);
            }
            String key = sb.toString();
            if (!ans.containsKey(key)) ans.put(key, new ArrayList());
            ans.get(key).add(s);
        }
        return new ArrayList(ans.values());
    }

//######################################### O(N * log K) ######################################### 
public List<List<String>> groupAnagrams(String[] strs) {
    Map<String, List<String>> map = new HashMap<>();
    for(String str : strs) {
        char[] ar = str.toCharArray();
        Arrays.sort(ar);
        String key = String.valueOf(ar);
        map.computeIfAbsent(key, v-> new ArrayList<>()).add(str);
    }    
    return new ArrayList(map.values());
}

//1. use auto& rather then auto to avoid unnecessary copy
//2. use std::move() to steal vector from map
//3. use vector.reserve() to avoid reallocate
//#################################### Move + reserve #################################### 
vector<vector<string>> groupAnagrams(vector<string>& strs) {
      int n = strs.size();
      unordered_map<string, vector<string>> map;
      vector<vector<string> > ret;
      for (const auto& s : strs) {
          string t = s;
          sort(t.begin(), t.end());
          map[t].push_back(s);
      }
      ret.reserve(map.size());
      for (auto& p : map) {
          ret.push_back(std::move(p.second));
      }
      return ret;
}

//#################################### GOOD #################################### 
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string,vector<string> > cntr;
    vector<vector<string> > result;
    for(auto str:strs) {
        string tmp = str;
        sort(tmp.begin(),tmp.end());
        cntr[tmp].push_back(str);
    } 
    for(auto &p:cntr) {
        vector<string> tmp;
        for(auto &str:p.second) {
            tmp.push_back(str);
        }
        result.push_back(tmp);
    }
    return result;
}
