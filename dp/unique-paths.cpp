//Unique Paths
//A robot is located at the top-left corner of a m x n grid (marked 'Start' in
//the diagram below).
//The robot can only move either down or right at any point in time. The robot
//is trying to reach the bottom-right corner of the grid (marked 'Finish' in
//the diagram below).
//How many possible unique paths are there?


//######################################### TC: O(m*n) #########################################
//Xtra space : O(mn)
    public int uniquePaths(int m, int n) {
        //Total # of subproblems : O(mn)
        int[][] path = new int[m][n];
        Arrays.fill(path[0], 1); //R->D
        Arrays.fill(path[m-1], 1); //D->R
        for(int i=1;i<m;i++) {
            path[i][0] = 1; //R->D
            path[i][n-1] = 1; //D->R
        }
        for(int i=1;i<m;i++)
            for(int j=1;j<n;j++)
                path[i][j] = path[i-1][j] + path[i][j-1];
        return path[m-1][n-1];
    }

//######################################### TC: O(m*n) #########################################
public int uniquePaths(int m, int n) {
	//Totol # of subproblems : O(mn)
    int[][] path = new int[m][n];
    Arrays.fill(path[0], 1);
    for(int i=1;i<m;i++) path[i][0] = 1;
    for(int i=1;i<m;i++)
        for(int j=1;j<n;j++)
            path[i][j] = path[i-1][j] + path[i][j-1];
    return path[m-1][n-1];
}




//########################################## Space O(n^2) ##########################################
//When (n==0||m==0) the function always returns 0 since the robot can't go left
//or up.
//For all other cells. The result = uniquePaths(m-1,n)+uniquePaths(m,n-1)
//Therefore I populated the edges with 1 first and use DP to get the full 2-D
//array.
int uniquePaths(int m, int n) {
    vector< vector<int> > paths(m, vector<int>(n,1) );
    for(int i=1;i<m;i++) {
        for(int j=1;j<n;j++) {
            paths[i][j] = paths[i-1][j] + paths[i][j-1];
        }
    }
    return paths[m-1][n-1];
}

//##################################### Space optimization O(min(m, n)) #####################################
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

//######################################### Recursion  #########################################
public int countPaths(int m, int n){
   if (m == 0 || n == 0) {
		return 0;
    }
   if (m == 1 || n == 1) {
		return 1;
   }
   int result = countPaths(m-1,n) + countPaths(m,n-1);
   return result;
}

//######################################### Python #########################################
class Solution:
    # @return an integer
    def uniquePaths(self, m, n):
        aux = [[1 for x in range(n)] for x in range(m)]
        for i in range(1, m):
            for j in range(1, n):
                aux[i][j] = aux[i][j-1]+aux[i-1][j]
        return aux[-1][-1]
