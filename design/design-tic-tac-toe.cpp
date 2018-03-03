//Design Tic-Tac-Toe
//Design a Tic-tac-toe game that is played between two players on a n x n grid.
//You may assume the following rules:
//A move is guaranteed to be valid and is placed on an empty block.
//Once a winning condition is reached, no more moves is allowed.
//A player who succeeds in placing n of their marks in a horizontal, vertical,
//or diagonal row wins the game.
//Example:
//Given n = 3, assume that player 1 is "X" and player 2 is "O" in the board.
//TicTacToe toe = new TicTacToe(3);
//toe.move(0, 0, 1); -> Returns 0 (no one wins)
//|X| | |
//| | | |    // Player 1 makes a move at (0, 0).
//| | | |
//toe.move(0, 2, 2); -> Returns 0 (no one wins)
//|X| |O|
//| | | |    // Player 2 makes a move at (0, 2).
//| | | |
//toe.move(2, 2, 1); -> Returns 0 (no one wins)
//|X| |O|
//| | | |    // Player 1 makes a move at (2, 2).
//| | |X|
//toe.move(1, 1, 2); -> Returns 0 (no one wins)
//|X| |O|
//| |O| |    // Player 2 makes a move at (1, 1).
//| | |X|
//toe.move(2, 0, 1); -> Returns 0 (no one wins)
//|X| |O|
//| |O| |    // Player 1 makes a move at (2, 0).
//|X| |X|
//toe.move(1, 0, 2); -> Returns 0 (no one wins)
//|X| |O|
//|O|O| |    // Player 2 makes a move at (1, 0).
//|X| |X|
//toe.move(2, 1, 1); -> Returns 1 (player 1 wins)
//|X| |O|
//|O|O| |    // Player 1 makes a move at (2, 1).
//|X|X|X|
//Follow up:
//Could you do better than O(n2) per move() operation?
//Hint:
//Could you trade extra space such that move() operation can be done in O(1)?
//You need two arrays: int rows[n], int cols[n], plus two variables: diagonal,
//anti_diagonal.
//Solution:
//Use addtional arrays rows[n], cols[n] and two varialbes diagonal,
//anti_diagonal to mark the number of Xs and Os.


//############################ ############################
//if ((row - col) == 0) diag += toAdd;
//if ((row + col) == (n - 1)) antidiag += toAdd;
//On an n x n matrix, you can compute the (anti-)diagonal of a cell by using x
//+ y or x - y. Since given y = mx + b, and m = {1, -1}, then y = {1, -1}x + b,
//thus y + {1, -1}x = b. If 'b' = 0 then it's the diagonal starting from the
//bottom, if 'b' = n then it's the diagonal starting from the top.
//And of course, the 'b' value creates an equivalency relation, which means you
//can generalize this property to partition all diagonals using the 'b' value.
//So two spots having the same b value are on the same diagonal.
public class TicTacToe {
  private int[] rows;
  private int[] cols;
  private int diagonal;
  private int antiDiagonal;

  /** Initialize your data structure here. */
  public TicTacToe(int n) {
      rows = new int[n];
      cols = new int[n];
  }

  /** Player {player} makes a move at ({row}, {col}).
      @param row The row of the board.
      @param col The column of the board.
      @param player The player, can be either 1 or 2.
      @return The current winning condition, can be either:
              0: No one wins.
              1: Player 1 wins.
              2: Player 2 wins. */
  public int move(int row, int col, int player) {
      int toAdd = player == 1 ? 1 : -1;

      rows[row] += toAdd;
      cols[col] += toAdd;
      if (row == col)
      {
          diagonal += toAdd;
      }

      if (col == (cols.length - row - 1))
      {
          antiDiagonal += toAdd;
      }

      int size = rows.length;
      if (Math.abs(rows[row]) == size ||
          Math.abs(cols[col]) == size ||
          Math.abs(diagonal) == size  ||
          Math.abs(antiDiagonal) == size)
      {
          return player;
      }

      return 0;
  }
}

//########################################################### Good ###########################################################
//Add +/- 1, check with /n
class TicTacToe {
public:
    TicTacToe(int n) : n(n), rows(n), cols(n), diag(0), diag2(0) {}

    int move(int row, int col, int player) {
        int add = player == 1 ? 1 : -1;
        if ((rows[row] += add) / n ||
            (cols[col] += add) / n ||
            row == col && (diag += add) / n ||
            row + col == n - 1 && (diag2 += add) / n)
            return player;
        return 0;
    }

private:
    int n, diag, diag2;
    vector<int> rows, cols;
};

//########################################################### Good ###########################################################
class TicTacToe {
private:
    //count parameter: player 1 + : player 2: -
    vector<int> rowJudge;
    vector<int> colJudge;
    int diag, anti;
    int total;
public:
    /** Initialize your data structure here. */

    TicTacToe(int n):total(n), rowJudge(n), colJudge(n),diag(0),anti(0){}

    int move(int row, int col, int player) {
        int add = player == 1 ? 1 : -1;
        diag += row == col ? add : 0;
        anti += row == total - col - 1 ? add : 0;
        rowJudge[row] += add;
        colJudge[col] += add;
        if(abs(rowJudge[row]) == total || abs(colJudge[col]) == total || abs(diag) == total || abs(anti) == total)
            return player;
        return 0;
    }
};


class TicTacToe {
public:
    TicTacToe(int n) : sz(n) {
        rows.resize(n, 0), cols.resize(n, 0);
        diagonal = anti_diagonal = 0;
    }

    int move(int row, int col, int player) {
        if (player == 1) {
            ++rows[row], ++cols[col];
            if (row == col)
                ++diagonal;
            if (row == sz - 1 - col)
                ++anti_diagonal;
            if (rows[row] == sz || cols[col] == sz || diagonal == sz || anti_diagonal == sz)
                return 1;
        }
        else {
            --rows[row], --cols[col];
            if (row == col)
                --diagonal;
            if (row == sz - 1 - col)
                --anti_diagonal;
            if (rows[row] == -sz || cols[col] == -sz || diagonal == -sz || anti_diagonal == -sz)
                return 2;
        }
        return 0;
    }

private:
    vector<int> rows, cols;
    int diagonal, anti_diagonal;
    int sz;
};

//########################################################### Ugly  ###########################################################
class TicTacToe {
private:
    //status:
    // 0: no one fill
    // 1 or 2: player fill
    //-1 : invalid
    //pair:
    //first:player, second:count
    vector<pair<int,int>> rowJudge;
    vector<pair<int,int>> colJudge;
    pair<int,int> diag, anti;
    int total;
public:
    /** Initialize your data structure here. */
    TicTacToe(int n):total(n), rowJudge(n), colJudge(n){}

    /** Player {player} makes a move at ({row}, {col}).
        @param row The row of the board.
        @param col The column of the board.
        @param player The player, can be either 1 or 2.
        @return The current winning condition, can be either:
                0: No one wins.
                1: Player 1 wins.
                2: Player 2 wins. */
    int move(int row, int col, int player) {
        if(rowJudge[row].first == 0 || rowJudge[row].first == player){
            rowJudge[row].first = player;
            rowJudge[row].second++;
            if(rowJudge[row].second == total){
                return player;
            }
        }
        else {
            rowJudge[row].first = -1;
        }

        if(colJudge[col].first == 0 || colJudge[col].first == player){
            colJudge[col].first = player;
            colJudge[col].second++;
            if(colJudge[col].second == total){
                return player;
            }
        }
        else {
            colJudge[col].first = -1;
        }


        if(row == col){
            if(diag.first == 0 || diag.first == player){
                diag.first = player;
                diag.second++;
                if(diag.second == total){
                    return player;
                }
            }
            else{
                diag.first = -1;
            }
        }
        if(row + col == total - 1){
            if(anti.first == 0 || anti.first == player){
                anti.first = player;
                anti.second++;
                if(anti.second == total){
                    return player;
                }
            }
            else{
                anti.first = -1;
            }
        }
        return 0;
    }
};

//########################### 6*n X 3 ###########################
public class TicTacToe {
    public TicTacToe(int n) {
        count = new int[6*n][3];
    }

    public int move(int row, int col, int player) {
        int n = count.length / 6;
        for (int x : new int[]{row, n+col, 2*n+row+col, 5*n+row-col})
            if (++count[x][player] == n)
                return player;
        return 0;
    }

    int[][] count;
}

//["TicTacToe","move","move","move","move","move","move","move"]
//[[3],[0,0,1],[0,2,2],[2,2,1],[1,1,2],[2,0,1],[1,0,2],[2,1,1]]


//############################ Pytonic  ############################

//class TicTacToe(object):
//    def __init__(self, n):
//        count = collections.Counter()
//        def move(row, col, player):
//            for i, x in enumerate((row, col, row+col, row-col)):
//                count[i, x, player] += 1
//                if count[i, x, player] == n:
//                    return player
//            return 0
//        self.move = move
//
//
//
//Record the number of moves for each rows, columns, and two diagonals.
//For each move, we -1 for each player 1's move and +1 for player 2's move.
//Then we just need to check whether any of the recored numbers equal to n or
//-n.
//class TicTacToe(object):
//
//    def __init__(self, n):
//        self.row, self.col, self.diag, self.anti_diag, self.n = [0] * n, [0] * n, 0, 0, n
//
//    def move(self, row, col, player):
//        offset = player * 2 - 3
//        self.row[row] += offset
//        self.col[col] += offset
//        if row == col:
//            self.diag += offset
//        if row + col == self.n - 1:
//            self.anti_diag += offset
//        if self.n in [self.row[row], self.col[col], self.diag, self.anti_diag]:
//            return 2
//        if -self.n in [self.row[row], self.col[col], self.diag, self.anti_diag]:
//            return 1
//        return 0
//
//################################################## For k players ##################################################
//public class TicTacToe {
//
//    int[][] rows;
//    int[][] cols;
//    int[][] diags;
//    int n;
//    int playerNum = 2; // can be replaced with n players
//
//    public TicTacToe(int n) {
//        this.rows = new int[n][playerNum];
//        this.cols = new int[n][playerNum];
//        this.diags = new int[2][playerNum];
//        this.n = n;
//    }
//
//    public int move(int row, int col, int player) {
//        rows[row][player-1] ++;
//        cols[col][player-1] ++;
//        diags[0][player-1] += row - col == 0 ? 1 : 0;
//        diags[1][player-1] += row + col == n - 1 ? 1 : 0;
//        if (rows[row][player - 1] == n || cols[col][player - 1] == n // n could be placed with K
//                || diags[0][player - 1] == n || diags[1][player - 1] == n) {
//            return player;
//        }
//        return 0;
//    }
//}
