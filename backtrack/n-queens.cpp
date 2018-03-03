//N-Queens
//The n-queens puzzle is the problem of placing n queens on an n×n chessboard
//such that no two queens attack each other.
//Given an integer n, return all distinct solutions to the n-queens puzzle.
//Each solution contains a distinct board configuration of the n-queens'
//placement, where 'Q' and '.' both indicate a queen and an empty space
//respectively.
//For example,
//There exist two distinct solutions to the 4-queens puzzle:
//[
// [".Q..",  // Solution 1
//  "...Q",
//  "Q...",
//  "..Q."],
// ["..Q.",  // Solution 2
//  "Q...",
//  "...Q",
//  ".Q.."]
//]
//
//################################################### Solve with Columns  ###################################################

class Solution {
public:
  vector<vector<string>> solveNQueens(int n) {
      vector<vector<string> > res;
    vector<string> temp(n, string(n,'.'));
    int dp[n];
    helper(res, temp, dp, 0, n);
    return res;
  }

private:
  void helper(vector<vector<string> > &res, vector<string> &temp, int dp[], int row, int n){
    if(row==n){
      res.push_back(temp);
      return;
    }
    for(int col=0;col<n;++col){
      if(valid(dp, row, col, n)){
        dp[row]=col;
        temp[row][col]='Q';
        helper(res, temp, dp, row+1,n);
        temp[row][col]='.';
      }
    }
  }

  bool valid(int dp[], int row, int col, int n){
    for(int i=0;i<row;++i){
      if(dp[i]==col || abs(row-i)==abs(dp[i]-col)){
        return false;
      }
    }
    return true;
  }
};


//################################################### Iteration ###################################################
bool ok(vector<int> &col, int c, int idx) {
// Validates last queen with all previous queens.
    for (int i = 0; i < idx; i++)
            if (col[i] == c || abs(col[i] - c) == abs(i - idx))
                return false; // Clash!
    return true;
}
vector<vector<string> > solveNQueens(int n) {
    vector<int> col(n, 0);
    vector<vector<string> > ans;
    int row = 0;
    while (1) {
        if (row == n) {
            // Generate string for this solution.
            string str;
            for (int i = 0; i < n; i++) str = str + ".";
            vector<string> t(n, str);
            for (int i = 0; i < n; i++) t[col[i]][i] = 'Q';
            ans.push_back(t);

            col[--row]++; // go back to previous row and increment that queen by 1 column.
        }
        else if (col[row] == n) {
            col[row--] = 0;       // Reset this queen to column 0.
            if (row == -1) break; // all cases checked! :)
            col[row]++;           // go back to previous row and increment that queen by 1 column.
        }
        else if (!ok(col, col[row], row)) {
            col[row]++; // problem at this column, so go to next column.
        }
        else row++;   // everything's perfect, lets go to queen in next row.
    }
    return ans;
}

//################################################### bitmask + 90,45,135 (1-array) + Space optimization ###################################################
class Solution {
public:
    vector<vector<string> > solveNQueens(int n) {
        vector<vector<string> > res;
        vector<string> nQueens(n, string(n, '.'));
        /*
        flag[0] to flag[n - 1] to indicate if the column had a queen before.
        flag[n] to flag[3 * n - 2] to indicate if the 45° diagonal had a queen before.
        flag[3 * n - 1] to flag[5 * n - 3] to indicate if the 135° diagonal had a queen before.
        */
        vector<int> flag(5 * n - 2, 1);
        solveNQueens(res, nQueens, flag, 0, n);
        return res;
    }
private:
    void solveNQueens(vector<vector<string> > &res, vector<string> &nQueens, vector<int> &flag, int row, int &n) {
        if (row == n) {
            res.push_back(nQueens);
            return;
        }
        for (int col = 0; col != n; ++col)
            if (flag[col] && flag[n + row + col] && flag[4 * n - 2 + col - row]) {
                flag[col] = flag[n + row + col] = flag[4 * n - 2 + col - row] = 0;
                nQueens[row][col] = 'Q';
                solveNQueens(res, nQueens, flag, row + 1, n);
                nQueens[row][col] = '.';
                flag[col] = flag[n + row + col] = flag[4 * n - 2 + col - row] = 1;
            }
    }
};
//################################################### bitmask + 90,45,135 (3-arrays)  ###################################################
/**    | | |                / / /             \ \ \
  *    O O O               O O O               O O O
  *    | | |              / / / /             \ \ \ \
  *    O O O               O O O               O O O
  *    | | |              / / / /             \ \ \ \
  *    O O O               O O O               O O O
  *    | | |              / / /                 \ \ \
  *   3 columns        5 45° diagonals     5 135° diagonals    (when n is 3)
  */
class Solution {
public:
    vector<vector<string> > solveNQueens(int n) {
        vector<vector<string> > res;
        vector<string> nQueens(n, string(n, '.'));
        vector<int> flag_col(n, 1), flag_45(2 * n - 1, 1), flag_135(2 * n - 1, 1);
        solveNQueens(res, nQueens, flag_col, flag_45, flag_135, 0, n);
        return res;
    }
private:
    void solveNQueens(vector<vector<string> > &res, vector<string> &nQueens, vector<int> &flag_col, vector<int> &flag_45, vector<int> &flag_135, int row, int &n) {
        if (row == n) {
            res.push_back(nQueens);
            return;
        }
        for (int col = 0; col != n; ++col) {
            if (flag_col[col] && flag_45[row + col] && flag_135[n - 1 + col - row]) {
                flag_col[col] = flag_45[row + col] = flag_135[n - 1 + col - row] = 0;
                nQueens[row][col] = 'Q';
                solveNQueens(res, nQueens, flag_col, flag_45, flag_135, row + 1, n);
                nQueens[row][col] = '.';
                flag_col[col] = flag_45[row + col] = flag_135[n - 1 + col - row] = 1;
            }
        }
    }
};



//################################################### BT + 90,45,135  ###################################################
class Solution {
public:
    vector<vector<string> > solveNQueens(int n) {
        vector<vector<string> > res;
        vector<string> nQueens(n, string(n, '.'));
        solveNQueens(res, nQueens, 0, n);
        return res;
    }
private:
    void solveNQueens(vector<vector<string> > &res, vector<string> &nQueens, int row, int &n) {
        if (row == n) {
            res.push_back(nQueens);
            return;
        }
        for (int col = 0; col != n; ++col)
            if (isValid(nQueens, row, col, n)) {
                nQueens[row][col] = 'Q';
                solveNQueens(res, nQueens, row + 1, n);
                nQueens[row][col] = '.';
            }
    }
    bool isValid(vector<string> &nQueens, int row, int col, int &n) {
        //check if the column had a queen before.
        for (int i = 0; i != row; ++i)
            if (nQueens[i][col] == 'Q')
                return false;
        //check if the 45° diagonal had a queen before.
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j)
            if (nQueens[i][j] == 'Q')
                return false;
        //check if the 135° diagonal had a queen before.
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; --i, ++j)
            if (nQueens[i][j] == 'Q')
                return false;
        return true;
    }
};



//####################################################  pytonic ####################################################

//Use the DFS helper function to find solutions recursively. A solution will be
//found when the length of queens is equal to n ( queens is a list of the
//indices of the queens).
//In this problem, whenever a location (x, y) is occupied, any other locations
//(p, q) where p + q == x + y or p - q == x - y would be invalid. We can use
//this information to keep track of the indicators (xy_dif and xy_sum ) of the
//invalid positions and then call DFS recursively with valid positions only.
//
//At the end, we convert the result (a list of lists; each sublist is the
//indices of the queens) into the desire format.
//####################################################  Recursive ####################################################
//def solveNQueens(self, n):
//    def DFS(queens, xy_dif, xy_sum):
//        p = len(queens)
//        if p==n:
//            result.append(queens)
//            return None
//        for q in range(n):
//            if q not in queens and p-q not in xy_dif and p+q not in xy_sum:
//                DFS(queens+[q], xy_dif+[p-q], xy_sum+[p+q])
//    result = []
//    DFS([],[],[])
//    return [ ["."*i + "Q" + "."*(n-i-1) for i in sol] for sol in result]


//####################################################  Iterative ####################################################
//def solveNQueens(self, n):
//        results = [[]]
//        for i in range(n):
//            tmp = []
//            for ares in results:
//                newLine = [' '] * n
//                for ki, kj in enumerate(ares):
//                    newLine[kj] = '.'
//                    if 0 <= ki + kj - i < n:  newLine[ki + kj - i] = '.' # i + j == ki + kj
//                    if 0 <= i + kj - ki < n:  newLine[i + kj - ki] = '.' # j - i == kj - ki
//
//                for j in range(n):
//                    if newLine[j] == '.': continue
//                    tmp.append(ares+[j])
//            results = tmp
//        return [['.'*j + 'Q' + '.'*(n-j-1) for j in ares] for ares in results]
//
//
//####################################################  Pytonic with lambda  ####################################################
//class Solution:
//def dfs(self,ret,pos,row,n):
//    if row == n:
//        ret.append([''.join('Q' if pos[i] == j else '.'for j in range(n)) for i in range(n)])
//        return
//    for j in range(n):
//        if j not in pos \
//            and all(map(lambda r: pos[r] != j - (row - r), range(row))) \
//            and all(map(lambda r: pos[r] != j + (row - r), range(row))):
//                pos.append(j)
//                self.dfs(ret,pos,row+1,n)
//                pos.pop()
//
//# @return a list of lists of string
//def solveNQueens(self, n):
//    ret=[]
//    self.dfs(ret,[],0,n)
//    return ret
