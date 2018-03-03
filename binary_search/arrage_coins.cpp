// Arranging Coins
//You have a total of n coins that you want to form in a staircase shape, where
//every k-th row must have exactly k coins.
//Given n, find the total number of full staircase rows that can be formed.
//n is a non-negative integer and fits within the range of a 32-bit signed
//integer.
//Example 1:
//n = 5
//The coins can form the following rows:
//¤
//¤ ¤
//¤ ¤
//Because the 3rd row is incomplete, we return 2.
//Example 2:
//n = 8
//The coins can form the following rows:
//¤
//¤ ¤
//¤ ¤ ¤
//¤ ¤
//Because the 4th row is incomplete, we return 3.
//[0,n]

//######################################## Iteration  #########################################
public int arrangeCoins(int n) {
      int stairCase = 0;
      while(n > 0){
          stairCase += 1;
          n -= stairCase;
      }
      return n == 0 ? stairCase : stairCase-1;
  }

//######################################## Recursion #########################################
public int arrangeCoins(int n) {
    //1,2,3,4
    int stairCase = 1;
    return arrangeCoinsHelper(stairCase,n);
}

int arrangeCoinsHelper(int k, int n) {
    if(n-k < 0) return n;
    return arrangeCoinsHelper(k+1, n-k);
}

int arrangeCoins(int n) {

      int l = 0;
      int r = n;
      long mid = 0;
      while(l <= r) {
          mid = l + (r -l)/2;
          if (mid * (mid+1)/2 > n) {
              r = mid - 1;
          } else {
              l = mid + 1;
          }
      }
      return r;
  }

//How to handle overflow [0,n+1]
//
//Input:
//2147483647
//Output:
//-1
//Expected:
//65535
int arrangeCoins(int n) {

     int l = 0;
     int r = n+1;
     long mid = 0;
     while(l < r) {
         mid = (l + r)/2;
         if (mid * (mid+1)/2 > n) {
             r = mid;
         } else {
             l = mid + 1;
         }
     }
     return l - 1;
 }
