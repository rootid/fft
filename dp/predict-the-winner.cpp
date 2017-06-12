//Predict the Winner
//Given an array of scores that are non-negative integers. Player 1 picks one of the numbers from either end of the array followed by the player 2 and then player 1 and so on. Each time a player picks a number, that number will not be available for the next player. This continues until all the scores have been chosen. The player with the maximum score wins.
//Given an array of scores, predict whether player 1 is the winner. You can assume each player plays to maximize his score.
//Example 1:
//Input: [1, 5, 2]
//Output: False
//Explanation: Initially, player 1 can choose between 1 and 2. 
//If he chooses 2 (or 1), then player 2 can choose from 1 (or 2) and 5. If player 2 chooses 5, then player 1 will be left with 1 (or 2). 
//So, final score of player 1 is 1 + 2 = 3, and player 2 is 5. 
//Hence, player 1 will never be the winner and you need to return False.
//Example 2:
//Input: [1, 5, 233, 7]
//Output: True
//Explanation: Player 1 first chooses 1. Then player 2 have to choose between 5 and 7. No matter which number player 2 choose, player 1 can choose 233.
//Finally, player 1 has more score (234) than player 2 (12), so you need to return True representing player1 can win.
//Note:
//1 <= length of the array <= 20.
//Any scores in the given array are non-negative integers and will not exceed 10,000,000.
//If the scores of both players are equal, then player 1 is still the winner.

//################################  DP store only the difference ##############################################################
//if player 1 get A, player 2 get B, we can use dp' to store A-B.
//dp(i, j) = max(nums[j] - dp(i, j-1), nums[i] - dp(i+1, j))
//if A = dp(i, j), then B = sum(i, j) - dp(i, j)
//Final formula: dp(i, j) = max(nums[j] - dp(i, j-1), nums[i] - dp(i+1, j))
//Given [1, 2, 3, 4, 5]
//Correct way:
//i=1: [1, 2] -> [2, 3] -> [3, 4] -> [4, 5]
//i=2: [1, 2, 3] -> [2, 3, 4] -> [3, 4, 5]
//i=3: [1, 2, 3, 4] -> [2, 3, 4, 5]
//i=4: [1, 2, 3, 4, 5]
bool PredictTheWinner(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(n)); // use to keep the score gap between player1 and player2
    for (int i = 0; i < n; i++) {
      dp[i][i] = nums[i]; //diagonal elements update
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j+i < n; j++) {
            dp[j][j+i] = max(nums[j+i]-dp[j][j+i-1], nums[j]-dp[j+1][j+i]);
        }
    }
    return dp[0][n-1] >= 0; // player1 get more score points than player2
}

//############################## MIT OCW  6.046 ############################## 
//https://www.youtube.com/watch?v=Tw1k46ywN6E&feature=youtu.be&list=PLUl4u3cNGP6317WaSNfmCvGym2ucw3oGp&t=3622
//The goal here is that we want to maximize the amount of money we can get assuming we move first.
//Here your dp[i][j] means the max value we can get if it it's our turn and only coins between i and j remain.(Inclusively)
//So dp[i][i] means there is only one coin left, we just pick it, dp[i][i+1] means there are only two left, we then pick the max one.
//Now we want to derive the more general case. dp[i][j] = max( something + v[i], something + v[j]), since we either will pick the i or j coin. The problem now turns to what "something" here will be.
//A quick idea may bedp[i][j] = max( dp[i + 1][j] + v[i], dp[i][j - 1] + v[j]), but here dp[i + 1][j] and dp[i][j - 1] are not the values directly available for us, it depends on the move that our opponent make.
//Then we assume our opponent is as good as we are and always make optimize move. The worse case is that we will get the minimal value out of all possible situation after our opponent make its move.
//so the correct dp formula would be dp[i][j] = max( min (dp[i + 1][j - 1], dp[i + 2][ j]) + v[i], min (dp[i][j - 2], dp[i + 1][ j - 1]) + v[j]}) .
//If we pick i, then our opponent need to deal with subproblem dp[i + 1][j], it either pick from i + 2 or j - 1. Similarly, If we pick j, then our opponent need to deal with subproblem dp[i][j - 1] , it either pick from i + 1 or j - 2. We take the worse case into consideration so use min() here.
bool PredictTheWinner(vector<int>& nums) {
     if(nums.size()% 2 == 0) return true;
     
     int n = nums.size();
     vector<vector<int>> dp(n, vector<int>(n, -1));
     
     int myBest = utill(nums, dp, 0, n-1);
     return 2*myBest >= accumulate(nums.begin(), nums.end(), 0);
}
 
int utill(vector<int>& v, vector<vector<int>> &dp, int i, int j){
     if(i > j) return 0;
     if(dp[i][j] != -1) return dp[i][j];
     
     int a = v[i] + min(utill(v,dp, i+1, j-1), utill(v, dp, i+2, j));
     int b = v[j] + min(utill(v,dp,i, j-2), utill(v,dp, i+1, j-1));
     dp[i][j] = max(a, b);
                     
     return dp[i][j];
 }
