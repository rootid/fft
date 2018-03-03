//Given a sequence of n integers a1, a2, ..., an, a 132 pattern is a
//subsequence ai, aj, ak such that i < j < k and ai < ak < aj. Design an
//algorithm that takes a list of n numbers as input and checks whether there is
//a 132 pattern in the list.
//Note: n will be less than 15,000.
//Example 1:
//Input: [1, 2, 3, 4]
//Output: False
//Explanation: There is no 132 pattern in the sequence.
//Example 2:
//Input: [3, 1, 4, 2]
//Output: True
//Explanation: There is a 132 pattern in the sequence: [1, 4, 2].
//Example 3:
//Input: [-1, 3, 2, 0]
//Output: True
//Explanation: There are three 132 patterns in the sequence: [-1, 3, 2], [-1,
//3, 0] and [-1, 2, 0].

#include "../headers/global.hpp"

bool find132pattern(vector<int>& nums) {
    int second_max = INT_MIN;
     stack<int> max_stack;
     for (int i = nums.size() - 1; i >= 0; --i) {
         if (nums[i] < second_max) {
           return true;
         } else {
           //found max elment
           while (!s.empty() && nums[i] > s.top()) {
             second_max = s.top();
             s.pop();
           }
         }
         max_stack.push(nums[i]);
     }
     return false;
}
//###### W/O Extra stack only indices #######
////
//This question gives us an array, let us find the 132 model, is the first
//number less than the second and third number, and the third number is less
//than the second number. Then we come to the order of the three numbers, first
//of all we come to the first number, this number needs the smallest, then if
//we find that the current number is greater than or equal to the back of a
//number, we continue to traverse down until the current number is less than
//the next A number stops. Then we find the second number, this number needs
//the largest, then if we find that the current number is less than or equal to
//the next number to continue traversing until the current number of heavy rain
//the next stop. Finally, we find the third figure, we verify that this figure
//is in the middle of the previous two figures, if not found, we will continue
//from the second digit of a position to re-find the three figures, see the
//code as follows:

bool find132pattern(vector<int>& nums) {
      if (nums.size() <= 2) return false;
      int n = nums.size(), i = 0, j = 0, k = 0;
      while (i < n) {
          while (i < n - 1 && nums[i] >= nums[i + 1]) ++i;
          j = i + 1;
          while (j < n - 1 && nums[j] <= nums[j + 1]) ++j;
          k = j + 1;
          while (k < n) {
              if (nums[k] > nums[i] && nums[k] < nums[j]) return true;
              ++k;
          }
          i = j + 1;
      }
      return false;
}


int main() {
}
