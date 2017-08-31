//Longest Line of Consecutive One in Matrix
//Given a 01 matrix M, find the longest line of consecutive one in the matrix. The line could be horizontal, vertical, diagonal or anti-diagonal.
//Example:
//Input:
//[[0,1,1,0],
// [0,1,1,0],
// [0,0,0,1]]
//Output: 3
//Hint: The number of elements in the given matrix will not exceed 10,000.
//

//######################################### DP ######################################### 
//TC : O(m*n)
//SC : O(n)
public class Solution {
    public int longestLine(int[][] M) {
        
        int m = M.length, ones = 0;
        if (m > 0) {
            int n = M[0].length;
            int[][] old = new int[4][n];
            for (int i = 0; i < m; i++) {
                int[][] curr = new int[4][n];
                for (int j = 0; j < n; j++) {
                    if (M[i][j] == 1) {
                        curr[0][j] = ((j > 0) ? curr[0][j - 1] + 1 : 1);
                        curr[1][j] = ((i > 0) ? old[1][j] + 1 : 1);
                        curr[2][j] = ((j < n - 1) ? old[2][j + 1] + 1 : 1);
                        curr[3][j] = ((j > 0) ? old[3][j - 1] + 1 : 1);
                        ones = Math.max(ones, Math.max(Math.max(curr[0][j], curr[1][j]), Math.max(curr[2][j], curr[3][j])));
                    } else {
                        curr[0][j] = curr[1][j] = curr[2][j] = curr[3][j] = 0;
                    }
                }
                
                old = curr;
            }
        }
        
        return ones;
    }
}

//######################################### Backtracking / DFS ######################################### 
//1. Traverse  in 4 directions
public class Solution {
    public int longestLine(int[][] M) {
        if(M == null) return 0;
        int res = 0;
        for(int i =0;i<M.length;i++){
            for(int j = 0;j<M[0].length;j++){
                if(M[i][j] == 1){
                    res = Math.max(res,getMaxOneLine(M, i, j));
                }
            }
        }
        return res;
    }
    final int [][] dirs = new int[][]{{1,0},{0,1},{1,1},{1,-1}};

    private int getMaxOneLine(int [][] M, int x, int y) {
        int res = 1;
        for(int [] dir:dirs){
            int i = x+dir[0];
            int j = y+dir[1];
            int count = 1;
            while(isValidPosition(M, i, j) && M[i][j] == 1){
                i+=dir[0];
                j+=dir[1];
                count++;
            }
            res = Math.max(count,res);
        }
        return res;
    }
    
    private boolean isValidPosition(int M[][], int i, int j){
        return (i<M.length && j<M[0].length && i>=0 && j>=0);
    }
}


//######################################### DP (3 - 1D array) ######################################### 
This is very similar to N-Queens. You can use the below approach and DFS to easily tackle down N-Queens problems.
public int longestLine(int[][] M) {
    if (M.length == 0 || M[0].length == 0) {
        return 0;
    }
    int max = 0;
    int[] col = new int[M[0].length];
    int[] diag = new int[M.length + M[0].length];
    int[] antiD = new int[M.length + M[0].length];
    for (int i = 0; i < M.length; i++) {
        int row = 0;
        for (int j = 0; j < M[0].length; j++) {
            if (M[i][j] == 1) {
                row++;
                col[j]++;
                diag[j + i]++;
                antiD[j - i + M.length]++;
                max = Math.max(max, row);
                max = Math.max(max, col[j]);
                max = Math.max(max, diag[j + i]);
                max = Math.max(max, antiD[j - i + M.length]);
            } else {
                row = 0;
                col[j] = 0;
                diag[j + i] = 0;
                antiD[j - i + M.length] = 0;
            }
        }
    }
    return max;
}


//######################################### DP (3D array) ######################################### 
public int longestLine(int[][] M) {
    int n = M.length, max = 0;
    if (n == 0) return max;
    int m = M[0].length;
    int[][][] dp = new int[n][m][4];
    for (int i=0;i<n;i++) 
        for (int j=0;j<m;j++) {
            if (M[i][j] == 0) 
				continue;
			//4 position/ groups (0: ht, 2: rt-dg, 3: lt-dg, 4: vt)
            for (int k=0;k<4;k++) 
				dp[i][j][k] = 1;
            if (j > 0) dp[i][j][0] += dp[i][j-1][0]; // horizontal line
            if (j > 0 && i > 0) dp[i][j][1] += dp[i-1][j-1][1]; // anti-diagonal line
            if (i > 0) dp[i][j][2] += dp[i-1][j][2]; // vertical line
            if (j < m-1 && i > 0) dp[i][j][3] += dp[i-1][j+1][3]; // diagonal line
            max = Math.max(max, Math.max(dp[i][j][0], dp[i][j][1]));
            max = Math.max(max, Math.max(dp[i][j][2], dp[i][j][3]));
        }
    return max;
}

//######################################### Grouping + Counting ######################################### 
//We can separate the problem into two subproblems. 
//The first subproblem is, given a 1 dimensional list of 0's and 1's, what is the longest chain of consecutive 1s?
//The second subproblem is to generate every line (row, column, diagonal, and anti-diagonal).
//The first problem is common. We keep track of the number of 1's we've seen before. If we see a 1, we add to our count and update our answer. If we see a 0, we reset. Alternatively, we can also use itertools.groupby. Straightforward code for the first part looks like this:

def score(line):
  ans = count = 0
  for x in line:
    if x:
      count += 1
      ans = max(ans, count)
    else:
      count = 0
  return ans
//The second part is more complex. We can try to manipulate indices of the grid,
//but there is a trick.
//Each element in the grid belongs to exactly 4 lines: 
//1. the r-th row,
//2. c-th column,
//3. (r+c)-th diagonal,
//4. and (r-c)-th anti-diagonal. We scan from left to right, top to bottom, adding each element's value to it's respective 4 groups. As we visited in reading order, our lines will be appended to in that order, which is suitable for our purposes.

def longestLine(self, A):
    if not A: return 0
    
    def score(line):
        return max(len(list(v)) if k else 0 
                   for k, v in itertools.groupby(line))
    
    groups = collections.defaultdict(list)
    for r, row in enumerate(A):
        for c, val in enumerate(row):
            groups[0, r] += [val]
            groups[1, c] += [val]
            groups[2, r+c] += [val]
            groups[3, r-c] += [val]
    
    return max(map(score, groups.itervalues()))

//######################################### TODO  ######################################### 
//TODO : Identify pattern in the stored location 
int numberOfConsectuiveOnes(vector<vector<int> >&mat) {
	if(mat.isEmpty()) return 0;
	int n = mat.size();
	int m = mat[0].size();
	int result = 0;
	vector<int> ones;
	for(int i=0;i<m;i++)  
	for(int j=0;j<n;j++) 
		ones.push_back(i*n + j);

	//find the pattern in ones vector
	for(int i=0;i<ones.size()-1;i++) {
		//if horizontal increase
		if(ones[i]+1 == ones[i+1]) {
			result++;
		}
	}
}
