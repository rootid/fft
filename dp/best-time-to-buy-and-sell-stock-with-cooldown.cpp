//Best Time to Buy and Sell Stock with Cooldown
//Say you have an array for which the ith element is the price of a given stock on day i.
//Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times) with the following restrictions:
//You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
//After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1 day)
//Example:
//prices = [1, 2, 3, 0, 2]
//maxProfit = 3
//transactions = [buy, sell, cooldown, buy, sell]

//##################################### DP : compute s[i] and b[i] to gain max sell ########################################
int maxProfit(vector<int> &prices) {
    int buy(INT_MIN), sell(0), prev_sell(0), prev_buy;
    for (int price : prices) {
        prev_buy = buy;
        buy = max(prev_sell - price, buy); //b[i] = s[i-2] - price , b[i-1]
        prev_sell = sell;                  //s[i-2] = s[i-1]
        sell = max(prev_buy + price, sell); //s[i] = b[i-1] + price,s[i-1]
    }
    return sell;
}

//##################################### state transition ########################################
int maxProfit(vector<int>& prices){
	if (prices.size() <= 1) return 0;
	vector<int> s0(prices.size(), 0);
	vector<int> s1(prices.size(), 0);
	vector<int> s2(prices.size(), 0);
  //base case
	s0[0] = 0; // rest
	s1[0] = -prices[0]; // buy
	s2[0] = INT_MIN; //sell
	for (int i = 1; i < prices.size(); i++) {
		s0[i] = max(s0[i - 1], s2[i - 1]);
		s1[i] = max(s1[i - 1], s0[i - 1] - prices[i]);
		s2[i] = s1[i - 1] + prices[i];
	}
	return max(s0[prices.size() - 1], s2[prices.size() - 1]);
}


//##################################### state transition const SPACE : O(K) ########################################
int maxProfit(vector<int>& prices) {
    int sold = 0, hold = INT_MIN, rest = 0;
    for (int i=0; i<prices.size(); ++i)
    {
        int prvSold = sold;
        sold = hold + prices[i];
        hold = max(hold, rest-prices[i]);
        rest = max(rest, prvSold);
    }
    return max(sold, rest);
}
