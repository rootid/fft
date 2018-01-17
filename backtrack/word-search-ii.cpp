//Word Search II
//Given a 2D board and a list of words from the dictionary, find all words in the board.
//Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.
//For example,
//Given words = ["oath","pea","eat","rain"] and board =
//[
//  ['o','a','a','n'],
//  ['e','t','a','e'],
//  ['i','h','k','r'],
//  ['i','f','l','v']
//]
//Return ["eat","oath"].
//Note:
//You may assume that all inputs are consist of lowercase letters a-z.
//click to show hint.
//You would need to optimize your backtracking to pass the larger test. Could you stop backtracking earlier?
//If the current candidate does not exist in all words' prefix, you could stop backtracking immediately. What kind of data structure could answer such query efficiently? Does a hash table work? Why or why not? How about a Trie? If you would like to learn how to implement a basic trie, please work on this problem: Implement Trie (Prefix Tree) first.
//########################################## Backtrack + Trie + Pruning  #############################################################
class TrieNode{
public:
    bool is_end;
    vector<TrieNode*> children;
    TrieNode(){
        is_end=false;
        children=vector<TrieNode*>(26, NULL);
    }   
};

class Trie{
public:
    TrieNode* getRoot(){ return root;}
    Trie(vector<string>& words){
        root=new TrieNode();
        for(int i=0; i<words.size(); ++i)
            addWord(words[i]);
    }
    void addWord(const string& word){
        TrieNode* cur=root;
        for(int i=0; i<word.size(); ++i){
            int index=word[i]-'a';
            if(cur->children[index]==NULL)   
               cur->children[index]=new TrieNode();
            cur=cur->children[index];    
        }
        cur->is_end=true;
    }

 ~Trie() {
    delTree(root);
  }

 void delTree( TrieNode *root )
  {
    for ( int i = 0; i < 26; ++i ) {
      if ( root->children[i] ) {
        delTree( root->children[i] );
      }
    }
    free( root );
  }
private:
    TrieNode* root;
};


vector<pair<int,int> > dir = {{1,0},{-1,0},{0,1},{0,-1}};
void findWords(vector<vector<char>>& board, int x, int y, TrieNode* root, string word, set<string>& result){
       if(x<0||x>=board.size()||y<0||y>=board[0].size() || board[x][y]==' ') {
         return;
       }
       if(root->children[board[x][y]-'a'] != NULL){ //check the prefix
           word = word + board[x][y];
           root= root->children[board[x][y]-'a'];  //update the root
           if(root->is_end) {  //check complete word exists
             result.insert(word);
           }
           char c=board[x][y];
           board[x][y]=' ';
           for(auto d: dir) {
            findWords(board, x+d.first, y+d.second, root, word, result);
           }
           board[x][y]=c;        
       } 
}

vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
  vector<string> result;
  if(words.empty()) {
    return result;
  }
  Trie* trie = new Trie(words);
  TrieNode* root=trie->getRoot();
  set<string> result_set;
  for(int x=0; x<board.size(); ++x) {
      for(int y=0; y<board[0].size(); ++y) { 
        findWords(board, x, y, root, "", result_set); 
      }
  }
  for(auto it:result_set)    
    result.push_back(it);
  return result;        
}

//#################### Complex number + py
class Solution:
    def findWords(self, board, words):

        root = {}
        for word in words:
            node = root
            for c in word:
                node = node.setdefault(c, {})
            node[None] = True
        board = {i + 1j*j: c
                 for i, row in enumerate(board)
                 for j, c in enumerate(row)}

        found = []
        def search(node, z, word):
            if node.pop(None, None):
                found.append(word)
            c = board.get(z)
            if c in node:
                board[z] = None
                for k in range(4): #//4 directions 
                    search(node[c], z + 1j**k, word + c)
                board[z] = c
        for z in board:
            search(root, z, '')
        return found
