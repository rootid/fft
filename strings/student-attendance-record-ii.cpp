//Student Attendance Record II
//Given a positive integer n, return the number of all possible attendance
//records with length n, which will be regarded as rewardable. The answer may
//be very large, return it after mod 10^9 + 7.
//A student attendance record is a string that only contains the following
//three characters:
//'A' : Absent.
//'L' : Late.
//'P' : Present.
//A record is regarded as rewardable if it doesn't contain more than one 'A'
//(absent) or more than two continuous 'L' (late).
//Example 1:
//Input: n = 2
//Output: 8
//Explanation:
//There are 8 records with length 2 will be regarded as rewardable:
//"PP" , "AP", "PA", "LP", "PL", "AL", "LA", "LL"
//Only "AA" won't be regarded as rewardable owing to more than one absent
//times.
//Note: The value of n won't exceed 100,000.

//######################################### Recurrencce #########################################
from collections import deque

class Solution(object):
    def checkRecord(self, n):
        """
        :type n: int
        :rtype: int
        """
        MOD = 1000000007
        withA = deque([1, 3, 8])
        withoutA = deque([1, 2, 4])
        if n < 3:
            return withA[n]
        for i in range(3, n+1):
            withoutA.append(sum(withoutA) % MOD)
            withA.append((sum(withA) + withoutA[-1]) % MOD)
            withoutA.popleft()
            withA.popleft()
        return withA[-1]
//Recurrence formula:
//Let Q(n) be the solution of the the question, namely the number of all
//rewardable records.
//Let R(n) be the number of all rewardable records without A.
//
//Thinking the problem as replacing Ps and As on an array of Ls instead. Since
//the constraint is no more than 3 continuous Ls is allowed. For a n-size
//array, let's just look into the first 3 places, since there must be at least
//on replacement been taken place there:
//
//First, let's consider the case we replacing with P. There're 3 cases:
//
//P??: meaning we replace the first L with P. Doing so will shrink the problem
//size by one, so the number of this case is Q(n-1);
//LP?: meaning we replace the second L with P. The first place got to be L
//since the case where P in the first place is being considered above. So the
//number of this case is Q(n-2);
//LLP: meaning we replace the third L with P. Leaving us the number of Q(n-3);
//Now let's consider the case we replacing with A:
//
//A??: This we narrow down the problem size by one, and for the rest places
//there must be no As. So the number is R(n-1);
//LA?: this will be R(n-2);
//LLA: this will be R(n-3);
//It's easy to see that the recurrence formula of R is just similar to the
//first 3 cases combined, namely:
//R(n) = R(n-1) + R(n-2) + R(n-3)
//
//So the recurrence formula of Q is:
//
//Q(n) = Q(n-1) + Q(n-2) + Q(n-3) + R(n-1) + R(n-2) + R(n-3)
//     = Q(n-1) + Q(n-2) + Q(n-3) + R(n)

//######################################### DFS #########################################
class Solution {
public:
int checkRecord(int n) {
    long long res = 0;
    dfs(n, 0, 0, 0, res);
    return res % (int(pow(10,9))+7);
}
void dfs(int n, int s, int A, int L, long long& res){
    if(s == n){
        res++;
        return;
    }
    dfs(n, s+1, A, 0, res);//add "P"
    if(A < 1){
        dfs(n, s+1, A + 1, 0, res);
    }
    if(L <= 1){
        dfs(n, s+1,A, L + 1, res);
    }
}
};
//######################################### DP O(n) #########################################
//Let f[i][j][k] denote the # of valid sequences of length i where:
//There can be at most j A's in the entire sequence.
//There can be at most k trailing L's.
//We give the recurrence in the following code, which should be
//self-explanatory, and the final answer is f[n][1][2].

public int checkRecord(int n) {
    final int MOD = 1000000007;
    int[][][] f = new int[n + 1][2][3];

    f[0] = new int[][]{{1, 1, 1}, {1, 1, 1}};
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 3; k++) {
                int val = f[i - 1][j][2]; // ...P
                if (j > 0) val = (val + f[i - 1][j - 1][2]) % MOD; // ...A
                if (k > 0) val = (val + f[i - 1][j][k - 1]) % MOD; // ...L
                f[i][j][k] = val;
            }
    return f[n][1][2];
}
//######################################### O(log n) #########################################
//The runtime of this solution is clearly O(n), using linear space (which can
//be easily optimized to O(1) though). Now, let's see how to further improve
//the runtime.
//In fact, if we treat f[i][][] and f[i-1][][] as two vectors, we can represent
//the recurrence of f[i][j][k] as follows:

//f[i][0][0]   | 0 0 1 0 0 0 |   f[i-1][0][0]
//f[i][0][1]   | 1 0 1 0 0 0 |   f[i-1][0][1]
//f[i][0][2] = | 0 1 1 0 0 0 | * f[i-1][0][2]
//f[i][1][0]   | 0 0 1 0 0 1 |   f[i-1][1][0]
//f[i][1][1]   | 0 0 1 1 0 1 |   f[i-1][1][1]
//f[i][1][2]   | 0 0 1 0 1 1 |   f[i-1][1][2]
//Let A be the matrix above, then f[n][][] = A^n * f[0][][], where f[0][][] =
//[1 1 1 1 1 1]. The point of this approach is that we can compute A^n using
//exponentiating by squaring (thanks to @StefanPochmann for the name
//correction), which will take O(6^3 * log n) = O(log n) time. Therefore, the
//runtime improves to O(log n), which suffices to handle the case for much
//larger n, say 10^18.
//Update: The final answer is f[n][1][2], which involves multiplying the last
//row of A^n and the column vector [1 1 1 1 1 1]. Interestingly, it is also
//equal to A^(n+1)[5][2] as the third column of A is just that vector. Credit
//to @StefanPochmann.

//f[i][0][0]   | 0 0 1 0 0 0 |   f[i-1][0][0]
//f[i][0][1]   | 1 0 1 0 0 0 |   f[i-1][0][1]
//f[i][0][2] = | 0 1 1 0 0 0 | * f[i-1][0][2]
//f[i][1][0]   | 0 0 1 0 0 1 |   f[i-1][1][0]
//f[i][1][1]   | 0 0 1 1 0 1 |   f[i-1][1][1]
//f[i][1][2]   | 0 0 1 0 1 1 |   f[i-1][1][2]
//The top row says that:
//
//f[i][0][0] = f[i-1][0][2]
//Why? We want at most 0 trailing L's, so the previous (i-1) case where we
//allow 0, 1, or 2 L's, we can simply add a 'P', and that get's the current (i)
//case. We don't need any of the f[i-1][1][x] cases, since we don't allow A's.
//And we don't need the f[i-1][0] and f[i-1][1] cases because those are already
//counted in the f[i-1][2] case.
//
//Moving on:
//
//f[i][0][1] = f[i-1][0][0] + f[i-1][0][2]
//Why? We want at most 1 trailing L, so we can either take a case with no L's
//(f[i-1][0]) and add an 'L', or we can take one with up to 2 L's (f[i-1][2])
//and add a 'P'. f[i-1][0][1] isn't included here because adding an 'L' to it
//would give us 2 L's, which is outside the desired k of 1, and adding a 'P' to
//it is already covered by f[i-1][2], which covers 0, 1, or 2 trailing L's.

final int MOD = 1000000007;
final int M = 6;

int[][] mul(int[][] A, int[][] B) {
    int[][] C = new int[M][M];
    for (int i = 0; i < M; i++)
        for (int j = 0; j < M; j++)
            for (int k = 0; k < M; k++)
                C[i][j] = (int) ((C[i][j] + (long) A[i][k] * B[k][j]) % MOD);
    return C;
}


int[][] pow(int[][] A, int n) {
    int[][] res = new int[M][M];
    for (int i = 0; i < M; i++)
        res[i][i] = 1;
    while (n > 0) {
        if (n % 2 == 1)
            res = mul(res, A);
        A = mul(A, A);
        n /= 2;
    }
    return res;
}

public int checkRecord(int n) {
    int[][] A = {
            {0, 0, 1, 0, 0, 0},
            {1, 0, 1, 0, 0, 0},
            {0, 1, 1, 0, 0, 0},
            {0, 0, 1, 0, 0, 1},
            {0, 0, 1, 1, 0, 1},
            {0, 0, 1, 0, 1, 1},
    };
    return pow(A, n + 1)[5][2];
}

//######################################### O(n) #########################################
// > A && LL
static final int M = 1000000007;

public int checkRecord(int n) {
    long[] PorL = new long[n + 1]; // ending with P or L, no A
    long[] P = new long[n + 1]; // ending with P, no A
    PorL[0] = P[0] = 1; PorL[1] = 2; P[1] = 1;

    for (int i = 2; i <= n; i++) {
        P[i] = PorL[i - 1];
        PorL[i] = (P[i] + P[i - 1] + P[i - 2]) % M;
    }

    long res = PorL[n];
    for (int i = 0; i < n; i++) { // inserting A into (n-1)-length strings
    	long s = (PorL[i] * PorL[n - i - 1]) % M;
        res = (res + s) % M;
    }

    return (int) res;
}


//dp[i]the number of all possible attendance (without 'A') records with length
//i :
//end with "P": dp[i-1]
//end with "PL": dp[i-2]
//end with "PLL": dp[i-3]
//end with "LLL": is not allowed
//so dp[i] = dp[i-1] + dp[i-2] + dp[i-3]
//the number of all possible attendance (with 'A') records with length n:
//∑dp[i] *dp[n-1-i] i = 0,1,...,n-1
//For n=3, it becomes dp0dp2+dp1dp1+dp2dp0, When you place A at pos1, then P&L
//can be placed in dp0dp2 ways.
//Time Complexity O(n)
//Space Complexity O(n)
//(In code nums[i+1] means dp[i])

class Solution(object):
    def checkRecord(self, n):
        if n == 1:
            return 3
        if n == 0:
            return 0
        nums = [1, 1, 2]
        i = 2
        while i < n:
            nums.append((nums[i] + nums[i-1] + nums[i-2])% 1000000007)
            i += 1
        result = (nums[n] + nums[n-1] + nums[n-2]) % 1000000007
        for i in range(n):
            result += nums[i+1] * nums[n-i] % 1000000007
            result %= 1000000007
        return result

