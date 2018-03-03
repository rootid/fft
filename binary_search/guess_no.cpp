//We are playing the Guess Game. The game is as follows:
//I pick a number from 1 to n. You have to guess which number I picked.
//Every time you guess wrong, I'll tell you whether the number is higher or
//lower.
//You call a pre-defined API guess(int num) which returns 3 possible results
//(-1, 1, or 0):
//-1 : My number is lower
// 1 : My number is higher
// 0 : Congrats! You got it!
//Example:
//N = 10, I pick 6.
//Return 6.
//
// Forward declaration of guess API.
// @param num, your guess
// @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
// Time limit  : 2126753390
//int guess(int num);
//class Solution {
//public:
//    int guessNumber(int n) {
//
//        for(int i=0;i<n;i++) {
//            if(guess(i) == 0) {
//                return i;
//            }
//        }
//        return n;
//    }
//};
#include<iostream>
using namespace std;

 //def guessNumber(self, n):
 //       lo, hi = 1, n
 //       while lo < hi:  // mid+1 < mid
 //           mid = (lo + hi) / 2
 //           if guess(mid) == 1:
 //               lo = mid + 1
 //           else:
 //               hi = mid
 //       return lo


int guess(int n) {
  if(n == 6) {
    return 0;
  } else if (n > 6) {
    return -1;
  }
  return 1;
}

int guessNumber(int n) {
  int low = 1;
  int high = n;
  int mid = 0;
  while(low < high) {
      mid = low + (high - low)/2;
      //cout << " L " << low << " M " << mid << " H " << high << endl;
      if(guess(mid) == 0) {
        return mid;
      } else if(guess(mid) == -1) {
           high = mid-1;
      } else {
          low = mid + 1;
      }
  }
  return low;  //base case n = 1
}

int main () {
  int r = guessNumber(10);
  cout << "R " << r << endl;
}
