//01 Matrix
//Given a matrix consists of 0 and 1, find the distance of the nearest 0 for
//each cell.
//The distance between two adjacent cells is 1.
//Example 1:
//Input:
//0 0 0
//0 1 0
//0 0 0
//Output:
//0 0 0
//0 1 0
//0 0 0
//Example 2:
//Input:
//0 0 0
//0 1 0
//1 1 1
//Output:
//0 0 0
//0 1 0
//1 2 1
//Note:
//The number of elements of the given matrix will not exceed 10,000.
//There are at least one 0 in the given matrix.
//The cells are adjacent in only four directions: up, down, left and right.

//##############################################  BFS ##################################################
vector<pair<int,int> > dir = {{1,0},{-1,0},{0,1},{0,-1}};

vector<vector<int> > updateMatrix(vector<vector<int> >& matrix) {
    if(matrix.empty()) {
      return matrix;
    }
    int m = matrix.size();
    int n = matrix[0].size();
    queue<pair<int,int>> zeros;
    for(int i = 0; i < m; ++i) {
      for(int j = 0; j < n; ++j) {
        if(matrix[i][j] == 0) {
          zeros.push({i,j});
        } else {
          matrix[i][j] = INT_MAX;
        }
      }
    }
    while(!zeros.empty()){
        auto xy = zeros.front();
        zeros.pop();
        int i = xy.first, j = xy.second;
        for(auto d : dir) { //move in all 4 diretions
            int ii = i + d.first, jj = j + d.second;
            if(ii < m && ii >= 0 && jj < n && jj >= 0) {
                if(matrix[ii][jj] >= matrix[i][j] + 1) {
                    matrix[ii][jj] = matrix[i][j] + 1; //update the cost
                    zeros.push({ii,jj});
                }
            }
        }
    }
    return matrix;
}

//##############################################  BFS ##################################################
//In the first sweep, we visit each entry in natural order (L-R) and res[i][j]
//= min(MAX, min(res[i - 1][j], res[i][j - 1]) + 1).
//in the second sweep, we visit each entry in reverse order(R-L) and res[i][j]
//= min(res[i][j], min(res[i + 1][j], res[i][j + 1]) + 1).
vector<vector<int> > updateMatrix(vector<vector<int> >& matrix) {
  if(matrix.empty()) {
    return matrix;
  }
  int m = matrix.size(), n = matrix[0].size();
  vector<vector<int> > res(m,vector<int>(n,0));
  for(int i = 0; i < m; i++) {
     for(int j = 0; j < n; j++) {
         res[i][j] = (matrix[i][j] == 0) ? 0 : m+n;
     }
  }
  //Traverse with natural order L-R and check from left and top
  for(int i = 0; i < m; i++) {
      for(int j = 0; j < n; j++) {
          int left =(j-1 >= 0) ? res[i][j - 1]: res[i][j];
          int top = (i-1 >= 0) ? res[i - 1][j]: res[i][j];
          res[i][j] = min(res[i][j], min(top, left) + 1);
      }
  }

  //Traverse with natural order R-L and check from right to bottom
  for(int i = m-1; i >=0 ; i--) {
    for(int j = n-1; j >= 0; j--) {
      int right = (j+1 < n) ? res[i][j+1]: res[i][j];
      int down = (i+1 < m) ? res[i+1][j]: res[i][j];
      res[i][j] = min(res[i][j], min(down, right) + 1);
    }
  }
  return res;
}

///######################## Same as above w/o extra space  ########################

public List<List<Integer>> updateMatrix(List<List<Integer>> matrix) {
        if (matrix ==null || matrix.size() <= 0 || matrix.get(0).size() <= 0) return matrix;
        for (int i=0; i<matrix.size(); i++) {
            for (int j=0; j<matrix.get(i).size(); j++) {
                if (matrix.get(i).get(j) > 0) {
                    matrix.get(i).set(j, 10000);
                }
            }
        }
        for (int i=0; i<matrix.size(); i++) {
            for (int j=0; j<matrix.get(i).size(); j++) {
                int cur = matrix.get(i).get(j);
                int min = i-1 >=0 ? Math.min( cur, matrix.get(i-1).get(j)) : cur;
                min = j-1 >=0 ? Math.min( min, matrix.get(i).get(j-1)) : min;
                matrix.get(i).set(j, Math.min(cur,min+1));
            }
        }
        for (int i=matrix.size()-1; i>=0; i--) {
            for (int j=matrix.get(i).size()-1; j>=0; j--) {
                int cur = matrix.get(i).get(j);
                int min = i+1 < matrix.size() ? Math.min( cur, matrix.get(i+1).get(j)) : cur;
                min = j+1 < matrix.get(i).size() ? Math.min( min, matrix.get(i).get(j+1)) : min;
                matrix.get(i).set(j, Math.min(cur,min+1));
            }
        }
        return matrix;
    }


public class Solution {
    public List<List<Integer>> updateMatrix(List<List<Integer>> matrix) {
        int m = matrix.size(), n = matrix.get(0).size();
        this.matrix = matrix;
        for (List<Integer> row : matrix)
            for (int j = 0; j < n; j++)
                row.set(j, row.get(j) * 10000);
        for (int i = 0; i < m; i++) {
            for (int j = 1; j < n; j++) {
                relax(i, j, i, j-1);
                relax(i, n-1-j, i, n-j);
            }
        }
        for (int j = 0; j < n; j++) {
            for (int i = 1; i < m; i++) {
                relax(i, j, i-1, j);
                relax(m-1-i, j, m-i, j);
            }
        }
        return matrix;
    }
    void relax(int i, int j, int i0, int j0) {
        matrix.get(i).set(j, Math.min(matrix.get(i).get(j), matrix.get(i0).get(j0) + 1));
    }
    List<List<Integer>> matrix;
}
