//Sqrt(x)
//Implement int sqrt(int x).
//Compute and return the square root of x.

#include<iostream>
using namespace std;


int mySqrt(int x) {

  if(x == 0) {
    return x; //avoid DIV by zero
  }
  int start = 1;
  int end = x;
  int tmp = start;
  while(start <= end) {
    int mid = start + (end-start)/2;
    //cout << mid << endl;
    if(mid == x/mid) {
      return mid;
    } 
    if(mid <= x/mid) {
      start = mid + 1;
      tmp = mid;
    } else {
      end = mid - 1;
    }
  }
  return tmp;
}

//BEST APPROACH

//As x is int, the maximum of x is 2^31-1, sqrt(x)'s most significant bit is at most 2^15. But (2^15 + 2^14)^2 exceeds int, not unsigned int, so I use unsigned int to represent sqrt(x) as res, so res * res will never overflow. Here is my code
//int sqrt(int x) {
//    unsigned int res = 0;
//    for (int i = 15; i >= 0; i--)
//    {
//        if ((res + (1 << i)) * (res + (1 << i)) <= x)
//            res += (1 << i);
//    }
//    return res;
//}
//
//What I meant is sqrt(x)'s most significant bit is at most 2^15. Also, you mentioned "2^30 makes sqrt(x) 2^15", this is true. But (2^15 + 2^14 + 2^13 + ... + 2^0)^2 is actually a negtive number (11111111111111100000000000000001) as highest bit is 1. That means MAX_INT could be represented with a number N, where N's most significant bit is 2^15.
//
int main(int argc, char *argv[])
{
  //int no = 9;
  int no = 1;
  int result = mySqrt(no);
  cout << " SQRT( " << no << " ) = " << result << endl;
  return 0;
}
