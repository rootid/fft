//Maximal Square
//Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.
//For example, given the following matrix:
//1 0 1 0 0
//1 0 1 1 1
//1 1 1 1 1
//1 0 0 1 0
//Return 4.
//
//

//######################### Optimization : O(n) : Space , O(n^2) : time  ####################################  
int maximalSquare(vector<vector<char>>& matrix) {
  if(matrix.empty()) {
    return 0;
  }
	int m = matrix.size();
	int n = matrix[0].size();
	vector<int> pre(m, 0);
	vector<int> cur(m, 0);
	int maxsize = 0;
  //from top to bottom
	for (int i = 0; i < m; i++) {
		pre[i] = matrix[i][0] - '0';
		maxsize = max(maxsize, pre[i]);
	}
  //from left to right
	for (int j = 1; j < n; j++) {
		cur[0] = matrix[0][j] - '0';
		maxsize = max(maxsize, cur[0]);
		for (int i = 1; i < m; i++) {
			if (matrix[i][j] == '1') {
				cur[i] = min(cur[i - 1], min(pre[i - 1], pre[i])) + 1;
				maxsize = max(maxsize, cur[i]);
			}
		}
		swap(pre, cur);
		fill(cur.begin(), cur.end(), 0);
	}
	return maxsize * maxsize;
}


//######################### Optimization-2 : O(n) : Space , O(n^2) : time  ####################################  
//it is actually enough to use one vector only instead of two. The whole purpose of maintaining two arrays is that we want to keep the information of pre[i-1]. 
//So we just need to use another variable to keep track of its value
int maximalSquare(vector<vector<char>>& matrix) {
    if (matrix.empty()) return 0;
    int nr = matrix.size(); 
    int nc = matrix[0].size(); 
    vector<int> dp(nc+1, 0);
    int maxsize = 0;
    int last_topleft = 0;  // This is 'pre[i-1]' for the current element
    
    for (int ir = 1; ir <= nr; ++ir) {
        for (int ic = 1; ic <= nc; ++ic) {
            int temp = dp[ic];      // This is 'pre[i-1]' for the next element                
             if (matrix[ir-1][ic-1] == '0') dp[ic] = 0; 
            else {
                dp[ic] = min(min(dp[ic], dp[ic-1]), last_topleft) + 1;
                maxsize = max(maxsize, dp[ic]);
            }
            last_topleft = temp;  // update 'pre[i-1]'
        }
    }
    return maxsize * maxsize;
}

//######################### Optimization-2 : O(n) : Space , O(n^2) : time  ####################################  
int maximalSquare(vector<vector<char>>& matrix) {
    if (matrix.empty()) return 0;
    int m = matrix.size(), n = matrix[0].size();
    vector<int> dp(m + 1, 0);
    int maxsize = 0, pre = 0;
    for (int j = 0; j < n; j++) {
        for (int i = 1; i <= m; i++) {
            int temp = dp[i];
            if (matrix[i - 1][j] == '1') {
                dp[i] = min(dp[i], min(dp[i - 1], pre)) + 1;
                maxsize = max(maxsize, dp[i]);
            }
            else dp[i] = 0; 
            pre = temp;
        }
    }
    return maxsize * maxsize;
}

//######################### O(n^2) : Space , O(n^2) : time  ######################### 
int maximalSquare(vector<vector<char>>& matrix) {
    if(matrix.empty()) {
      return 0;
    }
    int m = matrix.size();
    int n = matrix[0].size();
    vector<vector<int> > size(m, vector<int>(n, 0));
    int maxsize = 0;
    //top to bottom
    for (int j = 0; j < n; j++) {
        size[0][j] = matrix[0][j] - '0';
        maxsize = max(maxsize, size[0][j]);
    }
    //lef to right
    for (int i = 1; i < m; i++) {
        size[i][0] = matrix[i][0] - '0';
        maxsize = max(maxsize, size[i][0]);
    }
    //start from left + top to right+bottom
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (matrix[i][j] == '1') {
                size[i][j] = min(size[i - 1][j - 1], min(size[i - 1][j], size[i][j - 1])) + 1;
                maxsize = max(maxsize, size[i][j]);
            }
        }
    }
    return maxsize * maxsize;
}


//##################################################### pytonic ################################################ 
//What's the largest (full-of-ones-)square ending at (i,j), meaning lower right corner in row i, column j? Imagine there are 4x4 squares above, above-left and left of it:
//above  above-left  left
// 1111     1111
// 1111     1111     1111
// 1111     1111     1111
// 1111     1111     1111
//    *         *    1111*
//Clearly, if cell (i,j) itself is 1 as well, then there's a 5x5 square ending at (i,j). And if there were 5x5 squares above, above-left and left of it, then we'd have a 6x6. So to find the largest square ending at (i,j), we just take the minimum size of squares ending at (i-1,j), (i-1,j-1) and (i,j-1), and add 1.
//

//I write the maximum sizes directly into the input matrix A. Cell A[i][j] will tell the side length of the largest square ending at (i,j). I go top to bottom and left to right, so (i-1,j), (i-1,j-1) and (i,j-1) have all been handled already. First thing I do for each cell is turn it into an integer, and then if it's 1 and it's not on the top or left border of the matrix, I determine its largest-square size as explained above. In the end, I return 0 for the empty matrix and otherwise the area of the largest square ending anywhere.

//class Solution:
//    def maximalSquare(self, A):
//        for i in range(len(A)):
//            for j in range(len(A[i])):
//                A[i][j] = int(A[i][j])
//                if A[i][j] and i and j:
//                    A[i][j] = min(A[i-1][j], A[i-1][j-1], A[i][j-1]) + 1
//        return len(A) and max(map(max, A)) ** 2
//
//class Solution:
//    def maximalSquare(self, A):
//        for i, r in enumerate(A):
//            r = A[i] = map(int, r)
//            for j, c in enumerate(r):
//                if i * j * c:
//                    r[j] = min(A[i-1][j], r[j-1], A[i-1][j-1]) + 1
//        return max(map(max, A + [[0]])) ** 2
//
//O(n) : extra space
//Here's a version that doesn't overwrite the input matrix but uses two integer lists: s tells the sizes of the squares ending it the current row and p does the same for the previous row.
//class Solution:
//    def maximalSquare(self, A):
//        area = 0
//        if A:
//            p = [0] * len(A[0])
//            for row in A:
//                s = map(int, row)
//                for j, c in enumerate(s[1:], 1):
//                    s[j] *= min(p[j-1], p[j], s[j-1]) + 1
//                area = max(area, max(s) ** 2)
//                p = s
//        return area
//
//Note that in Python with its integer and string objects, I'm not sure this actually saves space. But in other languages, overwriting the input array might not even be possible, and if it's possible, it might take more space than a "O(n) Extra Space" variant.
//
//
//sol = Solution()
//m = [[]] * 10;
//sol.maximalSquare(m)
//Error:
//area = max(area, max(s) ** 2)
//ValueError: max() arg is an empty sequence
//In my opinion that's invalid input. That's the empty matrix, which ought to be encoded as []. That's also how the OJ encodes it. You could argue that the signature {character[][]} matrix allows it, but then I say that that also allows rows of different lengths.
//But if you want to allow your input, then just change my entry test to
//        if any(A):
//and for my first two solutions, change the last line to:
//
//        return int(any(A)) and max(map(max, A)) ** 2
