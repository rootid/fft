//Bitwise AND of Numbers Range
//
//Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND of all numbers in this range, inclusive.
//For example, given the range [5, 7], you should return 4.


#include "../headers/global.hpp"

//compute the unchanged part and & with the #
//############################################### GOOD ############################################### 
int rangeBitwiseAnd(int m, int n) {
   unsigned int mask = ~0;
    while ((m & mask) != (n & mask)) {
        mask <<= 1;
    }
    return m & mask;
    //or
    //return n & mask;
}

//############################################### GOOD ############################################### 
int rangeBitwiseAnd(int m, int n) {
      int i = 0;
      while(m != n ) {
          m=m>>1;
          n=n>>1;
          ++i;        
      }
      return m<<i;
}

//############################################### BAD  ############################################### 
int rangeBitwiseAnd(int m, int n) {
      int b = max(m,n);
      int a = min(m,n);
      int result = a;
      a += 1;
      for(int i=a;i<=b;i++) {
          result &= i;
      }
      return result;
}

int main() {

}
