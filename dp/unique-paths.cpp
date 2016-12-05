//Unique Paths
//A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
//The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
//How many possible unique paths are there?

//Space O(n^2)
int uniquePaths(int m, int n) {
    vector< vector<int> > paths(m, vector<int>(n,1) );
    for(int i=1;i<m;i++) {
        for(int j=1;j<n;j++) {
            paths[i][j] = paths[i-1][j] + paths[i][j-1];
        }
    }
    return paths[m-1][n-1];
}

//Space optimization O(min(m, n))
int uniquePaths(int m, int n) {
   if (m > n) return uniquePaths(n, m); 
        vector<int> pre(m, 1);
        vector<int> cur(m, 1);
        for (int j = 1; j < n; j++) {
            for (int i = 1; i < m; i++)
                cur[i] = cur[i - 1] + pre[i];
            swap(pre, cur);
        }
        return pre[m - 1];
    }
}
