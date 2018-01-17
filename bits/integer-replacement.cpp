//Integer Replacement
//Given a positive integer n and you can do operations as follow:
//If n is even, replace n with n/2.
//If n is odd, you can replace n with either n + 1 or n - 1.
//What is the minimum number of replacements needed for n to become 1?
//Example 1:
//Input:
//8
//Output:
//3
//Explanation:
//8 -> 4 -> 2 -> 1
//Example 2:
//Input:
//7
//Output:
//4
//Explanation:
//7 -> 8 -> 4 -> 2 -> 1
//or
//7 -> 6 -> 3 -> 2 -> 1


//######################################################## greedy ######################################################## 
//pick n+1/n-1 based on whether it is divisible by 4 or not
int integerReplacement(int n) {
    if(n == INT_MAX) return 32; //n = 2^31-1;
    int count = 0;
    while(n>1){
        if(n%2==0) n/=2;
        else{
            if((n+1)%4 == 0&&(n-1!=2)) n++;
            else n--;
        }
        count++;
    }
    return count;
}
//################################# greedy proof
//The greedy heuristic of the above solution: the "best" case of this problem is to divide as much as possible.
//Each time we divide by 2 we shift right one bit. We can only divide when the right most bit is 0 (n is even).
//When the right most bit is 1, we have 2 choices: n+1 or n-1. We choose n+1 when we can eliminate more 1-bit so we have a longer trailing 0 (so we can divide more).
//Example:
//1011 -> 1100
//1011 -> 1010
//
//Proof:
//Let n = 2k+1. Let count is the number of steps.
//
//Option 1: n+1 == 2k+2; (n+1) / 2 == k+1 (count: 2)
//Option 2: n-1 == 2k; (n-1) / 2 == k (count: 2)
//
//If (n+1) % 4 == 0, then (k+1) % 2 == 0 -> k will be odd.
//Let k = 2h + 1
//Continue option 1: (k+1) / 2 == h+1 (count: 3)
//Continue option 2:
//
//if we choose to +1 here: k+1 == 2h+2; (k+1) / 2 == h+1 (count: 4) -> worse than option 1
//if we choose to -1 here: k-1 == 2h; (k-1) / 2 == h (count: 4) -> need 4 steps to reach h, while option 1 need 3 steps to reach h+1. If h is even, option 1 can keep on dividing. If h is odd, option 1 can simply -1 to reach h (count: 4), so it will never be worse than option 2.
//Therefore, when (n+1) % 4 == 4, using option 1 (n+1) is always better or equally good compare with using option 2 (n-1).
//
//The proof is a little sloppy and it hasn't fully proved the correctness. However, I hope it give you the idea.
//
//############################################# Induction proof ############################################# 
//For any odd number k >= 3, f(k-1) <= f(k) and f(k+1) <= f(k), where f denotes "integerReplacement(int n)".
//In another words, for two adjacent numbers the even one needs less or equal steps to get to 1 than that of the odd one.
//This can be proven by induction:
//for 2,3,4,5,6 we have f(2) = 1, f(3) = 2, f(4) = 2, f(5) = 3, f(6) = 3 which agree with the statement
//for and odd number k let's prove f(k-1) <= f(k) (f(k+1) < f(k) can be proven in the same manner):
//for k-1: k-1 -> (k-1)/2
//for k: a. k -> k-1 -> (k-1)/2 OR
//b. k -> k+1->(k+1)/2
//if we take path a, it's obvious that k takes one more step than k-1 to get (k-1)/2 so f(k-1) < f(k)
//if we take path b,
//if (k+1)/2 is even and (k-1)/2 is odd, then for k-1 we can also take two step to reach (k+1)/2 by k-1 -> (k-1)/2 - > (k+1)/2, so f(k-1) = f(k)
//if (k+1)/2 is odd number, by induction we know f[(k-1)/2] <= f[(k+1)/2], so overall f(k-1) < f(k) (because it takes one step from k-1 to (k-1)/2 but two steps from k to (k+1)/2)
//So in all the cases f(k-1) <= f(k)
//Corollary:
//For our problem: if we have an odd number we need increase or decrease to make it be 4n. The reason is for an odd number after two steps it could become an odd or even number differed by 1 and the theorm above tell us you better become an even number after two steps.
//Why 3 is an exception? The theorem only applies for odd numbers >= 3 because f(2) > f(1) is an exception!
int integerReplacement(int n) {
        if(n == INT_MAX) return 32;
        if (n <= 2) return n-1;
        if (n == 3) return 2;
        if (n % 2 == 0) {
          return integerReplacement(n/2)+1;
        } //else {
        return (n&2) == 0 ? integerReplacement(n-1)+1 : integerReplacement(n+1)+1;
        //}
}

//######################################## iterative  ####################################### 
int integerReplacement(int n) {
     int counter = 0;
     if(n == INT_MAX) return 32;
     while(n > 1){
         counter++;
         if(n & 1)
             if((n & 2) && n != 3) n++;
             else n--;
         else
             n >>= 1;
     }
     return counter;
}

//######################################## bitcount ####################################### 
//1.If n is even, halve it.
//2.If n=3 or n-1 has less 1's than n+1, decrement n.
//3.Otherwise, increment n.
public int integerReplacement(int n) {
    int c = 0;
    while (n != 1) {
        if ((n & 1) == 0) {
            n >>>= 1;
        } else if (n == 3 || Integer.bitCount(n + 1) > Integer.bitCount(n - 1)) {
            --n;
        } else {
            ++n;
        }
        ++c;
    }
    return c;
}

//######################################## pytonic  ####################################### 
//class Solution(object):
//    def integerReplacement(self, n):
//        """
//        :type n: int
//        :rtype: int
//        """
//        if n == 1:
//            return 0
//        if n % 2:
//            return 1 + min(self.integerReplacement(n+1), self.integerReplacement(n-1))
//        else:
//            return 1 + self.integerReplacement(n/2)
