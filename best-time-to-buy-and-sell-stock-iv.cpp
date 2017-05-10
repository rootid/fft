//Best Time to Buy and Sell Stock IV
//Say you have an array for which the ith element is the price of a given stock on day i.
//Design an algorithm to find the maximum profit. You may complete at most k transactions.
//Note:
//You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
//############################################ DP formulated EAsy with 2 vecs ############################################ 
//current state (k,i), we only need the k-1 or i-1
//f[k][i]: max profit up to day i (included) with at most k transactions (global optimal objective)
//g[k][i]: max profit up to day i (included) with at most k transactions AND we sell at day i (local optimal objective, why local? think about it!)
//Time complexity is O(kn), space complexity can be O(n) because this DP only uses the result from last step
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

//####################################################### peak valley approach ####################################################### 
//TODO : cpp fixme
// idea
// consider two consecutive non-decreasing v/p pairs, (v1,p1) and (v2,p2)
// there are 4 possible relations between (v1,p1) and (v2,p2)
// 1. no overlap p2 < v1
// 2. overlap v1 <= p2 <= p1 && (v2 >= v1 || v2 < v1)
// 3. overlap v1 <= v2 <= p1 && p2 >= p1
// 4. no overlap p1 < v2 (doesn't seem possible to happen in this problem)
// what's the max profit if you do only ONE transaction?
// for case 1/2, we just pick one of the two transactions with max profit
// for case 3, however, (v1,p2) would be the max profit
// what's the max profit if you do exactly TWO transactions?
// for case 1/2, we can maintain top 2 most profit transactions with a  priority queue, and poll() twice
// for case 3, if we want to uniformly handle this and previous problems, we need to re-think (v1,p1) and (v2,p2) as (v1,p2) and (v2,p1)    
public int maxProfit(int k, int[] prices) {
    if(k < 1 || prices == null || prices.length == 0)
        return 0;
    int result = 0;
    List<Integer> profits = new LinkedList<>();
    Stack<Integer> starts = new Stack<>(); // hold valley, top element has largest valley value of the whole stack
    Stack<Integer> ends = new Stack<>(); // hold peak, top element has smallest peak value of the whole stack
    int s, e = 0;
    while(e < prices.length) {
        s = e;
        while(s+1 < prices.length && prices[s] >= prices[s+1]) s++;
        e = s+1;
        while(e+1 < prices.length && prices[e] <= prices[e+1]) e++;
        if(s < e && s < prices.length && e < prices.length) {
            while(!starts.isEmpty() && prices[s] < prices[starts.peek()]) 
                profits.add(prices[ends.pop()] - prices[starts.pop()]);
            
            while(!starts.isEmpty() && prices[e] >= prices[ends.peek()]) {                
                profits.add(prices[ends.pop()] - prices[s]);
                s = starts.pop();
            }
            starts.push(s);
            ends.push(e);
        }
    }
    while(!starts.isEmpty()) 
        profits.add(prices[ends.pop()] - prices[starts.pop()]);
    PriorityQueue<Integer> pq = new PriorityQueue<>((a,b)->b.compareTo(a));
    pq.addAll(profits);
    for(int i = 0; i < k && !pq.isEmpty(); i++) 
        result += pq.poll();
    return result;
}    

//####################################################### heap ####################################################### 
//https://discuss.leetcode.com/topic/9522/c-solution-with-o-n-klgn-time-using-max-heap-and-stack/22
//http://www.tachenov.name/2016/02/14/128/
//split the prices array into several consecutive ascending segments, 
//with valley and peak index denoting the start and end point.
//use a stack to process these segments into all possible profits.
//employ a max heap to find the max k profits as the result.
//buy : valley , sell : peak
//How could we find all possible profits?
//Suppose we are facing two segments (v1,p1) and (v2, p2) under the limit v1 < p1 < v2 < p2, 
//we would have two possible operations:
//1. buy at v1, sell at p1; buy at v2, sell at p2 ( p1 - v1 + p2 - v2 )
//2. buy at v1, sell at p2 ( p2 - v1 )
//What we need to do is to find out which could make more profit. We would meet these situations:
//prices[v2] <= prices[v1]
//it’s obvious that we’d better make two transactions: p1-v1 and p2-v2, and v2 is more possible to make bigger profit. So, we pop out (v1,p1) from the stack.
//prices[v2] > prices[v1]
//prices[p2] < prices[p1] We’d better use two transactions p1-v1 and p2-v2, and v1 is still more possible to make bigger profit. So, we keep (v1,p1) in the stack.
//prices[p2] >= prices[p1] We are not sure about using one or two transactions to get higher profit, so we push two possible results into the profits array. Here comes the key point: we push p2-v1 and p1-v2 into profits array. Why? If we could only use one transaction, p2-v1 is what we want, and if with two transactions, p2-v1 + p1-v2 is also the max profit.
//iterating valley-peak segments
//prices #=> [ 1, 3, 2, 4 ]
//# we could get
//(v1, p1): (0 ,1) 
//(v2, p2): (2, 3)
//# then push two possible profits
//profits << prices[p2] - prices[v1]
//profits << prices[p1] - prices[v2]
//profits #=> [3, 1]
//# If k is 1, the top profits is 3 
//# If k is 2, the top profits is 3+1
//
//
 int maxProfit(int k, vector<int>& prices) {
        vector<int> main_prices;
        int direct = -1, cl = 1;
        for (int i = 0; i + 1 < prices.size(); i += cl) {
            cl = 1;
            while (prices[i + cl] == prices[i]) cl++;
            if ((prices[i + cl] - prices[i]) * direct < 0) {
                main_prices.push_back(prices[i]);
                direct *= -1;
            }
        }
        if (direct == 1)
            main_prices.push_back(prices[prices.size() - 1]);
        if (main_prices.empty())
            return 0;
        vector<int> profits;
        stack<int> l, h;
        for (int i = 0; i < main_prices.size(); i += 2) {
            while (l.size() && l.top() > main_prices[i]) {
                profits.push_back(h.top() - l.top());
                h.pop();
                l.pop();
            }

            while (l.size() && h.top() < main_prices[i + 1]) {
                profits.push_back(h.top() - main_prices[i]);
                h.pop();
                main_prices[i] = l.top();
                l.pop();
            }
            l.push(main_prices[i]);
            h.push(main_prices[i + 1]);
        }
        while (l.size()) {
            profits.push_back(h.top() - l.top());
            h.pop();
            l.pop();
        }
        if (k >= profits.size())
            return accumulate(profits.begin(), profits.end(), 0);
        nth_element(profits.begin(), profits.end() - k, profits.end());
        return accumulate(profits.end() - k, profits.end(), 0);        
    }


