//You are given a matrix with N rows and N columns. Elements in matrix can be
//either 1 or 0. Each
//row and column of matrix is sorted in ascending order.  Find number of 0-s in
//the given matrix.
//Example:
//
//
//0 0 1
//0 1 1
//1 1 1
//Answer: 3
//
//0 0
//0 0
//Answer: 4
//

//O(N^2)
//O(N log(N))
//
//
def number_of_zeros(self, grid) :
  r,c = map(len, [grid, grid[0])
  cnt = 0
  for i in range(r) :
    for j in range(c) :
      if(grid[i][j] == 0)
        cnt += 1
  return cnt

