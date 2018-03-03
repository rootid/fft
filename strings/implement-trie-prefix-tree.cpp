//Implement Trie (Prefix Tree)
//Implement a trie with insert, search, and startsWith methods.
//Note:
//You may assume that all inputs are consist of lowercase letters a-z.
//class Trie {
//public:
//    /** Initialize your data structure here. */
//    Trie() {
//    }
//    /** Inserts a word into the trie. */
//    void insert(string word) { //must be recursive
//    }
//    /** Returns if the word is in the trie. */
//    bool search(string word) { //must be recursive
//    }
//    /** Returns if there is any word in the trie that starts with the given prefix. */
//    bool startsWith(string prefix) { //must be recursive
//    }
//};
/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * bool param_2 = obj.search(word);
 * bool param_3 = obj.startsWith(prefix);
 */

//##################################### Recursive version #########################
//Apis
class Trie {

    //ADT
    class TrieNode {

        TrieNode[] kids = new TrieNode[26];
        boolean isLeaf;

    }

    TrieNode root;

    /** Initialize your data structure here. */
    public Trie() {
        root = new TrieNode();
    }

    /** Inserts a word into the trie. */
    public void insert(String word) {
        root = insertHelper(word, 0, root);
    }

    /** Returns if the word is in the trie. */
    public boolean search(String word) {
        return searchHelper(word,0,root);
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    public boolean startsWith(String prefix) {
        return startsWithHelper(prefix,0,root);
    }

    private boolean searchHelper(String word, int d, TrieNode x) {
        if(x == null) return false;
        if(d == word.length()) return x.isLeaf;
        char c = (char)(word.charAt(d) - 'a');
        x = x.kids[c];
        return searchHelper(word, d+1, x);
    }

    private boolean startsWithHelper(String word, int d, TrieNode x) {
        if(x == null) return false;
        if(d == word.length()) return true;
        char c = (char)(word.charAt(d) - 'a');
        x = x.kids[c];
        return startsWithHelper(word, d+1, x);
    }

    private TrieNode insertHelper(String word, int d, TrieNode x) {
        if(x == null) x = new TrieNode();
        if(word.length() == d) {
            x.isLeaf = true;
            return x;
        }
        char c = (char)(word.charAt(d) - 'a');
        x.kids[c] = insertHelper(word, d+1, x.kids[c]);
        return x;
    }
}

//##################################### Iterative version #########################
/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * boolean param_2 = obj.search(word);
 * boolean param_3 = obj.startsWith(prefix);
 */


class TrieNode {
    public char val;
    public boolean isWord;
    public TrieNode[] children = new TrieNode[26];
    public TrieNode() {}
    TrieNode(char c){
        TrieNode node = new TrieNode();
        node.val = c;
    }
}

public class Trie {
    private TrieNode root;
    public Trie() {
        root = new TrieNode();
        root.val = ' ';
    }

    public void insert(String word) {
        TrieNode ws = root;
        for(int i = 0; i < word.length(); i++){
            char c = word.charAt(i);
            if(ws.children[c - 'a'] == null){
                ws.children[c - 'a'] = new TrieNode(c);
            }
            ws = ws.children[c - 'a'];
        }
        ws.isWord = true;
    }

    public boolean search(String word) {
        TrieNode ws = root;
        for(int i = 0; i < word.length(); i++){
            char c = word.charAt(i);
            if(ws.children[c - 'a'] == null) return false;
            ws = ws.children[c - 'a'];
        }
        return ws.isWord;
    }

    public boolean startsWith(String prefix) {
        TrieNode ws = root;
        for(int i = 0; i < prefix.length(); i++){
            char c = prefix.charAt(i);
            if(ws.children[c - 'a'] == null) return false;
            ws = ws.children[c - 'a'];
        }
        return true;
    }
}


//##################################### Python -Iterative #########################
class TrieNode:
        # Initialize your data structure here.
        def __init__(self):
            self.word=False
            self.children={}

    class Trie:

        def __init__(self):
            self.root = TrieNode()

        # @param {string} word
        # @return {void}
        # Inserts a word into the trie.
        def insert(self, word):
            node=self.root
            for i in word:
                if i not in node.children:
                    node.children[i]=TrieNode()
                node=node.children[i]
            node.word=True

        # @param {string} word
        # @return {boolean}
        # Returns if the word is in the trie.
        def search(self, word):
            node=self.root
            for i in word:
                if i not in node.children:
                    return False
                node=node.children[i]
            return node.word

        # @param {string} prefix
        # @return {boolean}
        # Returns if there is any word in the trie
        # that starts with the given prefix.
        def startsWith(self, prefix):
            node=self.root
            for i in prefix:
                if i not in node.children:
                    return False
                node=node.children[i]
            return True


    # Your Trie object will be instantiated and called as such:
    # trie = Trie()
    # trie.insert("somestring")
    # trie.search("key")

//##################################### C-style initialization #########################
class TrieNode {
public:
    TrieNode():isWord(false) {
        memset(Next,0,sizeof(TrieNode*)*26);
    }
    TrieNode(char ac):c(ac),isWord(false) {
        memset(Next,0,sizeof(TrieNode*)*26);
    }
    TrieNode* Next[26];
    char c;
    bool isWord;
};
class Trie {
public:
  Trie() {
    root = new TrieNode();
  }
  void insert(string word) {
      TrieNode *p = root;
      int index;
      for(char c:word) {
          index = c - 'a';
          if(p->Next[index] == NULL) {
              p->Next[index] = new TrieNode(c); //initialize p
          }
          p = p->Next[index];
      }
      p->isWord = true;
  }
  bool search(string word) {
      TrieNode*p = root;
      int index;
      for(char c:word) {
          index = c - 'a';
          if(p->Next[index] == NULL) {
              return false;
          }
          p = p->Next[index];
      }
      return p->isWord;
  }
  bool startsWith(string prefix) {
      TrieNode*p = root;
      int index;
      for(char c:prefix) {
          index = c - 'a';
          if(p->Next[index] == NULL) {
              return false;
          }
          p = p->Next[index];
      }
      return true;
  }
private:
  TrieNode* root;
};
//############################################# Recursive way ###############################################
//https://www.topcoder.com/community/data-science/data-science-tutorials/using-tries/
class TrieNode {
public:
  TrieNode() {
    words = 0;
    prefixs = 0;
    for(int i=0;i<26;i++) {
       links[i]=NULL;
    }
  }
  int words;
  int prefixs;
  TrieNode* links[26];
};
class Trie {
public:
  Trie() {
    root = new TrieNode();
  }
  void insert(string word) {
    insertHelper(root,word,0);
  }
  bool search(string word) {
    return searchHelper(root,word,0) != 0;
  }
  bool startsWith(string prefix) {
    return startsWithHelper(root,prefix,0)!=0;
  }
  void insertHelper(TrieNode * node,string &word,int pos) {
      if(pos == word.size()) { //reached to end-of the string
          node->words++;
          node->prefixs++;
      } else {
        node->prefixs++;
        int char_code=word[pos]-'a';
        if(node->links[char_code]== NULL) {
            node->links[char_code]= new TrieNode();
        }
        insertHelper(node->links[char_code],word,pos+1);
      }
  }
  int searchHelper(TrieNode * node,string &word,int pos) {
      int char_code=word[pos]-'a';
      if(pos==word.size()) {
          return node->words;
      } else if(node->links[char_code]==NULL) {
          return 0;
      }
      return searchHelper(node->links[char_code],word,pos+1);
  }

  int startsWithHelper(TrieNode * node,string &word,int pos) {
      int char_code=word[pos]-'a';
      if(pos==word.size())
          return node->prefixs;
      else if(node->links[char_code]==NULL)
          return 0;
     return startsWithHelper(node->links[char_code],word,pos+1);
  }
private:
    TrieNode* root;
};

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");
//####################################################### Ugly #######################################################
struct TrieNode {
    char data;
    int leafValue; //To check for the leaf node
    TrieNode* next[R];
    TrieNode (char adata,int aleafValue) :
        data(adata),leafValue(aleafValue)
    {
    };
};
//insert,search
void insertInTrie (vector<string>& inputVec,vector<int>& leafValue,TrieNode** rootHead) {
    if (*rootHead == NULL) {
        *rootHead = new TrieNode(-1,-1);
    }
    int leafVal = -1;
    for (int k=0;k<inputVec.size();k++)  {
        string input = inputVec[k];
        int len = input.length();
        TrieNode* crawlNode = *rootHead;
        for (int i=0;i<len;i++) {
                if (i == len - 1) {
                    leafVal = leafValue[k];
                }
                if (crawlNode->next[input[i] - 'a'] == NULL) {
                    crawlNode->next[input[i] - 'a'] = new TrieNode(input[i],leafVal);
                    cout << "IC1=" << crawlNode  << "V=" << input[i]<< endl;
                }
                crawlNode = crawlNode->next[input[i] - 'a'];
        }
    }
}
bool queryFromTrie(TrieNode* root,string& input) {
  for (int i=0;i<input.length();i++) {
    if (root && root->next[input[i] - 'a'] && input[i] == root->next[input[i] - 'a']->data) {
      root = root->next[input[i] - 'a'];
    } else {
      return false;
    }
   }
   if (root->leafValue != -1) {
       cout << "i" << root->leafValue << endl;
       return true;
   } else {
       return false;
   }
}

void test (string query,TrieNode *root) {
    if ( queryFromTrie (root,query) ) {
        cout << "query = (" << query << ") found in the tree." << endl;
    } else {
        cout << "query = (" << query << ") not found in the tree." << endl;
    }
}


int main () {
    TrieNode *root = NULL;
    string inputSet[] = {"she","sells","sea","shells"};
    int leafValues[] = {10,2,5,6};
    vector<string> inputVec (inputSet,inputSet+sizeof(inputSet)/sizeof(inputSet[0]));
    vector<int> inputLeaf (leafValues,leafValues+sizeof(leafValues)/sizeof(leafValues[0]));
    insertInTrie (inputVec,inputLeaf,&root);
    //string query = "she";
    test ("she",root);
    test ("sells",root);
    test ("shee",root);
}

// vim: set sw=2 sts=2 tw=120 et nospell :
