//Concatenated Words
//Given a list of words (without duplicates), please write a program that returns all concatenated words in the given list of words.
//A concatenated word is defined as a string that is comprised entirely of at least two shorter words in the given array.
//Example:
//Input: ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
//Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]
//Explanation: "catsdogcats" can be concatenated by "cats", "dog" and "cats"; 
// "dogcatsdog" can be concatenated by "dog", "cats" and "dog"; 
// "ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".
// Note:
// 1. The number of elements of the given array will not exceed 10,000
// 2. The length sum of elements in the given array will not exceed 600,000.
// 3. All the input string will only include lower case letters.
// 4. The returned elements order does not matter.
//

//######################################### Only data struct change ######################################### 
public List<String> findAllConcatenatedWordsInADict(String[] words) {
        List<String> list = new ArrayList<>();
        Set<String> dictionary = new HashSet<>();
        for(String string : words) dictionary.add(string);
        for(String word:words) {
            dictionary.remove(word);
            if(check(word,dictionary)) list.add(word);
            dictionary.add(word);
        }
        return list;
    }
    
    private boolean check(String word,Set<String> dictionary) {
        if(dictionary.contains(word)) return true;
        int i = word.length() - 1;
        while(i >= 1) {
            if(dictionary.contains(word.substring(0,i)) && check(word.substring(i),dictionary)) return true;
            i--;
        }
        return false;
    }
//######################################### DP ######################################### 
//TC : O(N^3)
//For any qualified word, there must be at least 3 indexes (at least 1 besides 0 and n-1 which n is the length of the word), which can be used to split the whole string to at least two sub strings and all sub strings can be found in words.
//E.g. input ["cat","cats", "dog", "sdog","dogcatsdog"], for word dogcatsdog, there are 2 sets of numbers: [0, 3, 6, 10] and [0, 3, 7, 10] which can be formed by concatenating [dog, cat, sdog] and [dog, cats, dog] respectively.
//So, we can use a vector<int> dp(n+1) to store if w.substr(0, i) can be formed by existing words. Once i reach to n and it is not the word itself, we put the word to results.
vector<string> findAllConcatenatedWordsInADict(vector<string>& words) { 
	unordered_set<string> s(words.begin(), words.end());
    vector<string> res;
    for (auto w : words) {
        int n = w.size();
        vector<int> dp(n+1);
        dp[0] = 1;
        for (int i = 0; i < n; i++) {
            if (dp[i] == 0) continue;
            for (int j = i+1; j <= n; j++) {
                if (j - i < n && s.count(w.substr(i, j-i))) dp[j] = 1;
            }
            if (dp[n]) { res.push_back(w); break; }
        }
    }
    return res; 
}


//######################################### DP ######################################### 
//If you do know one optimized solution for above question is using DP, this problem is just one more step further.
// We iterate through each word and see if it can be formed by using other words.
//Of course it is also obvious that a word can only be formed by words shorter than it.
//So we can first sort the input by length of each word, and only try to form one word by using words in front of it.
public class Solution {
    public static List<String> findAllConcatenatedWordsInADict(String[] words) {
        List<String> result = new ArrayList<>();
        Set<String> preWords = new HashSet<>();
	    //Sort by length
        Arrays.sort(words, new Comparator<String>() {
            public int compare (String s1, String s2) {
                return s1.length() - s2.length();
            }
        });
        
        for (int i = 0; i < words.length; i++) {
            if (canForm(words[i], preWords)) {
                result.add(words[i]);
            }
            preWords.add(words[i]);
        }
        
        return result;
    }
	
    private static boolean canForm(String word, Set<String> dict) { 
		if (dict.isEmpty()) return false;
		boolean[] dp = new boolean[word.length() + 1];
		dp[0] = true;
		for (int i = 1; i <= word.length(); i++) {
			for (int j = 0; j < i; j++) {
				if (!dp[j]) continue;
				if (dict.contains(word.substring(j, i))) { 
					dp[i] = true;
					break; 
				}
		  }
		}
		return dp[word.length()];
    }
}

//######################################### Backtrack/DFS  ######################################### 
public List<String> findAllConcatenatedWordsInADict(String[] words) {
    List<String> list = new ArrayList<String>();
    Set<String> set = new HashSet(Arrays.asList(words));

    for(String word : words) {
        set.remove(word);
        if(dfs(word, set, "")) list.add(word);
        set.add(word);
    }
    return list;
}

private boolean dfs(String word, Set<String> set, String previous) {
    if(!previous.equals("")) set.add(previous);
    if(set.contains(word)) return true;
    
    for(int i = 1; i < word.length(); i++) {
        String prefix = word.substring(0,i);
        if(set.contains(prefix) && 
            dfs(word.substring(i,word.length()), set, previous+prefix)) {
            return true;
        }
    }
    return false;
}

//######################################### Trie ######################################### 
public List<String> findAllConcatenatedWordsInADict(String[] words) {
        List<String> res = new ArrayList<String>();
        if (words == null || words.length == 0) {
            return res;
        }
        TrieNode root = new TrieNode();
        for (String word : words) { // construct Trie tree
            if (word.length() == 0) {
                continue;
            }
            addWord(word, root);
        }
        for (String word : words) { // test word is a concatenated word or not
            if (word.length() == 0) {
                continue;
            }
            if (testWord(word.toCharArray(), 0, root, 0)) {
                res.add(word);
            }
        }
        return res;
    }
    public boolean testWord(char[] chars, int index, TrieNode root, int count) { // count means how many words during the search path
        TrieNode cur = root;
        int n = chars.length;
        for (int i = index; i < n; i++) {
            if (cur.childern[chars[i] - 'a'] == null) return false; // no matching word found
            if (cur.childern[chars[i] - 'a'].isEnd) {
                if (i == n - 1) { // no next word, so test count to get result.
                    return count >= 1;
                }
                if (testWord(chars, i + 1, root, count + 1)) return true; //next word with ^ count
            }
            cur = cur.childern[chars[i] - 'a'];
        }
        return false;
    }
    public void addWord(String str, TrieNode root) {
        char[] chars = str.toCharArray();
        TrieNode cur = root;
        for (char c : chars) {
            if (cur.childern[c - 'a'] == null) cur.childern[c - 'a'] = new TrieNode();
            cur = cur.childern[c - 'a'];
        }
        cur.isEnd = true;
    }
}
class TrieNode {
    TrieNode[] childern;
    boolean isEnd;
    public TrieNode() {
        childern = new TrieNode[26];
    }

//######################################### Toplogical Sort ######################################### 
//Let's discuss whether a word should be included in our answer.
//Consider the word as a topologically sorted directed graph, where each node is a letter, 
//and an edge exists from i to j if word[i:j] is in our wordlist, [and there is no edge from i=0 to j=len(word)-1].
// We want to know if there is a path from beginning to end. If there is, then the word can be broken into concatenated parts from our wordlist. To answer this question, we DFS over this graph.

S = set(A)
ans = []
for word in A:
  if not word: continue
  stack = [0]
  seen = {0}
  M = len(word)
  while stack:
    node = stack.pop()
    if node == M:
      ans.append(word)
      break
    for j in xrange(M - node + 1):
      if (word[node:node+j] in S and 
          node + j not in seen and
          (node > 0 or node + j != M)):
        stack.append(node + j)
        seen.add(node + j)

return ans


//######################################### Backtrack ######################################### 
class Solution(object):
    def findAllConcatenatedWordsInADict(self, words):
        """
        :type words: List[str]
        :rtype: List[str]
        """
        word_set = set(words)
        ans = []
        def helper(w, cur, cnt):
            if cur == len(w):
                if cnt > 1:
                    return True
                else:
                    return False
            for i in xrange(cur + 1, len(w) + 1):
                if w[cur : i] in word_set and helper(w, i, cnt + 1):
                    return True
            return False
        for w in words:
            if helper(w, 0, 0):
                ans.append(w)
        return ans

