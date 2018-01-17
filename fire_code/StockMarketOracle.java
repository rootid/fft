// Stock Market Oracle
// You've recently acquired market prediction superpowers that let you predict
// the closing stock price of a Acme Inc.'s stock a month into the future! To
// get the most out of this superpower, you need to write a method called
// maxProfit that takes in an array of integers representing the close out stock
// price on a given day. This method should return the maximum profit you can
// make out of trading Acme Inc.'s stock. There are a few limitations however :
// 1) You must sell your current holding before buying another - i.e. You may
// not buy and then buy again. It needs to be a buy - sell - buy - sell ...
// pattern.
// 2)  You may complete as many transactions as you like. You're using an
// awesome service like Robinhood, and so there are no transaction costs!
// 3) If you're enormously unlucky (or karma takes over) and no profit can be
// made, return 0.
// Examples:
//[50,100,20,80,20] => 110
//[50,100] => 0 //50?
//[50,100,50,100,50] => 100

public class StockMarketOracle {
  public static int maxProfit(int[] prices) {
    int profit = 0, i = 0;
    int len = prices.length;
    while (i < len) {
      // find next local minima : Wait when prices are decreasing
      while (i < len - 1 && prices[i + 1] <= prices[i]) //i+1 : Future : wrong
        i++;  // monotonic decrease : continue, 100,10,5
      int lastBuy =
          prices[i++];  // need increment to avoid infinite loop for "[1]"
      // find next local maximum : Wait when prices are increasing
      while (i < len - 1 && prices[i + 1] >= prices[i])
        i++;                                          // monotonic decrease
      profit += i < len ? prices[i++] - lastBuy : 0;  // no montonic ↓
    }
    return profit;
  }

  //#####################Dynamic programming#####################
  // let P = {p0,...pn-1)
  // OPT(P_i) = max(OPT(P_i-1), OPT(P_i-2) + (if >0: buy at P_i-1 and sell at
  // P_i))
  public static int maxProfitDP(int[] a) {
    if (a.length <= 1) return 0;
    int[] P = a;

    int[] OPT = new int[a.length];
    OPT[0] = 0;
    OPT[1] = (P[1] - P[0] > 0) ? P[1] - P[0] : 0;
    for (int i = 2; i < P.length; i++) {
      int in = (P[i] - P[i - 1] > 0) ? P[i] - P[i - 1] : 0;
      OPT[i] = Math.max(OPT[i - 1], OPT[i - 2] + in);
    }
    return OPT[a.length - 1];
  }
}
