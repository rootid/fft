//K Inverse Pairs Array
//Given two integers n and k, find how many different arrays consist of numbers from 1 to n such that there are exactly k inverse pairs.
//We define an inverse pair as following: For ith and jth element in the array, if i < j and a[i] > a[j] then it's an inverse pair; Otherwise, it's not.
//Since the answer may very large, the answer should be modulo 109 + 7.
//Example 1:
//Input: n = 3, k = 0
//Output: 1
//Explanation: 
//Only the array [1,2,3] which consists of numbers from 1 to 3 has exactly 0 inverse pair.
//Example 2:
//Input: n = 3, k = 1
//Output: 2
//Explanation: 
//The array [1,3,2] and [2,1,3] have exactly 1 inverse pair.
//Note:
//The integer n is in the range [1, 1000] and k is in the range [0, 1000].

//############################################### O(k*n^2) ######################################################
class Solution {
public:
    int kInversePairs(int n, int k) {
        vector<vector<int>> dp(n + 1, vector<int>(k+1, 0));
        dp[0][0] = 1;
        for(int i = 1; i <= n; ++i){
            for(int j = 0; j < i; ++j){ // In number i, we can create 0 ~ i-1 inverse pairs 
                for(int m = 0; m <= k; ++m){ //dp[i][m] +=  dp[i-1][m-j]
                    if(m - j >= 0 && m - j <= k){
                        dp[i][m] = (dp[i][m] + dp[i-1][m-j]) % mod; 
                    }
                }
            }
        }
        return dp[n][k];
    }
private:
    const int mod = pow(10, 9) + 7; //to avoid overflow
};



//############################################### O(n*L) ######################################################
//Consider this situation
//1. Dp[i-1][j-i] < mod.
//2. Before Dp[i][j] % mod, Dp[i][j] > mod, 
//3. After we did Dp[i][j] % mod, It give a chance to less than Dp[i-1][j-i]
//That is to say It is possible
//
//Dp[i][j] < Dp[i-1][j-1],
//and (dp[i][j] - dp[i-1][j-i] ) % mod < 0, 
//This is a negative number, not the answer we want, So, We must + mod

//dp[i][j] = dp[i-1][j] + dp[i-1][j-1] + dp[i-1][j-2] + ..... +dp[i-1][j - i + 1]
//Let's consider this example
//if i = 5
//
//dp[i][0] = dp[i-1][0] (creates 0 inverse pair)
//dp[i][1] = dp[i-1][0] (1) + dp[i-1][1] (0)  =  dp[i][0] + dp[i-1][1]
//dp[i][2] = dp[i-1][0] (2) + dp[i-1][1] (1) + dp[i-1][2] (0) = dp[i][1] + dp[i-1][2]
//.
//.
//.
//dp[i][4] = dp[i-1][0] (4) + dp[i-1][1] (3) + dp[i-1][2] (2) + dp[i-1][3] (1) + dp[i-1][4] (0)  = dp[i][3] + dp[i-1][4]
//Can you find the rules about above formula.
//if j < i , we can compute dp[i][j] = dp[i][j-1] +dp[i-1][j]
//
//So, how about j >= i
//We know if we add number i into permutation(0 .. i -1 ), i can create 0 ~i -1 inverse pair
//If j >= i , we still use dp[i][j] = dp[i][j-1] +dp[i-1][j].
//We must minus dp[i][j-i]. (In fact it minusdp[i-1][j-i], because everyj >= iin dp vecor,it minus dp[i-1][j-i]individually)
//For example, if i = 5
//
//dp[i][5] = dp[i][4] + dp[i-1][5] - dp[i-1][0]
//dp[i][6] = dp[i][5] + dp[i-1][6] - dp[i-1][1]
class Solution {
public:
    int kInversePairs(int n, int k) {
        vector<vector<int>> dp(n+1, vector<int>(k+1));
        dp[0][0] = 1;
        for(int i = 1; i <= n; ++i){
            dp[i][0] = 1;
            for(int j = 1; j <= k; ++j){
                dp[i][j] = (dp[i][j-1] + dp[i-1][j]) % mod;
                if(j - i >= 0) { //optmization
                    dp[i][j] = (dp[i][j] - dp[i-1][j-i] + mod) % mod; 
                    //It must + mod, If you don't know why, you can check the case 1000, 1000
                }
            }
        }
        return dp[n][k];
    }
private:
    const int mod = pow(10, 9) + 7;
};


//############################################### pytonic  ######################################################


//############################################### top-down ######################################################
//Let's try for a top-down dp. Suppose we know dp[n][k], the number of permutations of (1...n) with k inverse pairs.
//
//Looking at a potential recursion for dp[n+1][k], depending on where we put the element (n+1) in our permutation, we may add 0, 1, 2, ..., n new inverse pairs. For example, if we have some permutation of 1...4, then:
//
//5 x x x x creates 4 new inverse pairs
//x 5 x x x creates 3 new inverse pairs
//...
//x x x x 5 creates 0 new inverse pairs
//where in the above I'm representing any permutation of 1...4 with x's.
//Thus, dp[n+1][k] = sum_{x=0..n} dp[n][k-x].
//
//This dp has NK states with K/2 work, which isn't fast enough. We need to optimize further.
//
//Let ds[n][k] = sum_{x=0..k-1} dp[n][x].
//Then dp[n+1][k] = ds[n][k+1] - ds[n][k-n],
//and the left hand side is ds[n+1][k+1] - ds[n+1][k].
//Thus, we can perform all calculations in terms of ds.
//
//Finally, to save space, we will only store the two most recent rows of ds, using ds and new.
//
//In the code, we refer to -ds[n][k-n+1] instead of -ds[n][k-n] because the n being considered is actually n+1. For example, when n=2, we are appending information about ds[2][k] to new, so our formula of dp[n+1][k] = ds[n][k+1] - ds[n][k-n] is dp[2][k] = ds[1][k+1] - ds[1][k-1].
////def kInversePairs(self, N, K):
//    MOD = 10**9 + 7
//    ds = [0] + [1] * (K + 1)
//    for n in xrange(2, N+1):
//        new = [0]
//        for k in xrange(K+1):
//            v = ds[k+1]
//            v -= ds[k-n+1] if k >= n else 0
//            new.append( (new[-1] + v) % MOD )
//        ds = new
//    return (ds[K+1] - ds[K]) % MOD
//

// vim: set sw=2 sts=2 tw=120 et nospell : 
