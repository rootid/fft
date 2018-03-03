//You are climbing a stair case. It takes n steps to reach to the top.
//Each time you can either climb 1 or 2 steps. In how many distinct ways can
//you climb to the top?
//Note: Given n will be a positive integer.
//Example 1:
//Input: 2
//Output:  2
//Explanation:  There are two ways to climb to the top.
//1. 1 step + 1 step
//2. 2 steps
//Example 2:
//Input: 3
//Output:  3
//Explanation:  There are three ways to climb to the top.
//1. 1 step + 1 step + 1 step
//2. 1 step + 2 steps
//3. 2 steps + 1 step/
//


//######################################### DP O(n)#########################################
public int climbStairs(int n) {
    int a = 1, b = 1;
    while (n-- > 0)
        a = (b += a) - a;
    return a;
}


//######################################### DP O(n)#########################################
int climbStairs(int n) {
    int a = 1, b = 1;
    while(--n >= 1){
        a += b;
        b = a - b;
    }
    return a;
}


//######################################### DP O(n)#########################################
public int climbStairs(int n) {
    if(n==0||n==1) return  1;
    int stepOne=1,stepTwo=1;
    int result=0;
    for(int i=2;i<=n;i++){
        result= stepOne+stepTwo;
        stepTwo= stepOne;
        stepOne= result;
    }
    return result;
}

//######################################### DP O(n)#########################################
public int climbStairs(int n) {
    if(n <= 0) return 0;
    if(n == 1| n == 2) return n;
    int[] storeArr = new int[n];
    storeArr[0] = 1; storeArr[1] = 2;
    for(int i=2;i<n;i++)
        storeArr[i] = storeArr[i-1] + storeArr[i-2];
    return storeArr[n-1];
}

//######################################### DP O(log n)#########################################
//The idea is to use the matrix power. In fact, [f(n), f(n - 1); f(n - 1), f(n
//- 2)] = [1, 1; 1, 0] ^ n for n >= 2.
//And similar to the problem Pow(x, n), the power of a matrix can be computed
//in O(logn) time.
class Solution {
public:
    int climbStairs(int n) {
		if (n < 2) return n;
        vector<int> fibs = {1, 1, 1, 0};
        vector<int> ans = fibPower(fibs, n);
        return ans[0];
    }
private:
    vector<int> matrixProd(vector<int>& l, vector<int>& r) {
        vector<int> ans(4, 0);
        ans[0] = l[0] * r[0] + l[1] * r[2];
        ans[1] = l[0] * r[1] + l[1] * r[3];
        ans[2] = l[2] * r[0] + l[3] * r[2];
        ans[3] = l[2] * r[1] + l[3] * r[3];
        return ans;
    }
    vector<int> fibPower(vector<int>& fibs, int n){
		if (n == 1) return fibs;
        vector<int> half = fibPower(fibs, n / 2);
        vector<int> ans = matrixProd(half, half);
        if (n % 2 == 0) return ans;
        ans[1] = (ans[0] += ans[1]) - ans[1];
        ans[3] = (ans[2] += ans[3]) - ans[3];
        return ans;
    }
};

//######################################### DP O(log n)#########################################
class Solution:
    # @param {integer} n
    # @return {integer}
    def climbStairs(self, n):
        if n  < 2:
            return n
        fibs = [1, 1, 1, 0]
        ans = self.fibsPower(fibs, n)
        return ans[0]

    def matrixProd(self, l, r):
        ans = [0] * 4
        ans[0] = l[0] * r[0] + l[1] * r[2]
        ans[1] = l[0] * r[1] + l[1] * r[3]
        ans[2] = l[2] * r[0] + l[3] * r[2]
        ans[3] = l[2] * r[1] + l[3] * r[3]
        return ans

    def fibsPower(self, fibs, n):
        if n == 1:
            return fibs
        half = self.fibsPower(fibs, n / 2)
        ans = self.matrixProd(half, half)
        if n % 2 == 0:
            return ans
        ans[0], ans[1], ans[2], ans[3] = ans[0] + ans[1], ans[0], ans[2] + ans[3], ans[2]
        return ans

//######################################### DP O(log n)#########################################
def climbStairs(self, n):
    def mul(A, B):
        N = 0, 1
        return [[sum(A[i][k] * B[k][j] for k in N) for j in N] for i in N]
    def pow(A, n):
        if n == 1:
            return A
        P = pow(A, n/2)
        P = mul(P, P)
        return mul(P, A) if n % 2 else P
    return pow([[1, 1], [1, 0]], n + 1)[0][1]
