import java.util.*;
// You're given a 2D Boggle Board which contains an m x n matrix of chars -
// char[][] board, and a fast, electronic Dictionary in the form of a Prefix
// Tree or Trie. Write a method - boggleSearchWithDict that searches the Boggle
// Board for words in the dictionary. Your method should return an
// alphabetically sorted ArrayList of words that are present on the board as
// well as in the dictionary. Words on the board can be constructed with
// sequentially adjacent letters, where adjacent letters are horizontal or
// vertical neighbors (not diagonal). Also, each letter on the Boggle Board must
// be used only once. Your program should run in a reasonable amount of time (at
// max about 50 ms for each test case) and shouldn't time out.
// Note: The Trie has two built-in methods that you'll find useful for this
// problem - searchWord(String s) and searchPrefix(String s). These will return
// true if the complete word or prefix are found in the dictionary,
// respectively.
// Example:
// Input Board :
//{
//    {A, O, L},
//    {D, E, L},
//    {G, H, I},
//}
// Dictionary : [HELLO, HOW, ARE, YOU] (as a Trie)
// Output: [HELLO]

public class BoggleWithElectronicDictionary {
  //#### Xtra space  + StringBuilder ####
  public ArrayList<String> boggleSearchWithDict(char[][] board,
                                                Trie dictionary) {
    ArrayList<String> result = new ArrayList<>();
    int m = board.length;
    int n = board[0].length;
    if (n == 0) return result;
    Set<Integer> visited = new HashSet<>();
    TreeSet<String> imdStore = new TreeSet<>();
    StringBuilder sb = new StringBuilder();
    for (int i = 0; i < m; i++)
      for (int j = 0; j < n; j++) {
        if (dictionary.searchPrefix("" + board[i][j])) {
          boggleHelper(board, i, j, dictionary, visited, sb, imdStore);
          visited.add(i * n + j);
        }
      }
    result.addAll(imdStore);
    return result;
  }

  private void boggleHelper(char[][] board, int x, int y, Trie dict,
                            Set<Integer> visited, StringBuilder sb,
                            TreeSet<String> result) {
    int m = board.length;
    int n = board[0].length;
    if (dict.searchWord(sb.toString())) {
      result.add(sb.toString());  // prep,preparation
    }
    if ((x >= m || y >= n) || (x < 0 || y < 0) || visited.contains(x * n + y))
      return;
    if (sb.length() == 0 || dict.searchPrefix(sb.toString())) {
      sb.append(board[x][y]);
      boggleHelper(board, x - 1, y, dict, visited, sb, result);
      boggleHelper(board, x, y - 1, dict, visited, sb, result);
      boggleHelper(board, x + 1, y, dict, visited, sb, result);
      boggleHelper(board, x, y + 1, dict, visited, sb, result);
      sb.setLength(sb.length() - 1);
    }
  }

  //#### In place update ####
  public ArrayList<String> boggleSearchWithDictGood(char[][] board,
                                                    Trie dictionary) {
    Set<String> words = new TreeSet<String>();

    for (int i = 0; i < board.length; i++) {
      for (int j = 0; j < board[i].length; j++) {
        if (dictionary.searchPrefix("" + board[i][j])) {
          words = boggleSearchWithDict(board, dictionary, words, i, j, "");
        }
      }
    }

    return new ArrayList<String>(words);
  }

  private Set<String> boggleSearchWithDict(char[][] board, Trie dictionary,
                                           Set<String> words, int i, int j,
                                           String wordSoFar) {
    if (i < 0 || j < 0 || i >= board.length || j >= board[i].length)
      return words;
    char c = board[i][j];
    wordSoFar += c;
    board[i][j] = '*';
    if (dictionary.searchWord(wordSoFar)) {
      words.add(wordSoFar);
    }
    if (dictionary.searchPrefix(wordSoFar)) {
      words =
          boggleSearchWithDict(board, dictionary, words, i + 1, j, wordSoFar);
      words =
          boggleSearchWithDict(board, dictionary, words, i - 1, j, wordSoFar);
      words =
          boggleSearchWithDict(board, dictionary, words, i, j + 1, wordSoFar);
      words =
          boggleSearchWithDict(board, dictionary, words, i, j - 1, wordSoFar);
    }
    board[i][j] = c;
    return words;
  }

  public static void main(String[] args) {
    BoggleWithElectronicDictionary bg = new BoggleWithElectronicDictionary();
    // bg.boggleSearchWithDict();
  }
}
