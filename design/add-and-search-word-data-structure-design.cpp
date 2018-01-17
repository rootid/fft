//Add and Search Word - Data structure design
//Design a data structure that supports the following two operations:
//void addWord(word)
//bool search(word)
//search(word) can search a literal word or a regular expression string containing only letters a-z or .. A . means it can represent any one letter.
//For example:
//addWord("bad")
//addWord("dad")
//addWord("mad")
//search("pad") -> false
//search("bad") -> true
//search(".ad") -> true
//search("b..") -> true
//Note:
//You may assume that all words are consist of lowercase letters a-z.
//click to show hint.
//You should be familiar with how a Trie works. If not, please work on this problem: Implement Trie (Prefix Tree) first.
//######################################################  TrieNode + Rec find ######################################################  
class TrieNode {
public:
    bool isLeaf;
    TrieNode* children[26];
    TrieNode(): isLeaf(false) {
        memset(children, NULL, sizeof(TrieNode*) * 26);
    }
};

class WordDictionary {

public: 
  WordDictionary() { 
    root = new TrieNode(); 
  }
  // Adds a word into the data structure.
  void addWord(string word) {
      TrieNode* current = root;
      for (char c : word) {
          if (!(current -> children[c - 'a'])) { //no node present create a new one
              current -> children[c - 'a'] = new TrieNode();
          }
          current = current -> children[c - 'a'];
      }
      current -> isLeaf = true;
  }

  // Returns if the word is in the data structure. A word could
  // contain the dot character '.' to represent any one letter.
  bool search(string word) {
      return query(word.c_str(), root);
  }

private:
    TrieNode* root; 
    
    bool query(const char* word, TrieNode* node) {
        TrieNode* current = node;
        for (int i = 0; word[i]; i++) {
            if (current && word[i] != '.')
                current = current -> children[word[i] - 'a'];
            else if (current && word[i] == '.') {  //for . search all children
                TrieNode* tmp = current;
                for (int j = 0; j < 26; j++) {
                    current = tmp -> children[j];
                    if (query(word + i + 1, current))
                        return true;
                }
            }
            else break;
        }
        return current && current -> isLeaf; 
    }
};
/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary obj = new WordDictionary();
 * obj.addWord(word);
 * bool param_2 = obj.search(word);
 */

//######################################################  TrieNode compact struct + Rec find + ######################################################  
class TrieNode {
public:
    TrieNode *next[26]{};
    bool is_leaf = false;
    TrieNode *get(char c) { return next[c - 'a']; }
    void add(char c) { next[c - 'a'] = new TrieNode; }
};

class WordDictionary {
public:
    WordDictionary() : root(new TrieNode) {}
    void addWord(const string &word) {
        auto p = root;
        for (auto c : word) {
            if (!p->get(c)) p->add(c);
            p = p->get(c);
        }
        p->is_leaf = true;
    }
    bool search(const string &word) {  return search(word, 0, root); }
private:
    bool search(const string &word, int pos, TrieNode *root) {
        if (pos == word.size()) return root->is_leaf;
        if (word[pos] != '.') {
            root = root->get(word[pos]);
            return root ? search(word, pos + 1, root) : false;
        }
        for (auto i = 0; i < 26; ++i)
            if (root->next[i] && search(word, pos + 1, root->next[i]))
                return true;
        return false;
    }
    TrieNode *root;
};


//################################################### TrieNode + vector ################################################### 
struct Trie 
{
     vector<Trie *> child;
     bool isWord;
     Trie() : isWord(false), child(vector<Trie *>(26, nullptr)) {}
 };

class WordDictionary {
public:
 Trie *root;
 WordDictionary() : root(new Trie()) {}

void addWord(string word) {
    const int size_w = word.size();
    Trie *cur = root;
    for (int i = 0; i < size_w; i++) {
        int index = word[i] - 'a';
        if (!cur->child[index]) cur->child[index] = new Trie();
        cur = cur->child[index];
    }
    cur->isWord = true;
}

bool search(string word) {
    return search(word.c_str(), root);
}
bool search(const char *ch, Trie *cur) {
    if (!cur) return false;
    if (*ch == '\0') return cur->isWord;
    if (*ch != '.') {
         return search(ch+1, cur->child[*ch - 'a']);
    } else {
        for (int i = 0; i <= 25; i++) {
            if (search(ch+1, cur->child[i])) return true;
        }
        return false;
    }
}
};

//#################################### pytonic  ################################################################ 
//#################################### recursive  ################################################################ 
//class WordDictionary:
//
//    def __init__(self):
//        self.root = {}
//    
//    def addWord(self, word):
//        node = self.root
//        for char in word:
//            node = node.setdefault(char, {})
//        node[None] = None
//
//    def search(self, word):
//        def find(word, node):
//            if not word:
//                return None in node
//            char, word = word[0], word[1:]
//            if char != '.':
//                return char in node and find(word, node[char])
//            return any(find(word, kid) for kid in node.values() if kid)
//        return find(word, self.root)
//########################################### iterative search ########################################### 
//    def search(self, word):
//        nodes = [self.root]
//        for char in word:
//            nodes = [kid
//                     for node in nodes
//                     for key, kid in node.items()
//                     if char in (key, '.') and kid]
//        return any(None in node for node in nodes)
//or 
//
//  def search(self, word):
//        nodes = [self.root]
//        for char in word:
//            nodes = [kid for node in nodes for kid in
//                     ([node[char]] if char in node else
//                      filter(None, node.values()) if char == '.' else [])]
//        return any(None in node for node in nodes)


//class WordDictionary:
//
//    def __init__(self):
//        self.root = {}
//    
//    def addWord(self, word):
//        node = self.root
//        for char in word:
//            node = node.setdefault(char, {})
//        node['$'] = None
//
//    def search(self, word):
//        nodes = [self.root]
//        for char in word + '$':
//            nodes = [kid for node in nodes for kid in
//                     ([node[char]] if char in node else
//                      filter(None, node.values()) if char == '.' else [])]
//        return bool(nodes)
//
//##### one liner pytonic
//
//
//class WordDictionary(object):
//    def __init__(self):
//        self.root = {}
//
//    def addWord(self, word):
//        cur = self.root
//        for c in word:
//            cur = cur.setdefault(c, {})
//        cur[None] = 'isWord'
//
//    def search(self, word):
//        def f(n, w):
//            return any(f(n[x], w[1:]) for x in (n if w[0]=='.' else [w[0]]) if x and x in n) if w else None in n
//        return f(self.root, word)
//
//from collections import defaultdict
//def _trie():
//    return defaultdict(_trie)
//
//class Trie(object):                                                              
//                                                                                 
//    def __init__(self):                                                          
//        self.trie = _trie()                                                      
//                                                                                 
//    def insert(self, word):                                                      
//        self._insert(word, self.trie)                                            
//                                                                                 
//    def _insert(self, word, trie):                                               
//        self._insert(word[1:], trie[word[0]]) if word else trie['$']             
//                                                                                 
//    def search(self, word):                                                      
//        return self._search(self.trie, word)                                     
//                                                                                 
//    def _search(self, trie, word, prefix=False):                                 
//        return True if not word and ('$' in trie or prefix) else self._search(trie[word[0]], word[1:], prefix=prefix) if word and word[0] in trie else False
//                                                                                 
//    def startsWith(self, prefix):                                                
//        return self._search(self.trie, prefix, True)
//######################################## updated insert and search ######################################## 
//def insert(self, word):
//    reduce(operator.getitem, word + '$', self.trie)
//
//def _search(self, trie, word, prefix=False):                                 
//    return word[0] in trie and self._search(trie[word[0]], word[1:], prefix) if word else '$' in trie or prefix
