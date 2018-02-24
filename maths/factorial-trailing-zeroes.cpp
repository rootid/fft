//Factorial Trailing Zeroes
//Given an integer n, return the number of trailing zeroes in n!.
//Note: Your solution should be in logarithmic time complexity.

//Traling zeros - count # of 5s in the prime factor of n!

//Trailing 0s in n! = Count of 5s in prime factors of n!
//                  = floor(n/5) + floor(n/25) + floor(n/125) + ..
//######################################### Maths #########################################
int trailingZeroes(int n) {
  int count = 0;
	int tmp=0;
	while(n/5>0) {
		tmp=n/5;
		count+=tmp;
		n=tmp;
  }
   // for (long i=5; n/i>=1; i *= 5) { //TO avoid overflow
   //     count += n/i;
   // }
   return count;
}

//######################################### Maths #########################################
//Ruby          (1..13).map{|e| n/5**e}.reduce(:+)
//              z=0; (1..13).each{|e| z+=n/5**e}; z
//              n > 0 ? trailing_zeroes(n/=5) + n : 0              Maybe unsafe
//              n > 0 ? n/5 + trailing_zeroes(n/5) : 0
//              (n/=5) > 0 ? n + trailing_zeroes(n) : 0
//              n > 0 ? (n/=5) + trailing_zeroes(n) : 0            Maybe unsafe
//Python        return sum(n/5**e for e in range(1,14))
//              return n and n/5 + self.trailingZeroes(n/5)
//C++ and C     int z=0; while(n) z+=n/=5; return z;
//              return n ? n + trailingZeroes(n/=5) : 0;           Maybe unsafe
//              return n ? n/5 + trailingZeroes(n/5) : 0;
//              return (n/=5) ? n + trailingZeroes(n) : 0;
//              return n ? (n/=5) + trailingZeroes(n) : 0;         Maybe unsafe
//Java and C♯   int z=0; while(n>0) z+=n/=5; return z;
//              return n > 0 ? trailingZeroes(n/=5) + n : 0;       Maybe unsafe
//              return n > 0 ? n/5 + trailingZeroes(n/5) : 0;
//              return (n/=5) > 0 ? n + trailingZeroes(n) : 0;
//              return n > 0 ? (n/=5) + trailingZeroes(n) : 0;     Maybe unsafe
