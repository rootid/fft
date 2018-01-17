//Implement a magic directory with buildDict, and search methods.
//For the method buildDict, you'll be given a list of non-repetitive words to build a dictionary.
//For the method search, you'll be given a word, and judge whether if you modify exactly one character into another character in this word, the modified word is in the dictionary you just built.
//Example 1:
//Input: buildDict(["hello", "leetcode"]), Output: Null
//Input: search("hello"), Output: False
//Input: search("hhllo"), Output: True
//Input: search("hell"), Output: False
//Input: search("leetcoded"), Output: False
//Note:
//You may assume that all the inputs are consist of lowercase letters a-z.
//For contest purpose, the test data is rather small by now. You could think about highly efficient algorithm after the contest.
//Please remember to RESET your class variables declared in class MagicDictionary, as static/class variables are persisted across multiple test cases. Please see here for more details.

class MagicDictionary {
    /** Initialize your data structure here. */
    public MagicDictionary() {
        
    }
    /** Build a dictionary through a list of words */
    public void buildDict(String[] dict) {
        
    }
    /** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
    public boolean search(String word) {
        
    }
}

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary obj = new MagicDictionary();
 * obj.buildDict(dict);
 * boolean param_2 = obj.search(word);
 */
//######################################### With Trie  ######################################### 
class MagicDictionary {
    class TrieNode {
        TrieNode[] children = new TrieNode[26];
        boolean isWord;
        public TrieNode() {}
    }
    TrieNode root;
    /** Initialize your data structure here. */
    public MagicDictionary() {
        root = new TrieNode();
    }
    
    /** Build a dictionary through a list of words */
    public void buildDict(String[] dict) {
        for (String s : dict) {
            TrieNode node = root;
            for (char c : s.toCharArray()) {
                if (node.children[c - 'a'] == null) {
                    node.children[c - 'a'] = new TrieNode();
                }
                node = node.children[c - 'a'];
            }
            node.isWord = true;
        }
    }
    
    /** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
    public boolean search(String word) {
        char[] arr = word.toCharArray();
        for (int i = 0; i < word.length(); i++) {
            for (char c = 'a'; c <= 'z'; c++) {
                if (arr[i] == c) {
                    continue;
                }
                char org = arr[i];
                arr[i] = c;
                if (helper(new String(arr), root)) {
                    return true;
                }
                arr[i] = org;
            }
        }
        return false;
    }
    public boolean helper(String s, TrieNode root) {
        TrieNode node = root;
        for (char c : s.toCharArray()) {
            if (node.children[c - 'a'] == null) {
                return false;
            }
            node = node.children[c - 'a'];
        }
        return node.isWord;
    }
}

//######################################### Use neighbors ######################################### 
//A word 'apple' has neighbors '*pple', 'a*ple', 'ap*le', 'app*e', 'appl*'. When searching for 
//a target word like 'apply', we know that a necessary condition is a neighbor of 'apply' is a neighbor of some source word in our magic dictionary.
//If there is more than one source word that does this, then at least one of those source words will be different from the target word. Otherwise, we need to check that the source doesn't equal the target.
class MagicDictionary(object):
    def _candidates(self, word):
        for i in xrange(len(word)):
            yield word[:i] + '*' + word[i+1:]
            
    def buildDict(self, words):
        self.words = set(words)
        self.near = collections.Counter(cand for word in words
                                        for cand in self._candidates(word))

    def search(self, word):
        return any(self.near[cand] > 1 or 
                   self.near[cand] == 1 and word not in self.words
                   for cand in self._candidates(word))

//######################################### only neightbors ######################################### 
//(extensions.get(key) >= 2)?
//It's because of the wording of the question, which says that search() looks for cases where exactly one change must occur.
//Suppose the dictionary contains just "apple" (and thus includes the wildcard version "appl*") and someone calls search("apple"). That needs to return false, because "apple" -> "apple" is zero transitions.
//However, the instant someone adds "apply" to the dictionary, then search("apple") should return true because there's a one-step path from "apple" to "apply". The same is true the other way around, because "apply"->"apple" is 1 step as well. Since each of those two dictionary words added "appl*", its weight should be 2.
public class MagicDictionary {
  Set<String> originalWords;
  Map<String, Integer> extensions;

  /**
   * Initialize your data structure here.
   */
  public MagicDictionary() {
    originalWords = new HashSet<>();
    extensions = new HashMap<>();
  }

  /**
   * Build a dictionary through a list of words
   */
  public void buildDict(String[] dict) {
    char[] str;
    int n;
    char temp;
    for (String word : dict) {
      originalWords.add(word);
      str = word.toCharArray();
      n = word.length();
      for (int i = 0; i < n; i++) {
        temp = str[i];
        str[i] = '*';
        String key = new String(str);
        extensions.put(key, extensions.getOrDefault(key, 0) + 1);
        str[i] = temp;
      }
    }
  }

  /**
   * Returns if there is any word in the trie that equals to the given word after modifying exactly one character
   */
  public boolean search(String word) {
    int n = word.length();
    char[] str = word.toCharArray();
    char temp;
    String key;
    for (int i = 0; i < n; i++) {
      temp = str[i];
      str[i] = '*';
      key = new String(str);
      if (extensions.containsKey(key)) {
        if (extensions.get(key) >= 2) {
          return true;
        }
        if (!originalWords.contains(word)) {
          return true;
        }
      }
      str[i] = temp;
    }
    return false;
  }
}
//######################################### Only map ######################################### 
class MagicDictionary {
public:
    unordered_map<string, char> map;

    void buildDict(vector<string> dict) {
        for (string &word : dict) {
            for (int i = 0; i < word.size(); i++) {
                string mw = word;
                mw[i] = '0';
                if (!map.count(mw))
                    map[mw] = word[i];
                else if (map[mw] != word[i])
                    map[mw] = 0;
            }
        }
    }
    
    bool search(string word) {
        for (int i = 0; i < word.size(); i++) {
            string mw = word;
            mw[i] = '0';
            if (map.count(mw) && map[mw] != word[i])
                return true;
        }
        return false;
    }
};


