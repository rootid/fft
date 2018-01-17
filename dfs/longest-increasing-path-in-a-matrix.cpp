//longest-increasing-path-in-a-matrix
//Given an integer matrix, find the length of the longest increasing path.
//From each cell, you can either move to four directions: left, right, up or down. You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).
//Example 1:
//nums = [
//  [9,9,4],
//  [6,6,8],
//  [2,1,1]
//]
//Return 4
//The longest increasing path is [1, 2, 6, 9].
//Example 2:
//nums = [
//  [3,4,5],
//  [3,2,6],
//  [2,2,1]
//]
//Return 4
//The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
//

//######################################### DFS  ######################################### 
//key observation is that the sequence is strictly increasing, so it can not have loops. So we have the following:
//longest(i,j) = longest increasing path from (i,j) to (k,l) + longest(k,l)
//where longest(i,j) is longest increasing path starting with (i,j).

//1. Do DFS from every cell
//2. Compare every 4 direction and skip cells that are out of boundary or smaller
//3. Get matrix max from every cell's max
//4. Use matrix[x][y] <= matrix[i][j] so we don't need a visited[m][n] array
//5. The key is to cache the distance because it's highly possible to revisit a cell
//DFS here is basically like DP with memorization. Every cell that has been computed will not be computed again, only a value look-up is performed. So this is O(mn), m and n being the width and height of the matrix.
//To be exact, each cell can be accessed 5 times at most: 4 times from the top, bottom, left and right and one time from the outermost double for loop. 4 of these 5 visits will be look-ups except for the first one. So the running time should be lowercase o(5mn), which is of course O(mn).

//######################################### DFS  With Map ######################################### 
public static final int[][] dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    
public int longestIncreasingPath(int[][] matrix) {
    if(matrix.length == 0) return 0;
    int m = matrix.length, n = matrix[0].length;
    Map<Integer, Integer> cache = new HashMap<>();
    int max = 1;
	//same as word boggle
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            int len = dfs(matrix, i, j, m, n, cache);
            max = Math.max(max, len);
        }
    }   
    return max;
}

public int dfs(int[][] matrix, int i, int j, int m, int n, Map<Integer, Integer> cache) {
    if(cache.containsKey( i * matrix[0].length + j ) ) return cache.get(i * matrix[0].length + j );
    int max = 1;
    for(int[] dir: dirs) {
        int x = i + dir[0], y = j + dir[1]; //x,y : Current position
		//Pruning based on the matrix value
        if(x < 0 || x >= m || y < 0 || y >= n || matrix[x][y] <= matrix[i][j]) continue;  
        int len = 1 + dfs(matrix, x, y, m, n, cache);
        max = Math.max(max, len);
    }
    cache.put( i * matrix[0].length + j, max);
    return max;
}


//######################################### Max PQ + DP ######################################### 
private static int[][] dir = new int[][]{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
private int maxLen = 0;

public int longestIncreasingPath(int[][] matrix) {
    
    // Algo thinking: reverse thinking
    //      (1) Use a maxPQ
    //      (2) DP
    // time = O(N*M*lg(N*M)), space = O(N*M)
    
    if (matrix == null || matrix.length == 0) return 0;
    
    int n = matrix.length;
    int m = matrix[0].length;
    
    PriorityQueue<int[]> maxPQ = new PriorityQueue<>((a, b) -> b[2] - a[2]);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            maxPQ.offer(new int[]{i, j, matrix[i][j]});
        }
    }
    
    int[][] dp = new int[n][m];
    while (!maxPQ.isEmpty()) {
        int[] cell = maxPQ.poll();
        int i = cell[0], j = cell[1];
        dp[i][j] = 1;
        for (int[] d: dir) {
            int newI = i + d[0], newJ = j + d[1];
            if (newI < 0 || newI >= n || newJ < 0 || newJ >= m || matrix[i][j] >= matrix[newI][newJ]) continue;
            dp[i][j] = Math.max(dp[i][j], dp[newI][newJ] + 1);
        }
        
        maxLen = Math.max(maxLen, dp[i][j]);
    }
    
    return maxLen;
}

//######################################### DFS  ######################################### 
public static final int[][] dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

public int longestIncreasingPath(int[][] matrix) {
    if(matrix.length == 0) return 0;
    int m = matrix.length, n = matrix[0].length;
    int[][] cache = new int[m][n];
    int max = 1;
	//same as word boggle
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            int len = dfs(matrix, i, j, m, n, cache);
            max = Math.max(max, len);
        }
    }   
    return max;
}

public int dfs(int[][] matrix, int i, int j, int m, int n, int[][] cache) {
    if(cache[i][j] != 0) return cache[i][j];
    int max = 1;
    for(int[] dir: dirs) {
        int x = i + dir[0], y = j + dir[1]; //x,y : Current position
		//Pruning based on the matrix value
        if(x < 0 || x >= m || y < 0 || y >= n || matrix[x][y] <= matrix[i][j]) continue;  
        int len = 1 + dfs(matrix, x, y, m, n, cache);
        max = Math.max(max, len);
    }
    cache[i][j] = max;
    return max;
}

//######################################### DFS  ######################################### 
private int m;
private int n;
private int[][] maxILen;
private int[][] matrix;

public int longestIncreasingPath(int[][] matrix) {
    
    m = matrix.length;
    if(m < 1) return 0;
    n = matrix[0].length;
    this.matrix = matrix;
    
    maxILen = new int[m][n];
    int max = 1;
    
    for(int i=0;i<m;i++){
        
        for(int j=0;j<n;j++){
            max = Math.max(max, maxDFS(i,j));                        
        }
    }
    
    return max;
}

private int maxDFS(int i,int j){
    if(maxILen[i][j] != 0) return maxILen[i][j];
    
    int max = 1;
    if(i+1 < m && matrix[i+1][j] > matrix[i][j]) max = Math.max(max, 1 + maxDFS(i+1,j));
    if(i-1 >= 0 && matrix[i-1][j] > matrix[i][j]) max = Math.max(max, 1 + maxDFS(i-1,j));
    if(j+1 < n && matrix[i][j+1] > matrix[i][j]) max = Math.max(max, 1 + maxDFS(i,j+1));
    if(j-1 >= 0 && matrix[i][j-1] > matrix[i][j]) max = Math.max(max, 1 + maxDFS(i,j-1));
    maxILen[i][j] = max;
    return max;
}


//######################################### DFS + longest decreasing #########################################  
def longestIncreasingPath(self, matrix):
    def dfs(i, j):
        if not dp[i][j]:
            val = matrix[i][j]
            dp[i][j] = 1 + max(
                dfs(i - 1, j) if i and val > matrix[i - 1][j] else 0,
                dfs(i + 1, j) if i < M - 1 and val > matrix[i + 1][j] else 0,
                dfs(i, j - 1) if j and val > matrix[i][j - 1] else 0,
                dfs(i, j + 1) if j < N - 1 and val > matrix[i][j + 1] else 0)
        return dp[i][j]

    if not matrix or not matrix[0]: return 0
    M, N = len(matrix), len(matrix[0])
    dp = [[0] * N for i in range(M)]
    return max(dfs(x, y) for x in range(M) for y in range(N))


//######################################### DFS + Stack ######################################### 
class Solution(object):
    def longestIncreasingPath(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: int
        """
        if not matrix:
            return 0
        w=len(matrix[0])
        h=len(matrix)
        bank=[[0]*w for i in range(h)]
        for i in range(h):
            for j in range(w):
                stack=[(i,j,0)]
                while stack:
                    iin,jin,k=stack.pop(0)
                    for x,y in (iin+1,jin),(iin-1,jin),(iin,jin+1),(iin,jin-1):
                        if -1<x<h and -1<y<w and matrix[x][y]>matrix[iin][jin]:
                            stack.append((x,y,k+1))
                            bank[x][y]=max(bank[x][y],k+1)
        return max(max(a)for a in bank)+1

//######################################### DFS ######################################### 
def longestIncreasingPath(self, M):
        if not any(M): return 0
        d = {}
        def check(i, j):
            if not (i, j) in d:
                d[(i, j)] = max(check(x, y) 
                    if 0 <= x < len(M) and 0 <= y < len(M[0]) and M[x][y] > M[i][j] else 0
                    for x, y in [(i + 1, j), (i - 1, j), (i, j + 1), (i, j - 1)]) + 1
            return d[(i, j)]
        return max(check(i, j) for i in range(len(M)) for j in range(len(M[0])))


//######################################### Bottom up ######################################### 
def longestIncreasingPath(self, M):
        if not any(M): return 0
        d = {}
        def check(i, j):
            if not (i, j) in d:
                d[(i, j)] = max(check(x, y) 
                    if 0 <= x < len(M) and 0 <= y < len(M[0]) and M[x][y] > M[i][j] else 0
                    for x, y in [(i + 1, j), (i - 1, j), (i, j + 1), (i, j - 1)]) + 1
            return d[(i, j)]
        return max(check(i, j) for i in range(len(M)) for j in range(len(M[0])))


//######################################### Top down ######################################### 
def longestIncreasingPath(self, matrix):
    def length(z):
        if z not in memo:
            memo[z] = 1 + max([length(Z)
                               for Z in z+1, z-1, z+1j, z-1j
                               if Z in matrix and matrix[z] > matrix[Z]]
                              or [0])
        return memo[z]
    memo = {}
    matrix = {i + j*1j: val
              for i, row in enumerate(matrix)
              for j, val in enumerate(row)}
    return max(map(length, matrix) or [0])

//######################################### Priority queue ######################################### 
private static int[][] dir = new int[][]{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
private int maxLen = 0;
public int longestIncreasingPath(int[][] matrix) {
    
    // Algo thinking: reverse thinking
    //      (1) Use a maxPQ
    //      (2) DP
    // time = O(N*M*lg(N*M)), space = O(N*M)
    
    if (matrix == null || matrix.length == 0) return 0;
    
    int n = matrix.length;
    int m = matrix[0].length;
    
    PriorityQueue<int[]> maxPQ = new PriorityQueue<>((a, b) -> b[2] - a[2]);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            maxPQ.offer(new int[]{i, j, matrix[i][j]});
        }
    }
    int[][] dp = new int[n][m];
    while (!maxPQ.isEmpty()) {
        int[] cell = maxPQ.poll();
        int i = cell[0], j = cell[1];
        dp[i][j] = 1;
        for (int[] d: dir) {
            int newI = i + d[0], newJ = j + d[1];
            if (newI < 0 || newI >= n || newJ < 0 || newJ >= m || matrix[i][j] >= matrix[newI][newJ]) continue;
            dp[i][j] = Math.max(dp[i][j], dp[newI][newJ] + 1);
        }
        
        maxLen = Math.max(maxLen, dp[i][j]);
    }
    
    return maxLen;
}

