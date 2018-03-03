//Sum of Square Numbers
//Given a non-negative integer c, your task is to decide whether there're two integers a and b such that a^2 + b^2 = c.
//Example 1:
//Input: 5
//Output: True
//Explanation: 1 * 1 + 2 * 2 = 5
//Example 2:
//Input: 3
//Output: False


//########################### 2 pointer pruning - O(n) ###########################
public boolean judgeSquareSum(int c) {
    if(c < 0) return false;
    int right = (int)Math.sqrt(c);
    int left = 0;
    while(left <= right) {
        int result = left*left + right*right;
        if(result == c) return true;
        if(result > c) right -= 1;
        else left += 1;
    }
    return false;
}

//########################### 2 pointer pruning - O(n^2) ###########################
public boolean judgeSquareSum(int c) {
  int limit = c/2;
  for(int i=0;i<=limit;i++) {
       for(int j=0;j<=limit;j++) {
          if(i*i + j*j == c) return true;
       }
  }
  return false;
}


//########################### 2 pointer pruning ###########################
bool judgeSquareSum(int c) {
   int root = (int) sqrt(c);
   int left = 0, right = root;
   while (left <= right) {
       if (left * left + right * right < c) {
           left++;
       } else if (left * left + right * right > c) {
           right--;
       } else {
           return true;
       }
   }
   return false;
}

//############################################### Fast pruning ######################################################
//a*a = c - b*b <= c, because b*b >= 0, and 0 <= a <= sqrt(c) is a necessary condition for a solution.
//
//Let's try each 0 <= a <= sqrt(c). For each choice of a, we must have b*b = c - a*a. There will be a solution if and
//only if the right-hand-side is a perfect square
//a can be further constrained by a*a <= c/2. If there is no solution in this range for a, then there cannot be a
//solution when c/2 < a*a <= c.
//Proof: if there is one solution with a * a > c/2, then the corresponding b must satisfy b * b <= c/2. Consequently,
//the solution (b, a) should have already been found.
#include <cmath>
class Solution {
public:
    bool judgeSquareSum(int c) {
        auto end = (int)std::sqrt(c / 2.0);
        for (int a = 0; a <= end; a++){
            auto bs = c - a * a; // b^2
            auto b = (int)std::sqrt(bs);
            if (b * b == bs)
                return true;
        }
        return false;
    }
};


//############################################### pytonic ######################################################

def judgeSquareSum(self, c):
    def is_square(N):
        return int(N**.5)**2 == N

    return any(is_square(c - a*a)
                for a in xrange(int(c**.5) + 1))


//######################################### Number Theory  #########################################
//I happen to have given a little talk about just this topic a while back in a number theory seminar. This problem is
//completely solved, in the sense of being reduced to simple checks of a number's prime factorization. A natural number
//is...
//... a square if and only if each prime factor occurs to an even power in the number's prime factorization.
//... a sum of two squares if and only if each prime factor that's 3 modulo 4 occurs to an even power in the number's prime factorization.
//... a sum of three squares if and only if it's not of the form 4a(8b+7) with integers a and b.
//... a sum of four squares. Period. No condition. You never need more than four.
//Of course single squares can also be identified by comparing a given number with the square of the rounded root of the
//number.
//The problem statement says "1, 4, 9, 16, ...", for some reason apparently excluding 0, but it really is a perfect
//square and the above theorems do consider it one. With that, you can for example always extend a sum of two squares
//a2+b2 to the sum of three squares a2+b2+02. Put differently, if n isn't a sum of three squares, then it also isn't a
//sum of two squares. So you can read the above statements as "... a sum of m (or fewer) squares". Thanks to ruben3 for
//asking about this in the comments.
//In my above solutions, I first divide the given number by 4 as often as possible and then do the three-squares check.
//Dividing by 4 doesn't affect the other checks, and the n % 8 == 7 is cheaper than the prime factorization, so this
//saves time in cases where we do need four squares.
//Armed with just the knowledge that you never need more than four squares, it's also easy to write O(n) solutions,
//e.g.:
//



//######################################### Number theory O(n) #########################################
int numSquares(int n) {
    int ub = sqrt(n);
    for (int a=0; a<=ub; ++a) {
        for (int b=a; b<=ub; ++b) {
            int c = sqrt(n - a*a - b*b);
            if (a*a + b*b + c*c == n)
                return !!a + !!b + !!c;
        }
    }
    return 4;
}

//######################################### No prime factorization  #########################################
int numSquares(int n) {
    while (n % 4 == 0)
        n /= 4;
    if (n % 8 == 7)
        return 4;
    for (int a=0; a*a<=n; ++a) {
        int b = sqrt(n - a*a);
        if (a*a + b*b == n)
            return 1 + !!a;
    }
    return 3;
}


//######################################### cpp #########################################
int numSquares(int n) {
    while (n % 4 == 0)
        n /= 4;
    if (n % 8 == 7)
        return 4;
    bool min2 = false;
    for (int i=2; i<=n; ++i) {
        if (i > n/i)
            i = n;
        int e = 0;
        while (n % i == 0)
            n /= i, ++e;
        if (e % 2 && i % 4 == 3)
            return 3;
        min2 |= e % 2;
    }
    return 1 + min2;
}

// vim: set sw=2 sts=2 tw=120 et nospell :
