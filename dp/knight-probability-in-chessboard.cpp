//Knight(Ghoda) Probability in Chessboard
//On an NxN chessboard, a knight starts at the r-th row and c-th column and
//attempts to make exactly K moves. The rows and columns are 0 indexed, so the
//top-left square is (0, 0), and the bottom-right square is (N-1, N-1).
//A chess knight has 8 possible moves it can make, as illustrated below. Each
//move is two squares in a cardinal direction, then one square in an orthogonal
//direction.
//Each time the knight is to move, it chooses one of eight possible moves
//uniformly at random (even if the piece would go off the chessboard) and moves
//there.
//The knight continues moving until it has made exactly K moves or has moved
//off the chessboard. Return the probability that the knight remains on the
//board after it has stopped moving.
//Example:
//Input: 3, 2, 0, 0
//Output: 0.0625
//Explanation: There are two moves (to (1,2), (2,1)) that will keep the knight
//on the board.
//From each of those positions, there are also two moves that will keep the
//knight on the board.
//The total probability the knight stays on the board is 0.0625.
//Note:
//N will be between 1 and 25.
//K will be between 0 and 100.
//The knight always initially starts on the board.
//

//3D
//######################################### DP #########################################
//the dp is a 3-dimensional array. But we only need the previous one to derive
//the current one,
// so I only preserve the previous one in the dp0 and calculate the current one in the dp1.
//Let's think about our formula, dp1[i][j] = sum(dp0[all reachable spots]).
//Assuming we are calculating the first step and all reachable spots are within
//the chessboard.
//Then the dp should be 8, which implies the initializing value should be 1.

int[][] moves = {{1, 2}, {1, -2}, {2, 1}, {2, -1}, {-1, 2}, {-1, -2}, {-2, 1}, {-2, -1}};
public double knightProbability(int N, int K, int r, int c) {
    int len = N;
    double dp0[][] = new double[len][len];
    for(double[] row : dp0) Arrays.fill(row, 1);
    for(int l = 0; l < K; l++) {
        double[][] dp1 = new double[len][len];
        for(int i = 0; i < len; i++) {
            for(int j = 0; j < len; j++) {
                for(int[] move : moves) {
                    int row = i + move[0];
                    int col = j + move[1];
                    if(isLegal(row, col, len)) dp1[i][j] += dp0[row][col];
                }
            }
        }
        dp0 = dp1;
    }
    return dp0[r][c] / Math.pow(8, K);
}
private boolean isLegal(int r, int c, int len) {
    return r >= 0 && r < len && c >= 0 && c < len;
}




//######################################### DP #########################################
//For this problem, I think memoization is more optimal than direct DP. The
//reason is that memoization can avoid a lot of unnecessary subproblems.
//The runtime is O(KN^2).

class Solution {
public:
    double knightProbability(int N, int K, int r, int c) {
        vector<vector<vector<double>>> dp(K+1, vector<vector<double>>(N, vector<double>(N, -1.0)));
        return helper(dp, N, K, r, c)/pow(8, K);
    }
private:
    double helper(vector<vector<vector<double>>>& dp, int N, int k, int r, int c) {
        // if out of board, return 0.0
        if (r < 0 || r >= N || c < 0 || c >= N) return 0.0;
        // when k = 0, no more move, so it's 100% safe
        if (k == 0) return 1.0;
        if (dp[k][r][c] != -1.0) return dp[k][r][c];
        dp[k][r][c] = 0.0;
        for (int i = -2; i <= 2; i++) {
            if (i == 0) continue;
            dp[k][r][c] += helper(dp, N, k-1, r+i, c+3-abs(i)) + helper(dp, N, k-1, r+i, c-(3-abs(i)));
        }
        return dp[k][r][c];
    }
};

//######################################### DP #########################################
class Solution {
    int[][] moves = {{1,2},{1,-2},{-1,2},{-1,-2},{2,-1},{2,1},{-2,-1},{-2,1}};
    public double knightProbability(int N, int K, int r, int c) {
        double[][][] dp = new double[K+1][N][N];
        return helper(dp, N, K, r, c)/Math.pow(8.0, K);
    }
    private double helper(double[][][] dp, int N, int k, int r, int c) {
        if (r < 0 || r >= N || c < 0 || c >= N) return 0.0;
        if (k == 0) return 1.0;
        if (dp[k][r][c] != 0.0) return dp[k][r][c];
        for (int i = 0; i < 8; i++)
            dp[k][r][c] += helper(dp, N, k-1, r+moves[i][0], c+moves[i][1]);
        return dp[k][r][c];
    }
}
//I am curious why is that when K is 100 and N is 25, there is no stack
//overflow. another question is why is the precision is not lost when dividing
//the possibilities 1, by 8, 100 times, which is 2^ 300, seems require
//something like a 40 bytes big decimal.
//Q1: The number of recursion levels you can do depends on the call-stack size
//and the size of local variables and arguments that are placed on such a
//stack. Theoretically current desktop machine can handle a recursive depth of
//hundreds to some thousands. stackoverflow
//Q2: I think the precision does get lost. Note that all possibilities in level
//i are summed together before division in level i+1. This may help preserve
//the precision, but cannot prevent it.

//######################################### DP #########################################
class Solution {
public:
    int movement[8][2] = {{1, 2},{1, -2},{-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1},{-2, -1}};
    double mem[100][25][25] = {0};
    double knightProbability(int N, int K, int r, int c) {
        double inside = 0;
        if(K){
            for(auto &i : movement)
                if(r + i[0] < N && r + i[0] >= 0 && c + i[1] < N && c + i[1] >= 0)
                    inside += 0.125* (mem[K-1][r+i[0]][c + i[1]]?
                                      mem[K-1][r+i[0]][c + i[1]] : knightProbability(N, K-1, r+i[0], c + i[1]));
            mem[K][r][c] = inside;
            return inside;
        }
        return 1;
    }
};

//######################################### BFS #########################################
//At the start, the knight is at (r, c) with probability 1 (and anywhere else
//with probability 0). Then update those probabilities over K moves.
def knightProbability(self, N, K, r, c):
    p = {(r, c): 1}
    for _ in range(K):
        p = {(r, c): sum(p.get((r+i, c+j), 0) + p.get((r+j, c+i), 0) for i in (1, -1) for j in (2, -2)) / 8
             for r in range(N) for c in range(N)}
    return sum(p.values())

//######################################### BFS #########################################
//Shorter and maybe nicer version, influenced a bit by @flamesofmoon's
//solution:
def knightProbability(self, N, K, r, c):
    p = {(r, c): 1}
    for _ in range(K):
        p = {(r, c): sum(p.get((r+i, c+j), 0) for x in (1, 2) for i in (x, -x) for j in (3-x, x-3)) / 8
             for r in range(N) for c in range(N)}
    return sum(p.values())

//{do sth for r in range(N) for c in range(N)}
//is morally the same as
//for r in range(N):
//    for c in range(N):
//        do sth
//The idea of the code is to compute the real-time probability distribution
//over the board. In other words, at time t (the t-th step), it computes the
//probability that the knight is at grid r,c for all r and c.
//That is also why the survival rate is the sum of everything inp.values()
//n my code, I am computing the survival rate for all grids on the board after
//K steps. The rates are updated step by step. For each step, probs[i][j]
//should be the sum of the rates in the possible eight grids divided by 8.
//Note that here I wrote a lengthy list comprehension in the for loop. This is
//not to show off. If I didn't do so, I will have to create a new 2D list,
//store values temporarily, and deepcopy that back to probs which is too much
//work.
//probs = [[(1 if i<N and j<N else 0) for j in xrange(N+2)] for i in
//xrange(N+2)]
//for t in xrange(K):
//    probs = [[(0.125*sum(probs[i+a*m1][j+(3-a)*m2] for a in [1,2] for m1 in [-1,1] for m2 in [-1,1]) if i<N and j<N else 0) for j in xrange(N+2)] for i in xrange(N+2)]
//return probs[r][c]
//Another interesting idea given by @StefanPochmann is here, in which he only
//computes for probs[r][c], but in the way that the probability distribution of
//the knight at each step is computed.
//I am curious if there is a mathematical solution to this problem using
//martingales or random walk. If you see one, please don't hesitate to

//######################################### DP #########################################
class Solution {
    public double knightProbability(int N, int K, int r, int c) {
        double[][] dp = new double[N][N];
        int[][] dirs = new int[][]{{-1,-2},{-1,2},{1,2},{1,-2},{2,1},{2,-1},{-2,-1},{-2,1}};
        dp[r][c] = 1;
        for(int p=0;p<K;p++){
            double[][] tempCount = new double[N][N];
            for(int i=0;i<N;i++){
                for(int j=0;j<N;j++){
                    for(int[] dir:dirs){
                        int x = i - dir[0];
                        int y = j - dir[1];
                        if(isInBoard(x,y,N)){
                            tempCount[i][j]+=dp[x][y];
                        }
                    }
                }
            }

            dp = tempCount;
        }

        double sum = 0;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                sum+=dp[i][j];
            }
        }

        return sum/Math.pow(8,K);
    }

    public boolean isInBoard(int x,int y,int N){
        if(x>=0&&x<N&&y>=0&&y<N){
            return true;
        }
        return false;
    }
}

