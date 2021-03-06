//Given four lists A, B, C, D of integer values, compute how many tuples (i, j,
//k, l) there are such that A[i] + B[j] + C[k] + D[l] is zero.
//To make problem a bit easier, all A, B, C, D have same length of N where 0 ≤
//N ≤ 500. All integers are in the range of -228 to 228 - 1 and the result is
//guaranteed to be at most 231 - 1.
//Example:
//Input:
//A = [ 1, 2]
//B = [-2,-1]
//C = [-1, 2]
//D = [ 0, 2]
//Output:
//2
//Explanation:
//The two tuples are:
//1. (0, 0, 0, 1) -> A[0] + B[0] + C[0] + D[1] = 1 + (-2) + (-1) + 2 = 0
//2. (1, 1, 0, 0) -> A[1] + B[1] + C[0] + D[0] = 2 + (-1) + (-1) + 0 = 0

#include "../headers/global.hpp"

//The algorithm is to hash the sum of each elements in A and B, then find
//whether opposite number for sum of elements in C and D occurs.
//The time complexity is O(n^2), space complexity is O(n)
int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
     int count = 0;
     unordered_map<int, int> mp;
     for (int i = 0; i < A.size(); i++) {
         for (int j = 0; j < B.size(); j++) {
             mp[A[i]+B[j]]++;
         }
     }
     for (int i = 0; i < C.size(); i++) {
         for (int j = 0; j < D.size(); j++) {
             if (mp.find(-(C[i] + D[j])) != mp.end()) {
                 count += mp[-(C[i] + D[j])];
             }
         }
     }
     return count;
}
