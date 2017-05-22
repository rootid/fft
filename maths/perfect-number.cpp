//Perfect Number
//We define the Perfect Number is a positive integer that is equal to the sum of all its positive divisors except itself.
//Now, given an integer n, write a function that returns true when it is a perfect number and false when it is not.
//Example:
//Input: 28
//Output: True
//Explanation: 28 = 1 + 2 + 4 + 7 + 14
//Note: The input number n will not exceed 100,000,000. (1e8)
//We can think about this problem this way, the sum of the divisor for a particular number can be forms like this.
//e.g.
//28 = 1 + (2 + 14) + (4 + 7)
//######################  add (index,divisor) pair ######################  
bool checkPerfectNumber(int num) {
    int total = 1;
    int i = 2;
    while (i * i < num) {
        if (num % i == 0)
            total += i + num/i;
        i += 1;
    }
    return num > 1 && total == num;
}

//######################  add (index,divisor) pair ######################  
bool checkPerfectNumber(int num) {
  if(num <= 0) return false;
  //for example, num=100;
  //sum = (1,100) + (2,50) + (4,25) + (5,20) 
  int sum = 0;
  int i;
  for(i = 1; i*i < num; ++i) {
      if(num%i == 0) { 
        sum += i + num/i;
      }
  }
  //adjust sum to get rid of the extra addition
  //for example when num=100, need to add 10 to sum
  //sum = (1,100) + (2,50) + (4,25) + (5,20) + 10 - 100
  //sum  = 1+100+2+50+4+25+5+20+10-100
  //Alternative 
  //if(i*i == num) {
  //    sum += sum + i;
  //} 
  //return 2* num == sum;
  //
  if(i*i == num) {
      sum = sum + i - num;
  } else {
      sum -= num;
  }
  return num == sum;
}

//######################  add (index,divisor) pair ######################  
bool checkPerfectNumber(int num) {
  if(num <= 1) return false;
    int sum = 0;
    int i = 1;
    while(i <= sqrt(num)){
        if(num % i == 0){
            sum += i + num / i;
        }
        i = i + 1;
    }
    return (sum - num) == num;
}

//######################  add (index,divisor) pair ######################  
bool checkPerfectNumber(int num) {
  if(num == 1) return false;
  int sum = 1;
  int tmpnum = num;
  for(int i = 2; i < tmpnum; i++){
      if(num % i == 0){
          sum += i;
          sum += num / i;
          tmpnum = num / i;
      }
  }
  if( sum == num) return true;
  return false;
}

//####################### pytonic ####################### 
//def checkPerfectNumber(self, num):
//    k = num.bit_length() / 2
//    return num > 1 and num == (2 << k) - 1 << k
//
//It just checks whether the number has a certain form (k+1 one-bits followed by k zero-bits). That form is necessary (at least for numbers in the allowed range, see Wikipedia) but not sufficient. It incorrectly returns True for the following numbers, so those should be added to the test suite:
//
//120, 2016, 32640, 130816, 523776, 2096128, 8386560

//##################### prime factoriization
//def prime_factorization(n):
//    d = 2
//    while d * d <= n:
//        expo = 0
//        while n % d == 0:
//            expo += 1
//            n /= d
//        if expo:
//            yield d, expo
//        d += 1
//    if n > 1:
//        yield n, 1
//
//########################  Time measurement ########################  
//from time import time
//t0 = time()
//for i in xrange(10**8 - 10000, 10**8):
//    list(prime_factorization(i))
//print time() - t0
//
//divsum = 1
//for p, e in prime_factorization(num):
//    divsum *= (p**(e+1) - 1) / (p - 1)
//return divsum == 2 * num
//
//
//################################ Unnecssary factoriization ################################ 
//def prime_factorization(N):
//  d = 2
//  while d * d <= n:
//    expo = 0
//    while N % d == 0:
//      expo += 1
//      N /= d
//    if expo:
//      yield (d, expo)
//    d += 1
//  if N > 1:
//    yield (N, 1)
//
//ans = 1
//for prime, expo in prime_factorization(abs(N)):
//  ans *= sum(prime ** k for k in xrange(expo + 1))
//return ans == 2*N
//
//prime_factorization does unnecessary work and yields unnecessary values. For example print list(prime_factorization(216)) prints [(2, 3), (3, 3), (4, 0), (5, 0), (6, 0), (7, 0), (8, 0), (9, 0), (10, 0), (11, 0), (12, 0), (13, 0), (14, 0)]. All those factors with exponent zero better shouldn't be yielded or even computed in the first place. Here's a better version which results in only [(2, 3), (3, 3)]:
