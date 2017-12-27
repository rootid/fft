//Sum of Two Integers
//Calculate the sum of two integers a and b, but you are not allowed to use the operator + and -.
//
//Example:
//Given a = 1 and b = 2, return 3.

#include<iostream>
using namespace std;

//######################################### Recursion ######################################### 
public int getSum(int a, int b) {
    if(b == 0) return a;
    return getSum(a^b, (a&b) << 1);
}


//######################################### Iteration ######################################### 
public int getSum(int a, int b) { 
    int sum = a;
    while(b != 0) {
      sum = a ^ b; //XOR sum
      b = (a&b) << 1; //carry
      a = sum;
    }
    return sum;
}

//######################################### Iteration ######################################### 
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

//######################################### Recursion ######################################### 
int recsum (int a,int b) {
  if(b == 0) {
    return a;
  } else {
    return recsum(a^b,(a&b) << 1);
  }
}

/* vim: set ts=4 sw=4 sts=4 tw=120 et: */
