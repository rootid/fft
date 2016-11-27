
//Number of Islands
//Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.
//Example 1:
//11110
//11010
//11000
//00000
//Answer: 1
//Example 2:
//11000
//11000
//00100
//00011
//Answer: 3


void helper(vector<vector<char> >& a, int i, int j, int m, int n) {
     a[i][j] = 0;
     if (i > 0 && a[i-1][j]=='1') helper(a,i-1,j,m,n);
     if (j > 0 && a[i][j-1]=='1') helper(a,i,j-1,m,n);
     if (i < m-1 && a[i+1][j]=='1') helper(a,i+1,j,m,n);
     if (j < n-1 && a[i][j+1]=='1') helper(a,i,j+1,m,n);
}

int numIslands(vector<vector<char>> &grid) {
     int m = grid.size();
     if (m==0) return 0;
     int n = grid[0].size();
     int count = 0;
     for (int i = 0; i < m; ++i) {
         for (int j = 0; j < n; ++j) {
             if (grid[i][j]=='1') {
                 helper(grid,i,j,m,n);
                 count++;
             }
         }
     }
     return count;
}
 
