// Boggle with Paper Dictionary
// You're given a 2D Boggle Board which contains an m x n matrix of chars -
// char[][] board, and a rudimentary, paper Dictionary in the form of an
// ArrayList of close to 10,000 words. Write a method - boggleByot that searches
// the Boggle Board for words in the dictionary. Your method should return an
// alphabetically sorted ArrayList of words that are present on the board as
// well as in the dictionary. Words on the board can be constructed with
// sequentially adjacent letters, where adjacent letters are horizontal or
// vertical neighbors (not diagonal). Also, each letter on the Boggle Board must
// be used only once.
// Note:
// Your program should run in a reasonable amount of time - about a few
// milliseconds for each test case.
// Example:
// Input Board :
//{
//    {A, O, L},
//    {D, E, L},
//    {G, H, I},
//}
// Dictionary : [HELLO, HOW, ARE, YOU] (as a Trie)
// Output: [HELLO]

public class BoggleWithPaperDictionary {
  class TrieNode {
    Character c;
    Boolean isLeaf = false;
    HashMap<Character, TrieNode> children = new HashMap<>();
    public TrieNode() {}
    public TrieNode(Character c) { this.c = c; }
  }

  class Trie {
    private TrieNode root;

    public Trie() { this.root = new TrieNode(); }

    public void insertWord(String word) {
      TrieNode cur = root;
      HashMap<Character, TrieNode> children = cur.children;
      for (int i = 0; i < word.length(); i++) {
        char c = word.charAt(i);
        if (children.containsKey(c)) {
          cur = children.get(c);
        } else {
          TrieNode n = new TrieNode(c);
          children.put(c, n);
          cur = n;
        }
        children = cur.children;

        if (i == word.length() - 1) cur.isLeaf = true;
      }
    }

    public Boolean searchWord(String word) {
      TrieNode cur = root;
      HashMap<Character, TrieNode> children = cur.children;
      for (int i = 0; i < word.length(); i++) {
        char c = word.charAt(i);
        if (children.containsKey(c)) {
          cur = children.get(c);
          children = cur.children;
        } else
          return false;
      }
      return cur.isLeaf;
    }

    public Boolean searchPrefix(String word) {
      TrieNode cur = root;
      HashMap<Character, TrieNode> children = cur.children;
      for (int i = 0; i < word.length(); i++) {
        char c = word.charAt(i);
        if (children.containsKey(c)) {
          cur = children.get(c);
          children = cur.children;
        } else {
          return false;
        }
      }
      return true;
    }
  }

  public ArrayList<String> boggleByot(char[][] board,
                                      ArrayList<String> dictionary) {
    Trie prefixTree = new Trie();
    for (String word : dictionary) {
      prefixTree.insertWord(word);
    }
    TreeSet<String> outputHolder = new TreeSet<>();
    int rows = board.length;
    int cols = board[0].length;
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        search(i, j, board, prefixTree, "", outputHolder);
      }
    }
    return new ArrayList<>(outputHolder);
  }

  public void search(int r, int c, char[][] board, Trie prefixTree,
                     String prefix, TreeSet<String> outputHolder) {
    int rows = board.length;
    int cols = board[0].length;

    // Terminating Conditions
    if (r > rows - 1                         // Out of Bounds
        || r < 0                             // Out of Bounds
        || c > cols - 1                      // Out of Bounds
        || c < 0                             // Out of Bounds
        || !prefixTree.searchPrefix(prefix)  // Not matching pattern
        || board[r][c] == '@') {             // Visited
      return;
    }
    char ch = board[r][c];
    String s = prefix + ch;
    if (prefixTree.searchWord(s)) {
      outputHolder.add(s);  // Add to the treeSet
    }

    board[r][c] = '@';  // Mark the board node as visited

    search(r - 1, c, board, prefixTree, s, outputHolder);  // Check Up
    search(r + 1, c, board, prefixTree, s, outputHolder);  // Check Down
    search(r, c - 1, board, prefixTree, s, outputHolder);  // Check Left
    search(r, c + 1, board, prefixTree, s, outputHolder);  // Check Right

    board[r][c] = ch;  // Unmark the board node
  }

  //#### TODO ####
  public ArrayList<String> boggleByot(char[][] board,
                                      ArrayList<String> dictionary) {
    Trie trie = new Trie();
    for (String s : dictionary) {
      trie.insertWord(s);
    }
    TreeSet<String> set = new TreeSet<>();
    for (int i = 0; i < board.length; i++) {
      for (int j = 0; j < board[0].length; j++) {
        searchBoard(board, "", i, j, trie, set);
      }
    }
    return new ArrayList<String>(set);
  }

  public void searchBoard(char[][] board, String s, int i, int j, Trie trie,
                          TreeSet<String> set) {
    if (i < 0 || i >= board.length || j < 0 || j >= board[0].length ||
        board[i][j] == '#') {
      return;
    }
    String current = s + board[i][j];
    if (!trie.searchPrefix(current)) {
      return;
    }
    if (trie.searchWord(current)) {
      set.add(current);
    }
    char temp = board[i][j];
    board[i][j] = '#';
    searchBoard(board, s + temp, i - 1, j, trie, set);
    searchBoard(board, s + temp, i + 1, j, trie, set);
    searchBoard(board, s + temp, i, j - 1, trie, set);
    searchBoard(board, s + temp, i, j + 1, trie, set);
    board[i][j] = temp;
  }

  class TrieNode {
    Character c;

    Boolean isLeaf = false;

    HashMap<Character, TrieNode> children = new HashMap<>();

    public TrieNode(){};

    public TrieNode(Character c) { this.c = c; };
  }

  class Trie {
    private TrieNode root;

    public Trie() { this.root = new TrieNode(Character.MIN_VALUE); };

    public void insertWord(String word) {
      TrieNode node = root;
      for (char c : word.toCharArray()) {
        if (!node.children.containsKey(c)) {
          TrieNode next = new TrieNode(c);
          node.children.put(c, next);
        }
        node = node.children.get(c);
      }
      node.isLeaf = true;
    };

    public Boolean searchWord(String word) {
      TrieNode node = root;
      for (char c : word.toCharArray()) {
        if (!node.children.containsKey(c)) {
          return false;
        }
        node = node.children.get(c);
      }
      return node.isLeaf;
    };

    public Boolean searchPrefix(String word) {
      TrieNode node = root;
      for (char c : word.toCharArray()) {
        if (!node.children.containsKey(c)) {
          return false;
        }
        node = node.children.get(c);
      }
      return true;
    };
  }
}
