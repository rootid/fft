//Max Sum of Rectangle No Larger Than K
//Given a non-empty 2D matrix matrix and an integer k, find the max sum of a
//rectangle in the matrix such that its sum is no larger than k.
//Example:
//Given matrix = [
//  [1,  0, 1],
//  [0, -2, 3]
//]
//k = 2
//The answer is 2. Because the sum of rectangle [[0, 1], [-2, 3]] is 2 and 2 is
//the max number no larger than k (k = 2).
//Note:
//The rectangle inside the matrix must have an area > 0.
//What if the number of rows is much larger than the number of columns?
//
//The naive solution is brute-force, which is O((mn)^2). In order to be more
//efficient, I tried something similar to Kadane's algorithm. The only
//difference is that here we have upper bound restriction K. Here's the easily
//understanding video link for the problem "find the max sum rectangle in 2D
//array": Maximum Sum Rectangular Submatrix in Matrix dynamic programming/2D
//kadane (Trust me, it's really easy and straightforward).
//Once you are clear how to solve the above problem, the next step is to find
//the max sum no more than K in an array. This can be done within O(nlogn), and
//you can refer to this article: max subarray sum no more than k.
//For the solution below, I assume that the number of rows is larger than the
//number of columns. Thus in general time complexity is O[min(m,n)^2 * max(m,n)
//* log(max(m,n))], space O(max(m, n)).

//######################################## DP + Kadane algo O(n) ########################
//https://www.youtube.com/watch?v=yCQN096CwWM
int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
    //empty matrix
    if (matrix.empty()) {
      return 0;
    }
    int row = matrix.size(), col = matrix[0].size(), res = INT_MIN;
    for (int l = 0; l < col; ++l) {
        vector<int> sums(row, 0);
        for (int r = l; r < col; ++r) {
            for (int i = 0; i < row; ++i) {
                sums[i] += matrix[i][r]; //get all the sum for each row
            }
            // Find the max subarray no more than K
            set<int> accuSet;
            accuSet.insert(0);
            int curSum = 0, curMax = INT_MIN;
            for (int sum : sums) { //iterate over all rows
                curSum += sum;
                set<int>::iterator it = accuSet.lower_bound(curSum - k); //max sum no more than k
                if (it != accuSet.end()) { //it sum found
                  curMax = max(curMax, curSum - *it);
                }
                accuSet.insert(curSum);
            }
            res = std::max(res, curMax);
        }
    }
    return res;
}


//######################################## DP ########################
int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
    int m=matrix.size();
    if(m==0) return 0;
    int n=matrix[0].size();
    int res=INT_MIN;
    for(int i=0;i<n;i++) {  // the number of columns is smaller
        vector<int> sums(m,0);
        for(int j=i;j<n;j++) {
            for(int row=0;row<m;row++) {
                sums[row]+=matrix[row][j];
            }
            int ms = maxSumArray(sums, k);
            if (ms == k) return ms;
            if (ms < k && ms > res) res = ms;

        }
    }
    return res;
}
int maxSumArray(vector<int> & arr, int k) {
    int sum = 0, maxS = INT_MIN;
    for (int i = 0; i < arr.size(); i++) {  //it's a trick. Maybe O(n) to solve this problem
        sum += arr[i];
        maxS = max(sum, maxS);
        if (sum == k ) return sum;
        if (sum < 0) sum = 0;
    }
    if (maxS <= k) return maxS;
    maxS= INT_MIN;
    set<int>sums;
    sum = 0;
    sums.insert(0);
    for (int i = 0; i < arr.size(); i++) {
        sum += arr[i];
        auto it = sums.lower_bound(sum - k);
        if (it != sums.end()) maxS = max(sum - *it, maxS);
        sums.insert(sum);
    }
    return maxS;
}


//######################################## naive O(n^3) ########################
int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
  if(matrix.empty()) {
    return 0;
  }
  int rowSize = matrix.size(), colSize = matrix[0].size();
  int ret = INT_MIN;
  for(int l = 0; l < colSize; ++l) { //starting leftmost column;
      vector<int> sums(rowSize, 0); //store the row pre-sums;
      for(int c = l; c < colSize; ++c) { //try different ending columns;
          for(int r = 0; r < rowSize; ++r) { //sum them up in rows;
              sums[r] += matrix[r][c];
          }
          set<int> sums_set; //store the sums from the starting top-left;
          sums_set.insert(0); //as a sentinel;
          int maxSum = INT_MIN, sum = 0;
          for(int i = 0; i < rowSize; ++i) {
              sum += sums[i]; //the sum from the starting top-left to current position;
              auto iter = sums_set.lower_bound(sum-k); //check the possible sum candidates;
              if(iter != sums_set.end()) {
                maxSum = max(maxSum, sum-*iter); //found one, check it;
              }
              sums_set.insert(sum);
          }
          ret = max(ret, maxSum);
      }
  }
  return ret;
}



//######################################## naive O(n^4) ########################
//Compute Running sum
//And check area <= k
public int maxSumSubmatrix(int[][] matrix, int k) {

    if (matrix == null || matrix.length == 0 || matrix[0].length == 0)
        return 0;
    int rows = matrix.length, cols = matrix[0].length;
	//Compute running Sum
    int[][] areas = new int[rows][cols];
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int area = matrix[r][c];
            if (r-1 >= 0)
                area += areas[r-1][c];
            if (c-1 >= 0)
                area += areas[r][c-1];
            if (r-1 >= 0 && c-1 >= 0)
                area -= areas[r-1][c-1];
            areas[r][c] = area;
        }
    }
    int max = Integer.MIN_VALUE;
    for (int r1 = 0; r1 < rows; r1++) {
        for (int c1 = 0; c1 < cols; c1++) {
            for (int r2 = r1; r2 < rows; r2++) {
                for (int c2 = c1; c2 < cols; c2++) {
                    int area = areas[r2][c2];
                    if (r1-1 >= 0)
                        area -= areas[r1-1][c2];
                    if (c1-1 >= 0)
                        area -= areas[r2][c1-1];
                    if (r1-1 >= 0 && c1 -1 >= 0)
                        area += areas[r1-1][c1-1];
                    if (area <= k)
                        max = Math.max(max, area);
                }
            }
        }
    }
    return max;
}


//######################################## O(n^3 log n) ########################
// idea = to find max subarray with sum <= k in 1D array, and apply here: we find all rectangles bounded between r1 & r2, with columns from 0 to end. Pick a pair from tree.
public int maxSumSubmatrix(int[][] matrix, int k) {
    if (matrix == null || matrix.length == 0 || matrix[0].length == 0)
        return 0;
    int rows = matrix.length, cols = matrix[0].length;
    int[][] areas = new int[rows][cols];
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int area = matrix[r][c];
            if (r-1 >= 0)
                area += areas[r-1][c];
            if (c-1 >= 0)
                area += areas[r][c-1];
            if (r-1 >= 0 && c-1 >= 0)
                area -= areas[r-1][c-1];
            areas[r][c] = area;
        }
    }
    int max = Integer.MIN_VALUE;
    for (int r1 = 0; r1 < rows; r1++) {
        for (int r2 = r1; r2 < rows; r2++) {
            TreeSet<Integer> tree = new TreeSet<>();
            tree.add(0);    // padding
            for (int c = 0; c < cols; c++) {
                int area = areas[r2][c];
                if (r1-1 >= 0)
                    area -= areas[r1-1][c];
                Integer ceiling = tree.ceiling(area - k);
                if (ceiling != null)
                    max = Math.max(max, area - ceiling);
                tree.add(area);
            }
        }
    }
    return max;
}
