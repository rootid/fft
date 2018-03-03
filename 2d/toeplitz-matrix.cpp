//Toeplitz Matrix
//A matrix is Toeplitz if every diagonal from top-left to bottom-right has the
//same element.
//Now given an M x N matrix, return True if and only if the matrix is Toeplitz.
//Example 1:
//Input: matrix = [[1,2,3,4],[5,1,2,3],[9,5,1,2]]
//Output: True
//Explanation:
//1234
//5123
//9512
//In the above grid, the diagonals are "[9]", "[5, 5]", "[1, 1, 1]", "[2, 2,
//2]", "[3, 3]", "[4]",
//and in each diagonal all elements are the same, so the answer is True.
//Example 2:
//Input: matrix = [[1,2],[2,2]]
//Output: False
//Explanation:
//The diagonal "[1, 2]" has different elements.
//Note:
//    matrix will be a 2D array of integers.
//    matrix will have a number of rows and columns in range [1, 20].
//    matrix[i][j] will be integers in range [0, 99].
//######################################### Group by Category  #########################################
//Time Complexity: O(M∗N). (Recall in the problem statement that M,NM, NM,N are
//the number of rows
//and columns in matrix.)
//Space Complexity: O(M∗N).
//
//Intuition and Algorithm
//We ask what feature makes two coordinates (r1, c1) and (r2, c2) belong to the
//same diagonal?
//It turns out two coordinates are on the same diagonal if and only if r1 - c1
//== r2 - c2.
//This leads to the following idea: remember the value of that diagonal as
//groups[r-c]. If we see a
//mismatch, the matrix is not Toeplitz; otherwise it is.
// Matrix > diagonal visit (L->R) subtract (R->L)
public boolean isToeplitzMatrix(int[][] matrix) {
    Map<Integer, Integer> groups = new HashMap();
    for (int r = 0; r < matrix.length; ++r) {
        for (int c = 0; c < matrix[0].length; ++c) {
            if (!groups.containsKey(r-c))
                groups.put(r-c, matrix[r][c]);
            else if (groups.get(r-c) != matrix[r][c])
                return False;
        }
    }
    return True;
}
//######################################### Compare With Top-Left Neighbor #########################################
//Intuition and Algorithm
//For each diagonal with elements in order a1,a2,a3,…,ak
//, we can check a1=a2,a2=a3,…,ak−1=ak
//. The matrix is Toeplitz if and only if all of these conditions are true for all (top-left to bottom-right) diagonals.
//Every element belongs to some diagonal, and it's previous element (if it
//exists) is it's top-left
//neighbor. Thus, for the square (r, c), we only need to check r == 0 OR c == 0
//OR matrix[r-1][c-1]
//== matrix[r][c]
class Solution {
    public boolean isToeplitzMatrix(int[][] matrix) {
        for (int r = 0; r < matrix.length; ++r)
            for (int c = 0; c < matrix[0].length; ++c)
                if (r > 0 && c > 0 && matrix[r-1][c-1] != matrix[r][c])
                    return false;
        return true;
    }
}
