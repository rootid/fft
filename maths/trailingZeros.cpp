
Ruby          (1..13).map{|e| n/5**e}.reduce(:+)
              z=0; (1..13).each{|e| z+=n/5**e}; z
              n > 0 ? trailing_zeroes(n/=5) + n : 0              Maybe unsafe
              n > 0 ? n/5 + trailing_zeroes(n/5) : 0
              (n/=5) > 0 ? n + trailing_zeroes(n) : 0
              n > 0 ? (n/=5) + trailing_zeroes(n) : 0            Maybe unsafe

Python        return sum(n/5**e for e in range(1,14))
              return n and n/5 + self.trailingZeroes(n/5)

C++ and C     int z=0; while(n) z+=n/=5; return z;
              return n ? n + trailingZeroes(n/=5) : 0;           Maybe unsafe
              return n ? n/5 + trailingZeroes(n/5) : 0;
              return (n/=5) ? n + trailingZeroes(n) : 0;
              return n ? (n/=5) + trailingZeroes(n) : 0;         Maybe unsafe

Java and C♯   int z=0; while(n>0) z+=n/=5; return z;
              return n > 0 ? trailingZeroes(n/=5) + n : 0;       Maybe unsafe
              return n > 0 ? n/5 + trailingZeroes(n/5) : 0;
              return (n/=5) > 0 ? n + trailingZeroes(n) : 0;
              return n > 0 ? (n/=5) + trailingZeroes(n) : 0;     Maybe unsafe
