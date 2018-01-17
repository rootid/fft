// Count Paths on a Game Board
// You're given a game board that has m x n squares on it, represented by an m x
// n array. Write a method - countPaths that takes in m and n and returns the
// number of possible paths from the top left corner to the bottom right corner.
// Only down and right directions of movement are permitted.
// Note:
// Your method should output the result in a reasonable amount of time for large
// values of m and n. If you're thinking of using DFS, consider the tree depth
// and branching factor for m and n > 15!
// m = number of rows, n = number of columns
// Example:
// countPaths(m = 2, n = 2) => 2
// as on the following 2x2 Board, the two paths are A->C->D and A->B->D
// A B
// C D

public class CountPathsOnAGameBoard {
  //######################################### DP T,S = O(m*n)
  //#########################################
  public int countPaths(int m, int n) {
    Integer[][] map = new Integer[m][n];
    for (int i = 0; i < m; i++) {
      map[i][0] = 1;
    }
    for (int j = 1; j < n; j++) {
      map[0][j] = 1;
    }
    for (int i = 1; i < m; i++) {
      for (int j = 1; j < n; j++) {
        map[i][j] = map[i - 1][j] + map[i][j - 1];
      }
    }
    return map[m - 1][n - 1];
  }
}
}
