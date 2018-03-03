//Reshape the Matrix
//In MATLAB, there is a very useful function called 'reshape', which can
//reshape a matrix into a new one with different size but keep its original
//data.
//You're given a matrix represented by a two-dimensional array, and two
//positive integers r and c representing the row number and column number of
//the wanted reshaped matrix, respectively.
//The reshaped matrix need to be filled with all the elements of the original
//matrix in the same row-traversing order as they were.
//If the 'reshape' operation with given parameters is possible and legal,
//output the new reshaped matrix; Otherwise, output the original matrix.
//Example 1:
//Input:
//nums =
//[[1,2],
// [3,4]]
//r = 1, c = 4
//Output:
//[[1,2,3,4]]
//Explanation:
//The row-traversing of nums is [1,2,3,4]. The new reshaped matrix is a 1 * 4
//matrix, fill it row by row by using the previous list.
//Example 2:
//Input:
//nums =
//[[1,2],
// [3,4]]
//r = 2, c = 4
//Output:
//[[1,2],
// [3,4]]
//Explanation:
//There is no way to reshape a 2 * 2 matrix to a 2 * 4 matrix. So output the
//original matrix.
//Note:
//The height and width of the given matrix is in range [1, 100].
//The given r and c are all positive.
//
//matrix[index / width][index % width]


//######################################### matrix[index / width][index % width]  #########################################
public int[][] matrixReshape(int[][] nums, int r, int c) {
    int m = nums.length;
    int n = nums[0].length;
    int[][] result = new int[r][c];
    if(r*c != m*n) return nums;
    for(int i=0;i<m;i++) {
        for(int j=0;j<n;j++) {
            int tmp = i*n + j;
            int ii = tmp/c;
            int jj = tmp%c;;
            result[ii][jj] = nums[i][j];
        }
    }
    return result;
}

//######################################### matrix[index / width][index % width]  #########################################
vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c) {
  if(nums.empty()) {
    return nums;
  }
  int m = nums.size();
  int n = nums[0].size();
  if(m * n != r*c) {
      return nums;
  }
  vector<vector<int> > reshaped(r,vector<int>(c,0));
  for (int i = 0; i < r * c; i++) {
    reshaped[i/c][i%c] = nums[i/n][i%n];
  }
  return reshaped;
}

//################ pytonic
//Generators
//def matrixReshape(self, A, nR, nC):
//    if len(A) * len(A[0]) != nR * nC:
//        return A
//    vals = (val for row in A for val in row)
//    return [[vals.next() for c in xrange(nC)] for r in xrange(nR)]
//W/o Generators
//def matrixReshape(self, A, nR, nC):
//    if len(A) * len(A[0]) != nR * nC:
//        return A
//
//    vals = [val for row in A for val in row]
//    ans = [[None] * nC for _ in xrange(nR)]
//    i = 0
//    for r in xrange(nR):
//        for c in xrange(nC):
//            ans[r][c] = vals[i]
//            i += 1
//    return ans
//
//
//numpy
//import numpy as np
//class Solution(object):
//    def matrixReshape(self, nums, r, c):
//        try:
//            return np.reshape(nums, (r, c)).tolist()
//        except:
//            return nums

//def matrixReshape(self, nums, r, c):
//    if r * c != len(nums) * len(nums[0]):
//        return nums
//    it = itertools.chain(*nums)
//    return [list(itertools.islice(it, c)) for _ in xrange(r)]
//
//
//def matrixReshape(self, nums, r, c):
//    flat = sum(nums, [])
//    if len(flat) != r * c:
//        return nums
//    tuples = zip(*([iter(flat)] * c))
//    return map(list, tuples)
//
//def matrixReshape(self, nums, r, c):
//    return nums if len(sum(nums, [])) != r * c else map(list, zip(*([iter(sum(nums, []))]*c)))
