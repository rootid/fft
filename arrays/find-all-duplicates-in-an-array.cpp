//Given an array of integers, 1 ≤ a[i] ≤ n (n = size of array), some elements
//appear twice and others appear once.
//Find all the elements that appear twice in this array.
//Could you do it without extra space and in O(n) runtime?
//Example:
//Input:
//[4,3,2,7,8,2,3,1]
//Output:
//[2,3]
//1 ≤ a[i] ≤ n i.e. all elements <= size of array

#include "../headers/global.hpp"

//######################################### O(n) #########################################
//Traverse the array. Do following for every index i of A[].
//{
//check for sign of A[abs(A[i])] ;
//if positive then
//   make it negative by   A[abs(A[i])]=-A[abs(A[i])];
//else  // i.e., A[abs(A[i])] is negative
//   this   element (ith element of list) is a repetition
//}

//Example: A[] =  {1, 1, 2, 3, 2}
//i=0;
//Check sign of A[abs(A[0])] which is A[1].  A[1] is positive, so make it
//negative.
//Array now becomes {1, -1, 2, 3, 2}
//i=1;
//Check sign of A[abs(A[1])] which is A[1].  A[1] is negative, so A[1] is a
//repetition.
//i=2;
//Check sign of A[abs(A[2])] which is A[2].  A[2] is  positive, so make it
//negative. '
//Array now becomes {1, -1, -2, 3, 2}
//i=3;
//Check sign of A[abs(A[3])] which is A[3].  A[3] is  positive, so make it
//negative.
//Array now becomes {1, -1, -2, -3, 2}
//i=4;
//Check sign of A[abs(A[4])] which is A[2].  A[2] is negative, so A[4] is a
//repetition

vector<int> findDuplicates(vector<int>& nums) {
    vector<int> result;
    int len = nums.size();
    if(len < 2) {
        return result;
    }
    for(int i=0;i<len;i++) {
        int idx = abs(nums[i]) - 1;
        if(nums[idx] < 0) {
            result.push_back( abs(nums[i]) );
        }
        nums[idx] = -nums[idx];
    }
    return result;
}
