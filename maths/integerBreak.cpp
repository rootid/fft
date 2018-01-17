//Given a positive integer n, break it into the sum of at least two positive integers and maximize the product of those integers. Return the maximum product you can get.
//
//For example, given n = 2, return 1 (2 = 1 + 1); given n = 10, return 36 (10 = 3 + 3 + 4).
//
//Note: You may assume that n is not less than 2 and not larger than 58.

int integerBreak(int n) {
  assert(n >=2 && n <=58 );
  if(n == 2) {
    return 1;
  }
  if(n == 3) {
    return 2;
  }
  int tmp = n%3;  
  switch(tmp) {
    case 1:
      return pow(3,(n/3)-1)*4;
    case 2:
      return pow(3,(n/3))*2;
    default:
      return pow(3,n/3);
  }
  return 0;
}

int main() {
}
