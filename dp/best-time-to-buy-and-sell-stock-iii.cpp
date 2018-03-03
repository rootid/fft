//Best Time to Buy and Sell Stock III
//Say you have an array for which the ith element is the price of a given stock
//on day i.
//Design an algorithm to find the maximum profit. You may complete at most two
//transactions.
//Note:
//You may not engage in multiple transactions at the same time (ie, you must
//sell the stock before you buy again).


//############################################ DP formulated EAsy with 2 vecs ############################################
//current state (k,i), we only need the k-1 or i-1
//f[k][i]: max profit up to day i (included) with at most k transactions
//(global optimal objective)
//g[k][i]: max profit up to day i (included) with at most k transactions AND we
//sell at day i (local optimal objective, why local? think about it!)
//Time complexity is O(kn), space complexity can be O(n) because this DP only
//uses the result from last step
//(1). f[k][i] = max ( f[k][i-1], g[k][i] )
//(2)'. g[k][i] = g[k][i-1], f[k-1][i-1]) + p[i] - p[i-1]
int maxProfit(int k, vector<int>& prices) {
       int n=prices.size();
       if (n<2) return 0;
       if (k>=n/2) { // buy-sell-II case, unlimited
           int maxProfit=0;
           for (int i=1; i<n; ++i) {
               if (prices[i]>prices[i-1]) maxProfit += prices[i] - prices[i-1];
           }
           return maxProfit;
       }
       // if k<n/2, use DP approach but only O(k) space
       vector<int> f(k+1,0), g(k+1,0);
       for (int i=1; i<n; ++i) {
           int diff = prices[i] - prices[i-1], temp = f[0];
           for (int kk=1; kk<=k; ++kk) {
               g[kk] = max(g[kk], temp) + diff;
               temp=f[kk];
               f[kk] = max(f[kk], g[kk]);
           }
       }
       return f[k];
}

//############################################ DP formulated ############################################
//Time complexity is O(kn), space complexity can be O(n) because this DP only
//uses the result from last step
//Same formulation
// dpProfit[t][i]: maximum Profit using at most t transactions up to day i (including day i)
// dpProfit[t][i] = max(dpProfit[t][i - 1], prices[i] - prices[j] + dpProfit[t - 1][j]) for all j in range [0, i - 1]
//                = max(dpProfit[t][i - 1], prices[i] + max(dpProfit[t - 1][j] - prices[j])) for all j in range [0, i - 1]
//                = max(dpProfit[t][i - 1], prices[i] + max prev [t - 1] trans profit at the corresponding j in range [0, i - 1] less price at j)
//                                                      maxPreProfitLessI inside loop iterations
//                                                      Note: subtracting price at j is for the last additional transaction to sell at day i
int maxProfit(vector<int> &prices) {

    //prices[ii] : current price on day current day ii
    // f[k, ii] represents the max profit up until prices[ii] (Note: NOT ending with prices[ii]) using at most k transactions.
    // f[k, ii] = max(f[k, ii-1], prices[ii] - prices[jj] + f[k-1, jj]) { jj in range of [0, ii-1] }
    //          = max(f[k, ii-1], prices[ii] + max(f[k-1, jj] - prices[jj]))
    // f[0, ii] = 0; 0 times transation makes 0 profit
    // f[k, 0] = 0; if there is only one price data point you can't make any money no matter how many times you can trade
    if (prices.size() <= 1) return 0;
    else {
        int K = 2; // number of max transation allowed
        int maxProf = 0;
        vector<vector<int>> f(K+1, vector<int>(prices.size(), 0));
        for (int kk = 1; kk <= K; kk++) {
            int tmpMax = f[kk-1][0] - prices[0];
            for (int ii = 1; ii < prices.size(); ii++) {
                f[kk][ii] = max(f[kk][ii-1], prices[ii] + tmpMax);
                tmpMax = max(tmpMax, f[kk-1][ii] - prices[ii]);
                maxProf = max(f[kk][ii], maxProf);
            }
        }
        return maxProf;
    }
}

//############################################  DP  ############################################
//buy1 = Math.max(buy1, -prices[i]);
//sell1 = Math.max(sell1, buy1 + prices[i]);
//buy2 = Math.max(buy2, sell1 - prices[i]);
//sell2 = Math.max(sell2, buy2 + prices[i]);
//buy1 and *sell1 *are for the first transaction. buy2 and *sell2 *are for the
//second transaction.
//Transition relation:
//buy1[i] = max( - prices[i], buy1[i - 1])
//sell1[i] = max(buy1[i - 1] + price[i], sell1[i - 1])
//buy2[i] = max( sell1[i -1] - prices[i], buy2[i - 1])
//sell2[i] = max(buy2[i - 1] + price[i], sell2[i - 1])

int maxProfit(vector<int>& prices) {
		int sell1 = 0, sell2 = 0, buy1 = INT_MIN, buy2 = INT_MIN;
		for (auto price:prices) {
			buy1 = max(buy1, -price);
			sell1 = max(sell1, buy1 + price);
			buy2 = max(buy2, sell1 - price);
			sell2 = max(sell2, buy2 + price);
		}
		return sell2;
}



//############################################ DP ############################################
//http://postimg.org/image/b0auzohv3/
//lowestBuyPrice2 < lowestBuyPrice1 < maxProfit1 < maxProfit2
//From the chart and figure of variables in each step, we can see that
//lowestBuyPrice1 is always the lowest price in the input array,
//maxProfit1 keeps track of the biggest difference between prices and lowest
//price so far,
//value change of lowestBuyPrice2 reflects the local valley in the input prices
//array and variable maxProfit2 maintains the maximum profit until the current
//price.
//lowestBuyPrice1 and maxProfit1 are easy to understand. But how does
//lowestBuyPrice2 and maxProfit2 works?
//First, we shall see that
//lowestBuyPrice2 decreases whenever we hit a local minimum price.
//It indirectly (since it is negative) reflects the lowest price that is
//closest to the current price.
//When the current price is bigger than -lowestBuyPrice2, maxProfit2i = price i
//- (price (i-1) -maxProfit1 (i-1))= price i - price (i-1) +maxProfit1 (i-1),
//which means the accrued maximum profit until now.
int maxProfit(vector<int>& prices) {
  int maxProfit1 = 0;
	int maxProfit2 = 0;
	int lowestBuyPrice1 = INT_MAX;
	int lowestBuyPrice2 = INT_MAX;
	for(auto p:prices){
		maxProfit2 = max(maxProfit2, p-lowestBuyPrice2); //gains
		lowestBuyPrice2 = min(lowestBuyPrice2, p-maxProfit1); //last buy i.e buy lowest
		maxProfit1 = max(maxProfit1, p-lowestBuyPrice1); //last profit
		lowestBuyPrice1 = min(lowestBuyPrice1, p);
	}
	return maxProfit2;
}

//
int maxProfit(vector<int>& prices) {
        int hold1 = INT_MIN, hold2 = INT_MIN;
        int release1 = 0, release2 = 0;
        for(int i:prices) {                              // Assume we only have 0 money at first
            release2 = (release2, hold2+i);     // The maximum if we've just sold 2nd stock so far./current
            hold2    = (hold2,    release1-i);  // The maximum if we've just buy  2nd stock so far. /current
            release1 = (release1, hold1+i);     // The maximum if we've just sold 1nd stock so far./last
            hold1    = (hold1,    -i);          // The maximum if we've just buy  1st stock so far. /last
        }
        return release2; ///Since release1 is initiated as 0, so release2 will always higher than release1.
    }
