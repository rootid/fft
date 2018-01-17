//Diagonal Traverse
//Given a matrix of M x N elements (M rows, N columns), return all elements of the matrix in diagonal order as shown in the below image.
//Example:
//Input:
//[
// [ 1, 2, 3 ],
// [ 4, 5, 6 ],
// [ 7, 8, 9 ]
//]
//Output:  [1,2,4,7,5,3,6,8,9]
//Explanation:
//Note:
//The total number of elements of the given matrix will not exceed 10,000.

//########################## Good ########################## 
vector<int> findDiagonalOrder(vector<vector<int> >& matrix) {
        int nrow = matrix.size();
        int ncol = matrix.empty() ? 0 : matrix[0].size();
        vector<int> out;
        for (int d=0; d<nrow+ncol-1; d++) {
            if (d%2) {
              for (int i=max(0,d-ncol+1); i<min(d+1,nrow); i++) {
                out.push_back(matrix[i][d-i]);
              }
            } else {
              for (int i=max(0,d-nrow+1); i<min(d+1,ncol); i++) {
                out.push_back(matrix[d-i][i]);
              }
            }
        }
        return out;
}
//##################### Iterative ##################### 
vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
     vector<int> res;
     if (matrix.empty()) return res;
     int direct = 1; // 1 for up diag direction, 0 for down diag direction
     for (int j = 0; j < matrix[0].size(); ++j) {
         diag(matrix, res, 0, j, direct);
     }
     for (int i = 1; i < matrix.size(); ++i) {
         diag(matrix, res, i, matrix[0].size() - 1, direct);
     }
     return res;
 }
 
 void diag(vector<vector<int>>& matrix, vector<int>& res, int i, int j, int& direct) {
     if (direct == 1) { // if upward
         pair<int, int> start;
         if (i + j < matrix.size()) start = make_pair(i + j, 0);
         else start = make_pair(matrix.size() - 1, i + j - matrix.size() + 1);
         for (int row = start.first, col = start.second; col <= j; --row, ++col) res.push_back(matrix[row][col]);
     } else { // downward
         while (i <= matrix.size() - 1 && j >= 0) res.push_back(matrix[i++][j--]);
     }
     direct ^= 1;
 }
