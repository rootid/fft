//Burst Balloons
//Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums. You are asked to burst all the balloons. If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.
//Find the maximum coins you can collect by bursting the balloons wisely.
//Note: 
//(1) You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
//(2) 0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100
//Example:
//Given [3, 1, 5, 8]
//Return 167
//    nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
//   coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167
//######################################### DP (Bottom-up) ######################################### 
int maxCoins(vector<int>& nums) {
       int size_nums = nums.size();
       if(size_nums <= 0)  return 0;
       
       nums.insert(nums.begin(), 1);
       nums.push_back(1);
       
       size_nums = nums.size();
       vector<vector<int>> dp(size_nums, vector<int>(size_nums, 0));
       
       /**
        * dp[i][j] = max { dp[i][k] + dp[k][j] + nums[i]* nums[k] *nums[j] }
        **/
       for(int j = 2; j < size_nums; j++) {
           //left ballons
           for(int i = j - 1; i >= 0; i--) {
               /** k in (i, j) field **/
               //Right ballons from (left+1) upto end (K)
               for(int k = i + 1; k < j; k ++) {
                   dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j] + nums[i] * nums[k] * nums[j]);
               }
           }
       }
       
       return dp[0][size_nums-1];
   }
