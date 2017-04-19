//Arithmetic Slices II - Subsequence
//A sequence of numbers is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.
//For example, these are arithmetic sequences:
//1, 3, 5, 7, 9
//7, 7, 7, 7
//3, -1, -5, -9
//The following sequence is not arithmetic.
//1, 1, 2, 5, 7
//A zero-indexed array A consisting of N numbers is given. A subsequence slice of that array is any sequence of integers (P0, P1, ..., Pk) such that 0 ≤ P0 < P1 < ... < Pk < N.
//A subsequence slice (P0, P1, ..., Pk) of array A is called arithmetic if the sequence A[P0], A[P1], ..., A[Pk-1], A[Pk] is arithmetic. In particular, this means that k ≥ 2.
//The function should return the number of arithmetic subsequence slices in the array A.
//The input contains N integers. Every integer is in the range of -231 and 231-1 and 0 ≤ N ≤ 1000. The output is guaranteed to be less than 231-1.
//Example:
//Input: [2, 4, 6, 8, 10]
//Output: 7
//Explanation:
//All arithmetic subsequence slices are:
//[2,4,6]
//[4,6,8]
//[6,8,10]
//[2,4,6,8]
//[4,6,8,10]
//[2,4,6,8,10]
//[2,6,10]

//############################################### O(N^2) ###############################################################
int numberOfArithmeticSlices(vector<int>& A) { 
  int res = 0;
  vector<unordered_map<int, int>> map(A.size()); //map will store the intermediate results T(i, d), with i indexed into the array and d as the key of the
    for (int i = 0; i < A.size(); i++) { //For each index i, we find the total number of "generalized" arithmetic subsequence slices ending at it with all possible differences. This is done by attaching A[i] to all slices of T(j, d) with j less than i.
        for (int j = 0; j < i; j++) {
            long long diff = (long long) A[i] - A[j];
            if (diff <= INT_MIN || diff > INT_MAX) {
              continue;
            }
            int dist = (int)diff;
            auto it = map[i].find(dist);
            int c1 = (it == map[i].end() ? 0 : it->second) ; //T(i, d)
            auto it1 = map[j].find(dist);
            int c2 = (it1 == map[j].end() ? 0 : it1->second); //T(j, d)
            res += c2;
            map[i][dist] = c1 + c2 + 1; //1 : count of the "two-element" slice (A[j], A[i])
        }
    }
    return res;
}

//############################################################################################################
int numberOfArithmeticSlices(vector<int>& A) { 
  int ans = 0;
  vector<unordered_map<long long, int>> dp(A.size());
  for (int i = 1; i < A.size(); i++) {
      for (int j = 0; j < i; j++) {
          long long dist = (long long)A[i] - A[j];
          auto it = dp[j].find(dist);
          int s = (it == dp[j].end() ? 0 : it->second) + 1;
          dp[i][dist] += s;
          ans += s;
      }
      ans -= i;
  }
  return ans; 
}
////
//class Solution(object):
//    def numberOfArithmeticSlices(self, A): 
//        ans = 0;
//        dp = [{} for i in xrange(len(A))]
//        for i in xrange(1, len(A)):
//            for j in xrange(0, i): 
//                dist = A[i] - A[j]
//                s = dp[j].get(dist, 0) + 1
//                dp[i][dist] = dp[i].get(dist, 0) + s
//                ans += s
//            ans -= i
//        return ans;
