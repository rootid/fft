//Paint House II
//There are a row of n houses, each house can be painted with one of the k
//colors. The cost of painting each house with a certain color is different.
//You have to paint all the houses such that no two adjacent houses have the
//same color.
//The cost of painting each house with a certain color is represented by a n x
//k cost matrix. For example, costs[0][0] is the cost of painting house 0 with
//color 0; costs[1][2] is the cost of painting house 1 with color 2, and so
//on... Find the minimum cost to paint all houses.
//Note:
//All costs are positive integers.
//Follow up:
//Could you solve it in O(nk) runtime?
//

//############################################ O(nk) + S : O(K) ############################################
//############################  array modification ############################
//Same as Paint House I, for each house and each color,
//the minimum cost of painting the house with that color should be the
//1. minimum cost of painting previous houses,
//2. make sure the previous house doesn't paint with the same color.
//We can use min1 and min2 to track the indices of the 1st and 2nd smallest
//cost till previous house,
//if the current color's index is same as min1, then we have to go with min2
//(as it violates the 2), otherwise we can safely go with min1.
//The code below modifies the value of costs[][] so we don't need extra space.
public int minCostII(int[][] costs) {
    if (costs == null || costs.length == 0) return 0;

    int n = costs.length, k = costs[0].length;
    // min1 is the index of the 1st-smallest cost till previous house
    // min2 is the index of the 2nd-smallest cost till previous house
    int min1 = -1, min2 = -1;

    for (int i = 0; i < n; i++) {
        int last1 = min1, last2 = min2;
        min1 = -1; min2 = -1;
		//Iterate over all colors
        for (int j = 0; j < k; j++) {
            if (j != last1) {
                // current color j is different to last min1
                costs[i][j] += last1 < 0 ? 0 : costs[i - 1][last1];
            } else {
                costs[i][j] += last2 < 0 ? 0 : costs[i - 1][last2];
            }
            // find the indices of 1st and 2nd smallest cost of painting current house i
            if (min1 < 0 || costs[i][j] < costs[i][min1]) { //cost[i][j] : current hose,current color
                min2 = min1;
				min1 = j;
            } else if (min2 < 0 || costs[i][j] < costs[i][min2]) {
                min2 = j;
            }
        }
    }
    return costs[n - 1][min1];
}


//############################################ O(nk) + S : O(K) ############################################
//maintain only the two smallest total costs until the previous house
//Otherwise we might need to traverse the other k-1 colors for each j, and the
//time complexity would be O(nk^2).
int minCostII(vector<vector<int>>& costs) {
	if(costs.empty()) {
		return 0;
	}
    int k = costs[0].size();
    if(k == 1) {
		return costs[0][0];
	}
    vector<int> dp(k, 0);
    int min1, min2;

	//maintain the minimum two costs min1(smallest) and min2 (second to smallest) after painting i-th house.
    for(int i=0; i<n; ++i) {
        int min1_old = (i==0)? 0:min1;
        int min2_old = (i==0)? 0:min2;
        min1 = INT_MAX;
        min2 = INT_MAX;
        for(int j=0; j<k; ++j){
            if(dp[j]!= min1_old || min1_old == min2_old){
                dp[j] = min1_old + costs[i][j];
            }else{//min1_old occurred when painting house i-1 with color j, so it cannot be added to dp[j]
                dp[j] = min2_old + costs[i][j];
            }
            if(min1 <= dp[j]){
                min2 = min(min2, dp[j]);
            }else{
                min2 = min1;
                min1 = dp[j];
            }
        }
    }
    return min1;
}

//############################################ Same optimized + O(nk) + S : O(K) ############################################
int minCostII(vector<vector<int>>& costs) {
       if (costs.empty()) return 0;
       int n = costs.size(), k = costs[0].size(), m1 = 0, m2 = 0;
       vector<int> dp(k, 0);
       for (int i = 0; i < n; i++) {
           int t1 = m1, t2 = m2;
           m1 = m2 = INT_MAX;
           for (int j = 0; j < k; j++) {
               dp[j] = (dp[j] != t1 ? t1 : t2) + costs[i][j];
               if (m1 <= dp[j]) m2 = min(m2, dp[j]);
               else m2 = m1, m1 = dp[j];
           }
       }
       return m1;
   }

//########################################## Pythonic ##########################################
//##########################################  T: (nk) S : O(1)
//store is the first and second minimum costs at current house and the
//corresponding color index of first minimum.
def minCostII(self, costs):
    if not costs or not costs[0]:
        return 0
    n = len(costs)
    k = len(costs[0])
    if n == 1:
        return min(costs[0])
    fst = [0, 0]  # first minimum
    col = [-1, -1]  # color index of first minimum
    sec = [0, 0]  # second minimum
    prev, curr = 0, 1
    for i in xrange(n):
        fst[curr] = sec[curr] = 0x7FFFFFFF
        for j in xrange(k):
            x = costs[i][j]
            x += fst[prev] if col[prev] != j else sec[prev]
            if x < fst[curr]:
                sec[curr] = fst[curr]
                fst[curr] = x
                col[curr] = j
            elif x < sec[curr]:
                sec[curr] = x
        curr, prev = prev, curr
    return fst[prev]


//################################################ O(nk) with Map ################################################
class Solution:
    def minCostII(self, costs):
        return min(reduce(self.combine, costs)) if costs else 0

    def combine(self, tmp, house):
        m, n, i = min(tmp), len(tmp), tmp.index(min(tmp))
        tmp, tmp[i] = [m]*n, min(tmp[:i]+tmp[i+1:])
        return map(sum, zip(house, tmp))


//################################################ O(nk) with Lambda ################################################
class Solution:
    # @param {integer[][]} costs
    # @return {integer}
    def minCostII(self, costs):
        return min(reduce(lambda x, y: self.combine(y, x), costs)) if costs else 0

    def combine(self, house, tmp):
        m, n, i = min(tmp), len(tmp), tmp.index(min(tmp))
        tmp = [m]*i + [min(tmp[0:i]+tmp[i+1:])] + [m]*(n-i-1)
        return [sum(i) for i in zip(house, tmp)]

//################################################ O(nk) with functions ################################################
class Solution:
    # @param {integer[][]} costs
    # @return {integer}
    def minCostII(self, costs):
        if not costs:
            return 0
        tmp = [0] * len(costs[0])
        for i in costs:
            tmp = self.combine(i, tmp)
        return min(tmp)

    def combine(self, house, tmp):
        m, n, i = min(tmp), len(tmp), tmp.index(min(tmp))
        tmp = [m]*i + [min(tmp[0:i]+tmp[i+1:] or [0])] + [m]*(n-i-1)
        return [sum(i) for i in zip(house, tmp)]
