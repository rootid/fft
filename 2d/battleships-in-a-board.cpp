//Battleships in a Board
//Given an 2D board, count how many battleships are in it. The battleships are represented with 'X's, empty slots are
//represented with '.'s. You may assume the following rules: You receive a valid board, made of only battleships or
//empty slots.
//Battleships can only be placed horizontally or vertically. In other words, they can only be made of the shape 1xN (1
//row, N columns) or Nx1 (N rows, 1 column), where N can be of any size.  At least one horizontal or vertical cell
//separates between two battleships - there are no adjacent battleships.
//Example:
//X..X
//...X
//...X
//In the above board there are 2 battleships.
//Invalid Example:
//...X
//XXXX
//...X
//This is an invalid board that you will not receive - as battleships will always have a cell separating between them.
//Follow up:
//Could you do it in one-pass, using only O(1) extra memory and without modifying the value of the board?

//######################################### traversal O(mn) #########################################
int countBattleships(vector<vector<char>>& board) {
  int result = 0;
  if(board.empty()) {
      return result;
  }
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[0].size(); j++) {
      //verify adjacent cells : must be empty
      if (board[i][j] == 'X' && (i == 0 || board[i - 1][j] == '.') && (j == 0 || board[i][j - 1] == '.')) {
        result++;
      }
    }
  }
  return result;
}

//######################################### traversal O(mn) #########################################
int countBattleships(vector<vector<char>>& b) {
  int cnt = 0;
  for (int i = 0; i < b.size(); ++i)
    for (int j = 0; j < b[0].size(); ++j)
      cnt += (b[i][j]-'.') && (!i||b[i-1][j]-'X') && (!j||b[i][j-1]-'X');
  return cnt;
}

//######################################### DFS #########################################
class Solution {
public:
    int m, n;
    vector<vector<bool>> flag;
    int go[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    void dfs(vector<vector<char>>& board, int i, int j) {
        if (i < 0 || i >= m || j < 0 || j >= n || board[i][j] == '.' || flag[i][j]) return;
        flag[i][j] = true;
        for (int d = 0; d < 4; ++d) dfs(board, i+go[d][0], j+go[d][1]);
    }

    int countBattleships(vector<vector<char>>& board) {
        if (board.empty()) return 0;
        m = board.size(), n = board[0].size();
        flag.resize(m, vector<bool>(n, false));
        int result = 0;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (board[i][j] == 'X' && !flag[i][j]) {
                    ++result;
                    dfs(board, i, j);
                }
        return result;
    }
};

//######################################### BFS #########################################
class Solution {
public:
    int go[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int countBattleships(vector<vector<char>>& board) {
        if (board.empty()) return 0;
        int m = board.size(), n = board[0].size();
        vector<vector<bool>> flag(m, vector<bool>(n, false));
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 'X' && !flag[i][j]) {
                    ++result;

                    queue<pair<int, int>> q;
                    q.push({i, j});
                    while (!q.empty()) {
                        auto t = q.front(); q.pop();
                        flag[t.first][t.second] = true;
                        for (int d = 0; d < 4; ++d) {
                            int ni = t.first+go[d][0], nj = t.second+go[d][1];
                            if (ni < 0 || ni >= m || nj < 0 || nj >= n || board[ni][nj] == '.' || flag[ni][nj]) continue;
                            q.push({ni, nj});
                        }
                    }
                }
            }
        }
        return result;
    }
};


//######################################### pytonic #########################################
//class Solution(object):
//    def countBattleships(self, board):
//        if len(board) == 0: return 0
//        m, n = len(board), len(board[0])
//        count = 0
//        for i in range(m):
//            for j in range(n):
//                if board[i][j] == 'X'
//                and (i == 0 or board[i-1][j] == '.')
//                and (j == 0 or board[i][j-1] == '.'):
//                    count += 1
//        return count
//
//
//def countBattleships(self, board):
//    total = 0
//    for i in range(len(board)):
//        for j in range(len(board[0])):
//            if board[i][j] == 'X':
//                flag = 1
//                if j > 0 and board[i][j-1] == 'X': flag = 0
//                if i > 0 and board[i-1][j] == 'X': flag = 0
//                total += flag
//    return total

    def countBattleships(self, board):
        count = 0
        for i in xrange(len(board)):
            for j in xrange(len(board[0])):
                # meet X
                # check if it is on border horizontally or has . in the left. i
                # check if it is on top of board or have dot above him.
                # if both check are OK - this is a ship and we have not counted him yet.
                if board[i][j] == 'X' and (i == 0 or board[i-1][j] == '.') and (j==0 or board[i][j-1] == '.'): count += 1
        return coun

// vim: set sw=2 sts=2 tw=120 et nospell :
