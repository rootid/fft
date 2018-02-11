//Find the Derangement of An Array
//In combinatorial mathematics, a derangement is a permutation of the elements of a set, such that no element appears in its original position.
//There's originally an array consisting of n integers from 1 to n in ascending order, you need to find the number of derangement it can generate.
//Also, since the answer may be very large, you should return the output mod 10^9 + 7.
//Example 1:
//Input: 3
//Output: 2
//Explanation: The original array is [1,2,3]. The two derangements are [2,3,1] and [3,1,2].
//Note:
//n is in the range of [1, 106].

//######################################### Recursion #########################################
//d(n)=(n−1)∗[d(n−1)+d(n−2)]
//Time complexity : O(n). memo array of length n is filled once only.
//Space complexity : O(n). memo array of length n is used.
public class Solution {
    public int findDerangement(int n) {
        Integer[] memo = new Integer[n + 1];
        return find(n, memo);
    }
    public int find(int n, Integer[] memo) {
        if (n == 0)
            return 1;
        if (n == 1)
            return 0;
        if (memo[n] != null)
            return memo[n];
        memo[n] = (int)(((n - 1L) * (find(n - 1, memo) + find(n - 2, memo))) % 1000000007);
        return memo[n];
    }
}

//######################################### DP #########################################
//d(n)=(n−1)∗[d(n−1)+d(n−2)] to dp[i]=(i−1)∗(dp[i−1]+dp[i−2])
public class Solution {
    public int findDerangement(int n) {
        if (n == 0)
            return 1;
        if (n == 1)
            return 0;
        int[] dp = new int[n + 1];
        dp[0] = 1;
        dp[1] = 0;
        for (int i = 2; i <= n; i++)
            dp[i] = (int)(((i - 1L) * (dp[i - 1] + dp[i - 2])) % 1000000007);
        return dp[n];
    }
}

//######################################### Constant space DP #########################################
//
public class Solution {
    public int findDerangement(int n) {
        if (n == 0)
            return 1;
        if (n == 1)
            return 0;
        int first = 1, second = 0;
        for (int i = 2; i <= n; i++) {
            int temp = second;
            second = (int)(((i - 1L) * (first + second)) % 1000000007);
            first = temp;
        }
        return second;
    }
}




//https://en.wikipedia.org/wiki/Derangement#Counting_derangements
//T(n) = T(n-1) + T(n-2)
//H(n) = (n-1) ( H(n-1)*H(n-2) )
//######################################### DP  #########################################
//Let D(N) be the required answer. The recursion for the number of derangements of N is: D(N) = (N-1) * (D(N-1) + D(N-2)).
//With this recursion in hand, the problem becomes similar to finding the N-th fibonacci number.
//To prove it, suppose there are people and hats labelled 1...N.
//We want the number of ways to put a hat on each person such that no person is wearing their hat.
//The first person has N-1 choices to put on a hat, say he wears hat X.
//Now consider what hat person X is wearing. Either he takes hat 1, and we have D(N-2) ways to arrange the remaining hats among people; or he doesn't take hat 1, which if we relabelled it as hat X, would have D(N-1) ways to arrange the remaining hats.
def findDerangement(self, N):
    MOD = 10**9 + 7
    X, Y = 1, 0
    for n in xrange(2, N+1):
        X, Y = Y, (n - 1) * (X + Y) % MOD
    return Y

//######################################### DP  #########################################
//For ith element, we have switch it with one of the previous numbers 1,2,...,i-1,
//and for each picked number j, for the positions left except the one take by i, j can take anyone of them.
//So there are dp[i - 2] permutation if j can take the original position of i, and
//dp[i - 1] permutations if j can not take the original position of i.
public int findDerangement(int n) {
	if(n <= 1) return 0;
    long[] dp = new long[n + 1];
    long mod = 1000000007;
    dp[2] = 1;
    for(int i = 3; i < dp.length; i++){
        dp[i] = (long)(i - 1) * (dp[i - 1] + dp[i - 2]) % mod;
    }
    return (int)dp[dp.length - 1];
}

//######################################### DP  #########################################
//The Staggered formula is D(n) = (n-1) [D(n-2) + D(n-1)]：
//For the k th element, it has k-1 positions and there are two possibilities for its position
//1. It's not in the first element, so it's going to be the same thing as D(n - 1)
//2. It's in the position of the first element, so there are two elements in the deranged position.
//So it's going to be the same thing as D(n - 2)
//so res = ((i-1)(dn1+dn2))%1000000007;*
//why we use long not int:
//a(11) = 14684570
//a(12) = 176214841
//a(13) = 12 * (a(12) + a(11)) = 2290792932 > Integer.MAX_VALUE

 public int findDerangement(int n) {
        long dn2 = 0, dn1 = 1;
        long res = n==1 ? 0 : 1;
        for (int i = 3; i <= n; i++){
            res = ((i-1) * (dn1+dn2))%1000000007;
            dn2 = dn1;
            dn1 = res;
        }
        return (int) res;
    }

// vim: set sw=2 sts=2 tw=120 et nospell :
