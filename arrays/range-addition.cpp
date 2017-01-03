//Assume you have an array of length n initialized with all 0's and are given k update operations.
//Each operation is represented as a triplet: [startIndex, endIndex, inc] which increments each element of subarray A[startIndex ... endIndex] (startIndex and endIndex inclusive) with inc.
//Return the modified array after all k operations were executed.
//Example:
//Given:
//    length = 5,
//    updates = [
//        [1,  3,  2],
//        [2,  4,  3],
//        [0,  2, -2]
//    ]
//Output:
//    [-2, 0, 3, 5, 3]
//Explanation:
//Initial state:
//[ 0, 0, 0, 0, 0 ]
//After applying operation [1, 3, 2]:
//[ 0, 2, 2, 2, 0 ]
//After applying operation [2, 4, 3]:
//[ 0, 2, 5, 5, 3 ]
//After applying operation [0, 2, -2]:
//[-2, 0, 3, 5, 3 ]
//Hint:
//Thinking of using advanced data structures? You are thinking it too complicated.
//For each update operation, do you really need to update all elements between i and j?
//Update only the first and end element is sufficient.
//The optimal time complexity is O(k + n) and uses O(1) extra space.
#include "../headers/global.hpp"

//O(k+n)
vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
     vector<int> a(length,0);
     for (int i=0;i<updates.size();i++) {
         int s_idx = updates[i][0];
         int e_idx = updates[i][1];
         int inc = updates[i][2];
         if(s_idx > 0) { 
           a[s_idx - 1] -= inc;
         }
         a[e_idx] += inc;
     }
     int sum = a[length - 1];
     for(int i= length - 2;i>=0;i--) {
        a[i] += sum;
        sum = a[i];
     }
     return a;
}

//O(n^2)
vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
     vector<int> a(length,0);
     for (int i=0;i<updates.size();i++) {
         int s_idx = updates[i][0];
         int e_idx = updates[i][1];
         int inc = updates[i][2];
         for(int j=s_idx;j<=e_idx;j++) {
             a[j] += inc;
         }
     }
     return a;
}

int main() {
}
