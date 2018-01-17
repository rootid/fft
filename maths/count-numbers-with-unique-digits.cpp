//Count Numbers with Unique Digits
//Given a non-negative integer n, count all numbers with unique digits, x, where 0 ≤ x < 10n.
//Example:
//Given n = 2, return 91. (The answer should be the total numbers in the range of 0 ≤ x < 100, excluding [11,22,33,44,55,66,77,88,99])
//Hint:
//A direct way is to use the backtracking approach.
//Backtracking should contains three states which are (the current number, number of steps to get that number and a bitmask which represent which number is marked as visited so far in the current number). Start with state (0,0,0) and count all valid number till we reach number of steps equals to 10n.
//This problem can also be solved using a dynamic programming approach and some knowledge of combinatorics.
//Let f(k) = count of numbers with unique digits with length equals k.
//f(1) = 10, ..., f(k) = 9 * 9 * 8 * ... (9 - k + 2) [The first factor is 9 because a number cannot start with 0].
#include "../headers/global.hpp"

//Using combinatrics result to choose the distinct elements
int countNumbersWithUniqueDigits(int n) {
    if(n == 0) {
      return 1;
    }
    int i = 9;
    int result = 9;
    int num = 0;
    while(--n) {
      result *= i--;  
      num += result;
    } 
    return num + 10; 
}


//Think in terms of creating no with 0 and w/o 0 and combine
//2-digits
// 9 + 9*8 = 9 * (1+8) = 9 * 9.
//dp[2]  = dp[1] + the combination with 0 digit 
//3-digits
//dp[3]  = dp[2] + the combination with  3 digits
//9 * 8  + 9 * 8 + 9 * 8 * 7  = 9 * 8 * (1 + 1 + 8 ) = 9 * 9 * 8 
int countNumbersWithUniqueDigits(int n) { 
    vector<int> dp(n+1);
    dp[0] = 1;
    dp[1] = 10;
    for(int i=2;i<=n;i++){
        //dp[i] = 9;
        int k = 9;
        int count = 1;
        while(count < i){
            dp[i] *= k;
            k--;
            count++;
        }
        dp[i] +=dp[i-1];
    }
    return dp[n];
}

//Backtracking
int countNumbersWithUniqueDigits(int n) {
        bool visit[10] = {false};
        int count = 0;
        for (int i = 0; i <= min(10,n); i++)
            count += DFS(i, 0, visit);
        return count;
}
int DFS(int target, int idx, bool* visit) {
    if (idx == target)
        return 1;

    int count = 0;
    for (int i = idx?0:1; i < 10; i++) {
        if (!visit[i]) {
            visit[i] = true;
            count += DFS(target, idx+1, visit);
            visit[i] = false;
        }
    }
    return count;
}

/* vim: set ts=4 sw=4 sts=4 tw=120 et: */
