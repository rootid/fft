//Follow up for "Unique Paths":
//Now consider if some obstacles are added to the grids. How many unique paths would there be?
//An obstacle and empty space is marked as 1 and 0 respectively in the grid.
//For example,
//There is one obstacle in the middle of a 3x3 grid as illustrated below.
//[
//  [0,0,0],
//  [0,1,0],
//  [0,0,0]
//]
//The total number of unique paths is 2.
//Note: m and n will be at most 100.

//##################### O(m*n) ##################### 
public int uniquePathsWithObstacles(int[][] obstacleGrid) {
    int m = obstacleGrid.length;
    if(m == 0) return m;
    int n = obstacleGrid[0].length;
    if(obstacleGrid[0][0] == 1) return 0;
    int[][] path = new int[m+1][n+1];
    path[0][1] = 1;
    for(int i=1;i<=m;i++)
       for(int j=1;j<=n;j++)
           if(obstacleGrid[i-1][j-1] == 0) path[i][j] = path[i-1][j] + path[i][j-1]; //look for obstacles backwards
    return path[m][n];
}

//##################### O(m*n) ##################### 
public int uniquePathsWithObstacles(int[][] obstacleGrid) {
    int m = obstacleGrid.length;
    if(m == 0) return m;
    int n = obstacleGrid[0].length;
    if(obstacleGrid[0][0] == 1) return 0;
    int[][] path = new int[m][n];
    for(int i=0;i<m;i++) {
        if(obstacleGrid[i][0] == 1) break;
        path[i][0] = 1;
    }       
    for(int j=0;j<n;j++) {
        if(obstacleGrid[0][j] == 1) break;
        path[0][j] = 1;
    }
    for(int i=1;i<m;i++)
       for(int j=1;j<n;j++)
           if(obstacleGrid[i][j] == 0) path[i][j] = path[i-1][j] + path[i][j-1];
    return path[m-1][n-1];
}


//##################### O(m*n) ##################### 
int uniquePathsWithObstacles(vector<vector<int> >& obstacleGrid) { 
  //base case : verification
  if(obstacleGrid.empty()) {
    return 0;
  }
  int m = obstacleGrid.size(), n = obstacleGrid[0].size();
  vector<vector<int> > path(m + 1, vector<int> (n + 1, 0));
  //base case : verification
  if(obstacleGrid[0][0] == 1) {
    return 0;
  }
  //obstacleGrid[0][0] == 0 
  path[0][1] = 1; 
  for (int i = 1; i <= m; i++) { 
    for (int j = 1; j <= n; j++) { 
      if (!obstacleGrid[i - 1][j - 1]) { 
        path[i][j] = path[i - 1][j] + path[i][j - 1]; 
      } 
    }
  }
  return path[m][n];
}

//##################### Space optimized ##################### 
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) { 
  int m = obstacleGrid.size();
  int n = obstacleGrid[0].size();
  vector<int> cur(m, 0); //holds # of paths
  //Scan first column
  for (int i = 0; i < m; i++) {
      if (obstacleGrid[i][0] == 0) {
          cur[i] = 1;
      }
      else break;
  }
  //Scan 2-n columns
  for (int j = 1; j < n; j++) {
      bool is_reachable = false;
      if (obstacleGrid[0][j] == 1) {
          cur[0] = 0;
      } else {
        is_reachable = true;
      }
      //scan all rows eg. all 1's in 2nd column
      for (int i = 1; i < m; i++) {
          //no obstacle
          if (obstacleGrid[i][j] == 0) {
              cur[i] += cur[i - 1]; 
              if (cur[i]) 
                is_reachable = true;
          } else {
            cur[i] = 0; 
          }
      }
      if (is_reachable == false) {
        return 0;
      }
  } 
  return cur[m - 1];
}
