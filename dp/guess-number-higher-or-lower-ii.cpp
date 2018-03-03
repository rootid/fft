//Guess Number Higher or Lower II
//We are playing the Guess Game. The game is as follows:
//I pick a number from 1 to n. You have to guess which number I picked.
//Every time you guess wrong, I'll tell you whether the number I picked is
//higher or lower.
//However, when you guess a particular number x, and you guess wrong, you pay
//$x. You win the game when you guess the number I picked.
//Example:
//n = 10, I pick 8.
//First round:  You guess 5, I tell you that it's higher. You pay $5.
//Second round: You guess 7, I tell you that it's higher. You pay $7.
//Third round:  You guess 9, I tell you that it's lower. You pay $9.
//Game over. 8 is the number I picked.
//You end up paying $5 + $7 + $9 = $21.
//Given a particular n ≥ 1, find out how much money you need to have to
//guarantee a win.

//############################################## Minmax algo #############################################
//https://en.wikipedia.org/wiki/Minimax
int getMoneyAmount(int n) {
  vector<vector<int>> dp(n+1,vector<int>(n+1,0));
  return getMoneyAmount(1,n,dp);
}
int getMoneyAmount(int lower, int upper,vector<vector<int>>& dp) {
    if (lower >= upper) {
        return 0;
    }
    if (dp[lower][upper] != 0) {
        return dp[lower][upper];
    }

    int maximum = INT_MAX;
    for (int i = lower; i <= upper; i++) {
        maximum = min(maximum, max(getMoneyAmount(lower, i-1,dp), getMoneyAmount(i+1, upper,dp)) + i);
    }
    dp[lower][upper] = maximum;
    return maximum;
}
//################################################## MultiSelection approach##################################################
//1. Range selection (i,j)
//2. consecutive selection (i,i+1)
//
//1.Two consectuive number i + 1 == j
//For example, dp[1][2] is the case that you can only choose from 1 and 2.
//Obviously you will choose the smaller number since you want to minimize the
//loss.
//2.Multiple numbers, range i - j
//In this case, we assign globalMin to dp[i][j] since globalMin is the minimum
//loss we got so far.

//################################################ Top-down solution ###############################################
//For each number x in range[i~j]
//we do: result_when_pick_x = x + max{DP([i~x-1]), DP([x+1, j])}
//--> // the max means whenever you choose a number, the feedback is always bad and therefore leads you to a worse branch.
//then we get DP([i~j]) = min{xi, ... ,xj}
//--> // this min makes sure that you are minimizing your cost.
int getMoneyAmount(int n) {
    vector<vector<int> > table(n+1,vector<int>(n+1,0));
    return DP(table, 1, n);
}
int DP(vector<vector<int> >&t, int s, int e){
    if(s >= e) return 0;
    if(t[s][e] != 0) {
      return t[s][e];
    }
    int res = INT_MAX;
    for(int x=s; x<=e; x++){
        int tmp = x + max(DP(t, s, x-1), DP(t, x+1, e));
        res = min(res, tmp);
    }
    t[s][e] = res;
    return res;
}
//################################################ bottom-up solution ############################################
int getMoneyAmount(int n) {
    vector<vector<int> > table(n+1,vector<int>(n+1,0));
    for(int j=2; j<=n; j++){
        for(int i=j-1; i>0; i--){
            int globalMin = INT_MAX;
            for(int k=i+1; k<j; k++){
                int localMax = k + max(table[i][k-1], table[k+1][j]);
                globalMin = min(globalMin, localMax);
            }
            table[i][j] = i+1==j?i:globalMin;
        }
    }
    return table[1][n];
}

//########################################### pytonic #############################################################
//########################################################## bottom up #######################################
//To find out how much money I need to win the range lo..hi (the game starts
//with the range 1..n), I try each possible x in the range (except hi, which is
//pointless because hi-1 costs less and provides more information), calculate
//how much I need when using that x, and take the minimum of those amounts.
//def getMoneyAmount(self, n):
//    need = [[0] * (n+1) for _ in range(n+1)]
//    for lo in range(n, 0, -1):
//        for hi in range(lo+1, n+1):
//            need[lo][hi] = min(x + max(need[lo][x-1], need[x+1][hi])
//                               for x in range(lo, hi))
//    return need[1][n]

//####################################### top-down #######################################
//
//Top-down with memoization, subclassing dict for convenience. Simpler than
//bottom-up because I don't need to specify ranges/loops for lo and hi and
//don't need to think about their orders and how big my DP matrix needs to be.
//On the other hand, it's slower.
//def getMoneyAmount(self, n):
//    class Need(dict):
//        def __missing__(self, (lo, hi)):
//            if lo >= hi:
//                return 0
//            ret = self[lo, hi] = min(x + max(self[lo, x-1], self[x+1, hi])
//                                     for x in range(lo, hi))
//            return ret
//    return Need()[1, n]
