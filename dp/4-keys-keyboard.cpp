//4 Keys Keyboard
//Imagine you have a special keyboard with the following keys:
//Key 1: (A): Prints one 'A' on screen.
//Key 2: (Ctrl-A): Select the whole screen.
//Key 3: (Ctrl-C): Copy selection to buffer.
//Key 4: (Ctrl-V): Print buffer on screen appending it after what has already
//been printed.
//Now, you can only press the keyboard for N times (with the above four keys),
//find out the maximum numbers of 'A' you can print on screen.
//Example 1:
//Input: N = 3
//Output: 3
//Explanation:
//We can at most get 3 A's on screen by pressing following key sequence:
//A, A, A
//Example 2:
//Input: N = 7
//Output: 9
//Explanation:
//We can at most get 9 A's on screen by pressing following key sequence:
//A, A, A, Ctrl A, Ctrl C, Ctrl V, Ctrl V
//Note:
//1 <= N <= 50
//Answers will be in the range of 32-bit signed integer.
//

//######################################### O(n^2)#########################################
//Say best[k] is the largest number of written 'A's possible after k
//keypresses.
//If the last move in some optimal solution of k keypresses was adding, then
//best[k] = best[k-1] + 1.
//Otherwise, if the last move was multiplying, then we multiplied by x, and
//best[k-(x+1)] = best[k-(x+1)] * x for some x < k-1.
//Taking the best of these candidates lets us find best[k] in terms of previous
//best[j], when j < k.


//######################################### O(2^n)#########################################
//cnstrnt : A->ctrl-c - cpoy ,ctr-v - paster,ctrl-a -buffer
//Ida
//1. Either use 3 step copy or 1 char type
//N = 3 -> o/p A
//N - key p cnt , o/p # of A
//N = 3
//4 -> 4A , (4) - kstrk -> Chars -> 4,1
//5 -> A, (4) -> 2,5
//6 -> 2 , (4) -> 4/6
//N = 8,  4 * (4)
//
//[1, 1, 1, 1, 5]
//
//We use i steps to reach maxA(i) then use the remaining n - i steps to reach n
//- i - 1 copies of maxA(i)
//For example:
//A, A, A, Ctrl A, Ctrl C, Ctrl V, Ctrl V
//Here we have n = 7 and we used i = 3 steps to reach AAA
//Then we use the remaining n - i = 4 steps: Ctrl A, Ctrl C, Ctrl V, Ctrl V, to
//reach n - i - 1 = 3 copies of AAA
//We either don't make copies at all, in which case the answer is just n, or if
//we want to make copies, we need to have 3 steps reserved for Ctrl A, Ctrl C,
//Ctrl V so i can be at most n - 3
public int maxA(int n) {
    int maxAs = n;
    for (int i = 1; i <= n - 3; i++)
        maxAs = Math.max(maxAs, maxA(i) * (n - i - 1)); //
    return maxAs;
}
//Why n-i-1 represents copies of maxA(i)? Because after you use i steps to
//reach maxA(i), you still have n -i steps. then you cost 2 more steps to do
//Ctrl-A and Ctrl-C, After this you have n-i-2 steps left, all the rest could
//be used to do Ctrl-V, so you increase n-i-2 copies, at last, you have the
//original copy, you need add it to the total num of copies. therefore, you
//have n-i-1 copies

//######################################### O(n^2)#########################################
class Solution {
    public int maxA(int N) {
        int[] best = new int[N+1];
        for (int k = 1; k <= N; ++k) {
            best[k] = best[k-1] + 1;
            for (int x = 0; x < k-1; ++x)
                best[k] = Math.max(best[k], best[x] * (k-x-1));
        }
        return best[N];
    }
}
public int maxA(int n) {
    int[] dp = new int[n + 1];
    for (int i = 0; i <= n; i++) {
        dp[i] = i;
        for (int j = 1; j <= i - 3; j++)
            dp[i] = Math.max(dp[i], dp[j] * (i - j - 1));
    }
    return dp[n];
}


//######################################### O(n^2)#########################################
def maxA(self, N):
    best = [0, 1]
    for x in xrange(2, N+1):
        cur = best[x-1] + 1
        for y in xrange(x-1):
            cur = max(cur, best[y] * (x-y-1))
        best.append(cur)
    return best[N]
