//Best Time to Buy and Sell Stock II
//Say you have an array for which the ith element is the price of a given stock on day i.
//Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times). However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
//Obs:
//we can't sell and buy in the same day
//From this, we can simply jude the positive profit,and sum them up
//
//
///The idea: We will sell the stock today, if today's profit is greater than tomorrow's profit.
///Proof
///There is a list of the stock [A0,A1,A2....Ax...Ai,Aj..Ak,...An-1]
///Condition:
///1 Now we are on Ai and we get the minimum prices Ax.
///2 Ai -Ax > Aj -Ax
///If we sell it on the Kth day when Ak-Ax>Ai-Ax. the overall profit we get on day K is Ak-Ax.
///But if we sell it on day i, the profit on day K would be >= Ai-Ax + Ak -Aj.
///We know Ai-Ax + Ak -Aj = Ak-Ax + Ai -Aj > Ak-Ax, so to gain more profit on day K, we should sell it on Day i.
// 2 cases 
// 1. Monotonic increase/decrease
// 1. Bitonic  increase
int maxProfit(vector<int>& prices) {
  if(prices.size()==0) return 0;
  int min = prices[0];
  int max = 0;
  int sum = 0;
  for(int i=1; i< prices.size();i++){
      if(prices[i]-min>=max){
          max = prices[i] - min;
          if(i==prices.size()-1) sum+=max;
      }else{
          sum += max;
          min = prices[i];
          max = 0;
      }
      
  }
  return sum; 
}
