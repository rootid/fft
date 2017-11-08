//Range Addition II
//Given an m * n matrix M initialized with all 0's and several update operations.
//Operations are represented by a 2D array, and each operation is represented by an array with two positive integers a and b, which means M[i][j] should be added by one for all 0 <= i < a and 0 <= j < b.
//You need to count and return the number of maximum integers in the matrix after performing all the operations.
//Example 1:
//Input: 
//m = 3, n = 3
//operations = [[2,2],[3,3]]
//Output: 4
//Explanation: 
//Initially, M = 
//[[0, 0, 0],
// [0, 0, 0],
// [0, 0, 0]]
//After performing [2,2], M = 
//[[1, 1, 0],
// [1, 1, 0],
// [0, 0, 0]]
//After performing [3,3], M = 
//[[2, 2, 1],
// [2, 2, 1],
// [1, 1, 1]]
//So the maximum integer in M is 2, and there are four of it in M. So return 4.
//Note:
//The range of m and n is [1,40000].
//The range of a is [1,m], and the range of b is [1,n].
//The range of operations size won't exceed 10,000.

//######################################### Minimum intersection count ######################################### 
public int maxCount(int m, int n, int[][] ops) {
    //NOTE : visualize LED board always start blinking from left corner
    //Max value can be obtained as ops.length as (0,0)/ left corner incremented by 1
    for(int[] corner : ops) {
        m = Math.min(m, corner[0]);
        n = Math.min(n, corner[1]);
    }
    return m * n;
}

//######################################### Use of auto ######################################### 
int maxCount(int m, int n, vector<vector<int>>& ops) {
    for (auto op : ops) {
        m = min(op[0], m);
        n = min(op[1], n);
    }
    return m * n;
}

//######################################### Use of auto ######################################### 
int maxCount(int m, int n, vector<vector<int>>& ops) { 
  for (int i = 0; i < ops.size(); ++i) { 
    m = min(m, ops[i][0]);
    n = min(n, ops[i][1]);
  }
  return m*n;
}



//################################################### pytonic ################################################### 
//Say the operations are [(x_1, y_1), (x_2, y_2), ..., (x_n, y_n)]. The top left square is clearly incremented by every operation. If some square (x, y) has x >= x_i, then it will not be marked by operation i. So all squares (x, y) with x >= min_i(x_i) do not get marked.
//Thus, when there is atleast one operation, all squares (x, y) with 0 <= x < min(x_1, x_2, ..., x_n) and 0 <= y < min(y_1, y_2, ..., y_n) get marked; and there are min_i(x_i) * min_i(y_i) of them. If there are no operations, then what is marked is the entire board.
//
//def maxCount(self, R, C, ops):
//    if not ops: return R * C
//    X, Y = zip(*ops)
//    return min(X) * min(Y)
