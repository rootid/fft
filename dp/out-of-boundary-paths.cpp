//Out Of Boundary Paths
//There is an m by n grid with a ball. Given the start coordinate (i,j) of the ball, you can move the ball to adjacent cell or cross the grid boundary in four directions (up, down, left, right). However, you can at most move N times. Find out the number of paths to move the ball out of grid boundary. The answer may be very large, return it after mod 10^9 + 7. 
//Example 1:
//Input:m = 2, n = 2, N = 2, i = 0, j = 0
//Output: 6
//Explanation:
//Example 2:
//Input:m = 1, n = 3, N = 3, i = 0, j = 1
//Output: 12
//Explanation:
//Note:
//Once you move the ball out of boundary, you cannot move it back.
//The length and height of the grid is in range [1,50].
//N is in range [0,50].


//NOTE : 2d array can be represented as 1-D array 
//(i,j) = i*j
//######################################### DP  ######################################### 
//DP[i][j][k] stands for how many possible ways to walk into cell j,k in step i,
//DP[i][j][k] only depends on DP[i - 1][j][k], so we can compress 3 dimensional dp array to 2 dimensional.
public int findPaths(int m, int n, int N, int i, int j) { 
	if (N <= 0) return 0;
    final int MOD = 1000000007;
    int[][] count = new int[m][n];
    count[i][j] = 1; //count[i][j] = number of ways to walk into cell i,j
    int result = 0;
    
    int[][] dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	//At most N iterations 
    for (int step = 0; step < N; step++) { 
		int[][] temp = new int[m][n];
		//Iterate over board
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                for (int[] d : dirs) {
                    int nr = r + d[0];
                    int nc = c + d[1];
					//Ball reached to boundary
                    if (nr < 0 || nr >= m || nc < 0 || nc >= n) {
                        result = (result + count[r][c]) % MOD;
                    } else { 
						temp[nr][nc] = (temp[nr][nc] + count[r][c]) % MOD;
                    }
                }
            }
        }
        count = temp;
    }
    return result; 
}

//######################################### Space : space O(N*m*n) ######################################### 
//######################################### 3D array JAVA ######################################### 
public class Solution {
    public int findPaths(int m, int n, int N, int i0, int j0) {
        long limit = 1000000007;
        long[][][] dp = new long[N + 1][m][n];
        for (int k = 1; k <= N; k++) { //k : # of steps in each iteration
            for (int i = 0; i < m; i++) { // i,j : Board representation of array
                for (int j = 0; j < n; j++) {
                    dp[k][i][j] += i == 0     ? 1 : dp[k - 1][i - 1][j];
                    dp[k][i][j] += i == m - 1 ? 1 : dp[k - 1][i + 1][j];
                    dp[k][i][j] += j == 0     ? 1 : dp[k - 1][i][j - 1];
                    dp[k][i][j] += j == n - 1 ? 1 : dp[k - 1][i][j + 1];
                    dp[k][i][j] %= limit;
                }
            }
        }
        return (int)dp[N][i0][j0];        
    }
}

//######################################### Space : space O(m*n) ######################################### 
//######################################### Rolling matrix  ######################################### 
public class Solution {
    public int findPaths(int m, int n, int N, int i0, int j0) {
        long limit = 1000000007;
        long[][][] dp = new long[2][m][n];
        for (int k = 1; k <= N; k++) {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    dp[k % 2][i][j] =((i == 0     ? 1 : dp[(k - 1) % 2][i - 1][j])
                                    + (i == m - 1 ? 1 : dp[(k - 1) % 2][i + 1][j])
                                    + (j == 0     ? 1 : dp[(k - 1) % 2][i][j - 1])
                                    + (j == n - 1 ? 1 : dp[(k - 1) % 2][i][j + 1])) % limit;
                }
            }
        }
        return (int)dp[N % 2][i0][j0];        
    }
}

//######################################### 3D array ######################################### 
class Solution {
public:
    int findPaths(int m, int n, int N, int i, int j) {
        size_t limit = 1000000007;
        vector<vector<vector<size_t>>> dp(N + 1, vector<vector<size_t>>(m, vector<size_t>(n, 0)));
        for (int k = 1; k <= N; k++) {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    dp[k][i][j] += i == 0     ? 1 : dp[k - 1][i - 1][j];
                    dp[k][i][j] += i == m - 1 ? 1 : dp[k - 1][i + 1][j];
                    dp[k][i][j] += j == 0     ? 1 : dp[k - 1][i][j - 1];
                    dp[k][i][j] += j == n - 1 ? 1 : dp[k - 1][i][j + 1];
                    dp[k][i][j] %= limit;
                }
            }
        }
        return dp[N][i][j];
    }
};

//################################################### DFS  ################################################### 
class Solution {
public:
    int findPaths(int m, int n, int N, int i, int j) {
        int limit = 1000000007;
        int paths = 0;
        dfs(m, n, N, i, j, paths, limit);
        return paths;
    }

private:
    void dfs(int m, int n, int N, int i, int j, int& paths, int limit) {
        if (N > 0 && paths < limit && i >= 0 && i < m && j >= 0 && j < n) {
            if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {
                paths += i == 0;
                paths += i == m - 1;
                paths += j == 0;
                paths += j == n - 1;
                if (N == 0 || paths >= limit)
                    return;
            }

            dfs(m, n, N - 1, i + 1, j, paths, limit);
            dfs(m, n, N - 1, i - 1, j, paths, limit);
            dfs(m, n, N - 1, i, j + 1, paths, limit);
            dfs(m, n, N - 1, i, j - 1, paths, limit);
        }
    }
};

//######################################### DP : Python ######################################### 
//At time t, let's maintain cur[r][c] = the number of paths to (r, c) with t moves,
//and nxt[r][c] = the number of paths to (r, c) with t+1 moves.
//A ball at (r, c) at time t, can move in one of four directions.
//If it stays on the board, then it contributes to a path that takes t+1 moves.
//If it falls off the board, then it contributes to the final answer.
def findPaths(self, R, C, N, sr, sc):
    MOD = 10**9 + 7
    nxt = [[0] * C for _ in xrange(R)]
    nxt[sr][sc] = 1
    
    ans = 0
    for time in xrange(N):
        cur = nxt
        nxt = [[0] * C for _ in xrange(R)]
        for r, row in enumerate(cur):
            for c, val in enumerate(row):
                for nr, nc in ((r-1, c), (r+1, c), (r, c-1), (r, c+1)):
                    if 0 <= nr < R and 0 <= nc < C:
                        nxt[nr][nc] += val
                        nxt[nr][nc] %= MOD
                    else:
                        ans += val
                        ans %= MOD
        
    return ans


//#########################################2. Functor #########################################
class Solution {
public:
    int findPaths(int m, int n, int N, int i0, int j0) {
        vector<vector<vector<uint>>> dp(N + 1, vector<vector<uint>>(m, vector<uint>(n, 0)));
        auto paths = [&](int k, int i, int j) { return (i < 0 || i >= m || j < 0 || j >= n) ? 1 : dp[k][i][j]; };
        for (int k = 1; k <= N; k++) {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    dp[k][i][j] = paths(k - 1, i - 1, j) + paths(k - 1, i + 1, j) + paths(k - 1, i, j - 1) + paths(k - 1, i, j + 1);
                    dp[k][i][j] %= 1000000007;
                }
            }
        }
        return dp[N][i0][j0];
    }
};
//#########################################3. Functor & Rolling Matrix #########################################
class Solution {
public:
    int findPaths(int m, int n, int N, int i0, int j0) {
        vector<vector<vector<uint>>> dp(N + 1, vector<vector<uint>>(m, vector<uint>(n, 0)));
        auto paths = [&](int k, int i, int j) { return (i < 0 || i >= m || j < 0 || j >= n) ? 1 : dp[k % 2][i][j]; };
        for (int k = 1; k <= N; k++) {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    dp[k % 2][i][j] = paths(k - 1, i - 1, j) + paths(k - 1, i + 1, j) + paths(k - 1, i, j - 1) + paths(k - 1, i, j + 1);
                    dp[k % 2][i][j] %= 1000000007;
                }
            }
        }
        return dp[N % 2][i0][j0];
    }
};
//#########################################4. Use Functor for Rolling #########################################
class Solution {
public:
    int findPaths(int m, int n, int N, int i0, int j0) {
        vector<vector<vector<uint>>> dp(2, vector<vector<uint>>(m, vector<uint>(n, 0)));
        auto paths = [&](int k, int i, int j) ->uint& { uint one = 1; return (i < 0 || i >= m || j < 0 || j >= n) ? one : dp[k % 2][i][j]; };
        for (int k = 1; k <= N; k++) {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    paths(k, i, j) = paths(k - 1, i - 1, j) + paths(k - 1, i + 1, j) + paths(k - 1, i, j - 1) + paths(k - 1, i, j + 1);
                    paths(k, i, j) %= 1000000007;
                }
            }
        }
        return paths(N, i0, j0);
    }
};

//#########################################5. Functor Rolling Array & Delta Sequence #########################################
class Solution {
public:
    int findPaths(int m, int n, int N, int i0, int j0) {
        vector<vector<vector<uint>>> dp(2, vector<vector<uint>>(m, vector<uint>(n, 0)));
        auto paths = [&](int k, int i, int j) ->uint& { uint one = 1; return (i < 0 || i >= m || j < 0 || j >= n) ? one : dp[k % 2][i][j]; };
        int delta[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};
        for (int k = 1; k <= N; k++) {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    paths(k, i, j) = 0; // reset before reuse
                    for (int d = 0; d < 4; d++) {
                        paths(k, i, j) += paths(k - 1, i + delta[d][0], j + delta[d][1]);
                    }
                    paths(k, i, j) %= 1000000007;
                }
            }
        }
        return paths(N, i0, j0);
    }
};


//Fastest posted Python solution so far. Takes about 120 ms, of which about 80 ms are for judge overhead and importing NumPy. The other three Python solutions posted so far take about 350-850 ms, of which about 40 ms are for judge overhead.
//My two-dimensional paths array tells the number of paths ending at each cell with the moves made so far. So initially all zeros except for the starting position, which has one path (the empty path). The for each move, I spread each path number in all four directions.
//This only keeps track of the paths staying inside the boundary. To compute how many paths went outside in the latest move, I take all previous paths, multiply them by 4 (for the four directions) and subtract the new number of inside-paths after the move.
import numpy as np

class Solution(object):
    def findPaths(self, m, n, N, i, j):
        paths = np.zeros((m, n), dtype=np.int64)
        paths[i][j] = 1
        out = 0
        mod = 10**9 + 7
        for _ in range(N):
            prev = paths % mod
            paths = prev - prev
            paths[1:] += prev[:-1]
            paths[:-1] += prev[1:]
            paths[:,1:] += prev[:,:-1]
            paths[:,:-1] += prev[:,1:]
            out += 4 * prev.sum() - paths.sum()
        return int(out % mod)
//A slightly shorter version using Python ints (which can grow arbitrarily large) and doing mod 109-7 only at the end:

import numpy as np

class Solution(object):
    def findPaths(self, m, n, N, i, j):
        paths = np.zeros((m, n), dtype=object)
        paths[i][j] = 1
        out = 0
        for _ in range(N):
            prev = paths
            paths = prev * 0
            paths[1:] += prev[:-1]
            paths[:-1] += prev[1:]
            paths[:,1:] += prev[:,:-1]
            paths[:,:-1] += prev[:,1:]
            out += 4 * prev.sum() - paths.sum()
        return out % (10**9 + 7)
