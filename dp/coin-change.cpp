//Coin Change
//You are given coins of different denominations and a total amount of money
//amount. Write a function to compute the fewest number of coins that you need
//to make up that amount. If that amount of money cannot be made up by any
//combination of the coins, return -1.
//Example 1:
//coins = [1, 2, 5], amount = 11
//return 3 (11 = 5 + 5 + 1)
//Example 2:
//coins = [2], amount = 3
//return -1.
//Note:
//You may assume that you have an infinite number of each kind of coin.

//######################################### Coin change : Pick coin or do not pick the coin #########################################
//1. Pick the coin : and increament coin count
public int coinChange(int[] coins, int amount) {
    int m = coins.length;
    int[] opt = new int[amount+1];
    for(int i=1;i<=amount;i++) opt[i] = amount+1;
    for(int coin: coins)
        for(int i=coin;i<=amount;i++)
            opt[i] = Math.min(opt[i], opt[i-coin]+1); //pick the coin
    return opt[amount] > amount ? -1 : opt[amount];
}

//#################### DP - 1 ################################
int coinChange(vector<int>& coins, int amount) {
  int Max = amount + 1;
  vector<int> dp(Max, Max);
  dp[0] = 0;
  for (int i = 1; i <= amount; i++) {
      for (int j = 0; j < coins.size(); j++) {
          if (coins[j] <= i) {
              dp[i] = min(dp[i], dp[i - coins[j]] + 1);
          }
      }
  }
  if(dp[amount] > amount) {
    return -1;
  }
  return dp[amount];
}

//#################### DP - 2 ################################
// Iterating over all combinations instead of all permutations!
int coinChange(vector<int>& coins, int amount) {
   vector<int> A(amount+1, amount+1);
    A[0] = 0;
    for (int coin : coins) {
        for (int i = coin; i <= amount; i++) {
            A[i] = min(A[i], A[i - coin] + 1);
        }
    }
  if(dp[amount] > amount) {
    return -1;
  }
  return dp[amount];
}

//###################### DFS ######################
int coinChange(vector<int>& coins, int amount) {
       int res = INT_MAX;
       sort(coins.begin(), coins.end());
       dfs(res, coins, amount, coins.size() - 1, 0);
       return res == INT_MAX? -1: res;
}
void dfs(int& res, vector<int>& coins, int target, int idx, int count) {
       if (idx < 0) return;
       if (target % coins[idx] == 0) {
           res = min(res, count + target / coins[idx]);
           return;
       }
       for (int i = target / coins[idx]; i >= 0; i--) {
           if (count + i >= res - 1) break; // pruing
           dfs(res, coins, target - i * coins[idx], idx - 1, count + i);
       }
}
//########################## BFS ##########################
 public int coinChange(int[] coins, int amount) {
        int coinsLength = coins.length;
        Arrays.sort(coins);
        Queue<Integer> q = new LinkedList<>();
        int count = 1;
        if (amount == 0)
            return 0;
        boolean[] cache = new boolean[amount];
        //Set<Integer> cache = new HashSet<>();

        for (Integer coin : coins)
        {
            if (amount == coin)
                return count;
            else if (amount > coin)
            {
                q.add(amount - coin);
                cache[amount - coin] = true;
            }
        }

        while (true)
        {
            Queue<Integer> newQ = new LinkedList<>();
            count++;
            while (!q.isEmpty())
            {
                int newAmount = q.poll();
                for (int i = coinsLength - 1; i >= 0; i--)
                {
                    if (newAmount == coins[i])
                        return count;
                    else if (newAmount > coins[i])
                    {
                        int value = newAmount - coins[i];
                        if (value >= coins[0] && !cache[value])
                        {
                            newQ.add(value);
                            cache[value] = true;
                        }
                    }
                }
            }

            if (newQ.isEmpty())
                break;
            else
                q = newQ;
        }

        return -1;
    }

//################# NEED TO FIX #################
static int total_number_of_ways = 0;
void get_number_of_ways (int input[],int k,int c,int input_sum,int total_sum,string result) {
    //cout << "input_sum = "  << input_sum << " total sum = " << total_sum  << " k = " << k << endl;
    if (input_sum == total_sum || k >= c) {
         if (input_sum == total_sum ) {
             cout << " output " << result << endl;
             total_number_of_ways += 1;
        }
    } else {
        //PROBLEM : always pick up the first coin
        for (int i=(k-1);i>=0;i--){
            input_sum += input[i];
            ostringstream ostr; //output string stream
            ostr << input[i]; //use the string stream just like cout,
            result.append(ostr.str());
            result.append(",");
            if (input_sum <= total_sum) {
                get_number_of_ways (input,k,c,input_sum,total_sum,result);
            } else if (input_sum > total_sum){
                get_number_of_ways (input,k-1,c,0,total_sum,"");
            }
        }
    }
}
int rec_formulation (vector<int>& nums,int total_sum,int m) {
    //http://www.algorithmist.com/index.php/Coin_Change
    //Prereq : input[] array must be non decreaing  s1<s2<s3..<sm
    //C(N,m) = C(N,m - 1) + C(N - Sm,m)
    //C(N,m) = 1,N = 0 (one solution -- we have no money, exactly one way to solve the problem - by choosing no coin change, or, more precisely, to choose coin change of 0)
    //C(N,m) = 0,N <= 0 (no solution -- negative sum of money)
    //C(N,m) = 0 N >= 1,m < 0(no solution -- we have money, but no change available)
    if (total_sum == 0)  {
        return 1;
    } if (total_sum < 0) {
        return 0;
    }
    if (m < 0) {
        return 0;
    }
    return rec_formulation (nums,total_sum,m-1) + rec_formulation (nums,total_sum - input[m],m) ;
}
int main () {
        int input[] = {1,5,10,25};
        string result = "";
        get_number_of_ways (input,3,4,0,10,result);
        cout << "total # of ways = " << total_number_of_ways << endl;
        cout << "total # of ways = " << rec_formulation(input,10,3)  << endl;
        //cout << "total # of ways = " << rec_formulation(input,9,3)  << endl;
}
//this approach is used in the coin picking,computing the combination using
//pascal traingle
//eg pascal traingle
//Choose r from c
int gen_pascal (int r,int c) {
    if (r == 1 && c == 1) {
        return 1;
    } else if (r <= 0 || c <= 0) {
        return 0;
    } else {
        //gen_pascal (r,c-1) : not pick/choose the r
        //gen_pascal (r-1,c) : pick/choose the r from c
        return (gen_pascal (r,c-1) + gen_pascal (r-1,c) );
        //Recursive version becomes pascal_vec[i][j] = pascal_vec[i][j-1] + pascal_vec[i-1][j];
    }
}
int gen_pascalI (int r,int c) {
    int pascalVec[r+1][c+1];
    for (int i=0;i<=r;i++) {
        for (int j=1;j<=c;j++) {
            pacalVec[i][j] = 0;
        }
    }
    pacalVec[0][1] = 1;
    for (int i=1;i<=r;i++) {
        for (int j=1;j<=c;j++) {
            pacalVec[i][j] = pascalVec[i-1][j] + pascalVec[i][j-1];
        }
    }
    return (pascalVec[r][c]);
}
//A top down approach
int rec_knapsack (int a[],int val[],int item,int capacity) {
    if (capacity < 0 || item < 0 || capacity < a[item] ) {
        return 0;
    } else {
        //# of subproblems
        //pick it or not pick it
        return max ( rec_knapsack (a,val,item-1,capacity),
                (val[item] + rec_knapsack (a,val,item-1,capacity - a[item]) ) );
    }
}
//top down approach
int dp_knapsack (int wt[],int val[],int item,int capacity) {

    int profit[item+1][capacity+1];

    //init stages
    for (int i=0;i<=item;i++) {
        profit[i][0] = 0;
    }
    //init state
    for (int j=0;j<=capacity;j++) {
        profit[0][j] = 0;
    }

    //compute the values
    for (int i=1;i<=item;i++) {
        for (int j=1;j<=capacity;j++) {
            if (wt[i] < capacity) {
                //Pick the element
                //which is max (previous state value,previous state value by adding the current state value)
                profit[i][j] = max (profit[i-1][j],val[j] + profit[i-1][j-wt[i]] );
            } else {
                //Don't pick the element
                profit[i][j] = profit[i-1][j];
            }
        }
    }
    return profit[item][capacity];
}
int main () {
    //int val[] = {60, 100, 120};
    //int wt[] = {10, 20, 30};
    //int  W = 50;
    int val[] = {1,6,18,22,28};
    int wt[] = {1,2,5,6,7};
    int  W = 11;

    int no_of_items = sizeof(val)/sizeof(val[0]);
    int max = rec_knapsack (wt,val,no_of_items -1 ,W);
    cout << "the max profit " << max << endl;
    dp_knapsack (wt,val,no_of_items,W);
    cout << "the max profit " << max << endl;
    //observations
    //cannot take the item with W >
}
