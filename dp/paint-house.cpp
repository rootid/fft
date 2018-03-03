//Paint House
//There are a row of n houses, each house can be painted with one of the three
//colors: red, blue or green.
//The cost of painting each house with a certain color is different. You have
//to paint all the houses such that no two adjacent houses have the same color.
//The cost of painting each house with a certain color is represented by a n x
//3 cost matrix.
//For example, costs0 is the cost of painting house 0 with color red; costs1 is
//the cost of painting house 1 with color green, and so on... Find the minimum
//cost to paint all houses.
//Note: All costs are positive integers.
//

//############################### Keep costs array unmodfied ###############################
//T = O(n)
//S = O(1).
class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        if (costs.empty()) return 0;
        int n = costs.size(), r = 0, g = 0, b = 0;
        for (int i = 0; i < n; i++) {
            int rr = r, bb = b, gg = g;
            r = costs[i][0] + min(bb, gg);
            b = costs[i][1] + min(rr, gg);
            g = costs[i][2] + min(rr, bb);
        }
        return min(r, min(b, g));
    }
};

//############################### modify costs array ###############################
public class Solution {
public int minCost(int[][] costs) {
    if(costs == null || costs.length==0){
        return 0;
    }
    for(int i=1; i<costs.length; i++){
        costs[i][0] += Math.min(costs[i-1][1],costs[i-1][2]);
        costs[i][1] += Math.min(costs[i-1][0],costs[i-1][2]);
        costs[i][2] += Math.min(costs[i-1][1],costs[i-1][0]);
    }
    int n = costs.length-1;
    return Math.min(Math.min(costs[n][0], costs[n][1]), costs[n][2]);
}

//######################################################## Pythonic ########################################################
//O(n*k^2) : k = # of colors = 3
def minCost(self, costs):
    prev = [0] * 3
    for now in costs:
        prev = [now[i] + min(prev[:i] + prev[i+1:]) for i in range(3)]
    return min(prev)


def minCost(self, costs):
    return min(reduce(lambda (A,B,C), (a,b,c): (a+min(B,C), b+min(A,C), c+min(A,B)),
                      costs, [0]*3))
