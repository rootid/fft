//Calculate the sum of two integers a and b, but you are not allowed to use the operator + and -.
//
//Example:
//Given a = 1 and b = 2, return 3.

#include<iostream>
using namespace std;
int getSum(int a, int b) {
  if(a == 0) {
    return b;
  }
  if(b == 0) {
    return a;
  }
  int sum = a;
  while(b != 0) {
    sum = a ^ b;
    b = (a&b) << 1; //carry
    a = sum;
  }
  return sum;
}

int recsum (int a,int b) {
  if(b == 0) {
    return a;
  } else {
    return recsum(a^b,(a&b) << 1);
  }
}

int main() {
}
