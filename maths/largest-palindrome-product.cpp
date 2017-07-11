//Largest Palindrome Product
//Find the largest palindrome made from the product of two n-digit numbers.
//Since the result could be very large, you should return the largest palindrome mod 1337.
//Example:
//Input: 2
//Output: 987
//Explanation: 99 x 91 = 9009, 9009 % 1337 = 987
//Note:
//The range of n is [1,8].
//

//######################################### greedy ######################################### 
//The idea of this question is greedy:
//find the max number that product of two number
//try first largest palindrome, then second ...
//verify if the palindrome can be formed by production of two i digit number.
//repeat this until the palindrome has been found.
int largestPalindrome(int n) {
     if (n == 1) return 9;
     int upper = pow(10, n) - 1;
     int lower = pow(10, n-1);
     for (int i = upper; i >= lower; i--) {
         long cand = buildPalindrome(i);
         for (long j = upper; j*j >= cand; j--) {
             if (cand % j == 0 && cand / j <= upper) {
                 return cand % 1337;
             }
         }
     }
     return -1;
 }

private : 
long buildPalindrome(int n) {
     string s = to_string(n);
     reverse(s.begin(), s.end());
     return stol(to_string(n) + s);
}

//######################################### greedy JAVA ######################################### 


public int largestPalindrome(int n) {
  // if input is 1 then max is 9 
  if(n == 1){
      return 9;
  }
  // if n = 3 then upperBound = 999 and lowerBound = 99
  int upperBound = (int) Math.pow(10, n) - 1, lowerBound = upperBound / 10;
  long maxNumber = (long) upperBound * (long) upperBound;
  // represents the first half of the maximum assumed palindrom.
  // e.g. if n = 3 then maxNumber = 999 x 999 = 998001 so firstHalf = 998
  int firstHalf = (int)(maxNumber / (long) Math.pow(10, n));
  boolean palindromFound = false;
  long palindrom = 0;
  while (!palindromFound) {
      // creates maximum assumed palindrom
      // e.g. if n = 3 first time the maximum assumed palindrom will be 998 899
      palindrom = createPalindrom(firstHalf);
      // here i and palindrom/i forms the two factor of assumed palindrom
      for (long i = upperBound; upperBound > lowerBound; i--) {
          // if n= 3 none of the factor of palindrom  can be more than 999 or less than square root of assumed palindrom 
          if (palindrom / i > maxNumber || i * i < palindrom) {
              break;
          }
          // if two factors found, where both of them are n-digits,
          if (palindrom % i == 0) {
              palindromFound = true;
              break;
          }
      }
      firstHalf--;
  }
  return (int) (palindrom % 1337);
}
private long createPalindrom(long num) {
    String str = num + new StringBuilder().append(num).reverse().toString();
    return Long.parseLong(str);
}


// vim: set sw=2 sts=2 tw=120 et nospell : 
