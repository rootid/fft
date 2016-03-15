//Bitwise AND of Numbers Range
#include<iostream>
using namespace std;

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
