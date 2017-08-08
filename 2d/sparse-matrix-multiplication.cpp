//Sparse Matrix Multiplication
//Given two sparse matrices A andB, return the result of AB.
//You may assume that A's column number is equal to B's row number.
//Example:
//A = [
//      [ 1, 0, 0],
//      [-1, 0, 3]
//]
//B = [
//      [ 7, 0, 0 ],
//      [ 0, 0, 0 ],
//      [ 0, 0, 1 ]
//]
//
//     |  1 0 0 |   | 7 0 0 |   |  7 0 0 |
//AB = | -1 0 3 | x | 0 0 0 | = | -7 0 3 |
//                  | 0 0 1 |
//
//


//#########################################  Naive optimization #########################################  
// Time:  O(m * n * l), A is m x n matrix, B is n x l matrix
// Space: O(m * l)
class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) { 
		int m = A.size(), n = B.size(), p = B[0].size();
        vector<vector<int>> C(m, vector<int>(p, 0));
        for (int i = 0; i < m; i++) { 
			for (int j = 0; j < n; j++) { 
				if (A[i][j]) 
					for (int k = 0; k < p; k++) { // bug: k < n should be k < p
                        C[i][k] += A[i][j] * B[j][k];
					} 
			} 
		}
        return C;
    }
};

//#########################################  Sparse matrix (col #,value) ######################################### 
public int[][] multiply(int[][] A, int[][] B) {
    int n = A.length, m = A[0].length, mb = B[0].length;
    int[][] res = new int[n][mb];
    ArrayList<int[]>[] nzA = new ArrayList[m]; // for each col of A, nzA saves non-zero elements' row number and value
    for (int j = 0; j < m; j++) {
		nzA[j] = new ArrayList();
	}
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (A[i][j] != 0) nzA[j].add(new int[]{i, A[i][j]});
		}
	}
            
    for (int i = 0; i < m; i++)
        for (int[] a : nzA[i]) // put it to inner will be 200ms
            for (int j = 0; j < mb; j++)
                if (B[i][j] != 0) res[a[0]][j] += B[i][j] * a[1];
    return res;
}

//#########################################  Sparse matrix ######################################### 
vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
    const int rowA = A.size(), rowB = B.size();
    const int colA = A[0].size(), colB = B[0].size();
    vector<vector<int>> res(rowA, vector<int>(colB, 0));
    vector<vector<pair<int, int>>> sparseA(rowA, vector<pair<int,int>>());

    for(int i = 0; i < rowA; i++)
       for(int j = 0; j < colA; j++) {
        if(A[i][j] != 0)  {
			sparseA[i].emplace_back(j, A[i][j]); //non zero values A[i][j] stored at idx j
		}
    }
    for (int i = 0; i < rowA; ++i)  {
     for (auto noZeros : sparseA[i]) {
      for (int j = 0; j < rowB; ++j) {
          if(B[noZeros.first][j] != 0) {
			  res[i][j] += noZeros.second * B[noZeros.first][j]; 
		  }
	  }
	 }
	}
    return res;
}


//######################################### Pytonic ######################################### 
def multiply(self, A, B):
    cols = [[(j, b) for j, b in enumerate(col) if b]
            for col in zip(*B)]
    return [[sum(row[j]*b for j, b in col)
             for col in cols]
            for row in A]


//######################################### Pytonic + Sparse matrix######################################### 
class Solution(object):
    def multiply(self, A, B):
        """
        :type A: List[List[int]]
        :type B: List[List[int]]
        :rtype: List[List[int]]
        """
        if A is None or B is None: return None
        m, n, l = len(A), len(A[0]), len(B[0])
        if len(B) != n:
            raise Exception("A's column number must be equal to B's row number.")
        C = [[0 for _ in range(l)] for _ in range(m)]
        for i, row in enumerate(A):
            for k, eleA in enumerate(row):
                if eleA:
                    for j, eleB in enumerate(B[k]):
                        if eleB: C[i][j] += eleA * eleB
        return C
