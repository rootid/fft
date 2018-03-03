//Shopping Offers
//In LeetCode Store, there are some kinds of items to sell. Each item has a
//price.
//However, there are some special offers, and a special offer consists of one
//or more different kinds of items with a sale price.
//You are given the each item'sIdx price, a set of special offers, and the
//number we need to buy for each item. The job is to output the lowest price
//you have to pay for exactly certain items as given, where you could make
//optimal use of the special offers.
//Each special offer is represented in the form of an array, the last number
//represents the price you need to pay for this special offer, other numbers
//represents how many specific items you could get if you buy this offer.
//You could use any of special offers as many times as you want.
//Example 1:
//Input: [2,5], [[3,0,5],[1,2,10]], [3,2]
//Output: 14
//Explanation:
//There are two kinds of items, A and B. Their prices are $2 and $5
//respectively.
//In special offer 1, you can pay $5 for 3A and 0B
//In special offer 2, you can pay $10 for 1A and 2B.
//You need to buy 3A and 2B, so you may pay $10 for 1A and 2B (special offer
//#2), and $4 for 2A.
//Example 2:
//Input: [2,3,4], [[1,1,0,4],[2,2,1,9]], [1,2,1]
//Output: 11
//Explanation:
//The price of A is $2, and $3 for B, $4 for C.
//You may pay $4 for 1A and 1B, and $9 for 2A ,2B and 1C.
//You need to buy 1A ,2B and 1C, so you may pay $4 for 1A and 1B (special offer
//#1), and $3 for 1B, $4 for 1C.
//You cannot add more items, though only $9 for 2A ,2B and 1C.
//Note:
//There are at most 6 kinds of items, 100 special offers.
//For each item, you need to buy at most 6 of them.
//You are not allowed to buy more items than you want, even if that would lower
//the overall price
//

//################################################### With backtracking###################################################
class Solution {
public:
    int shoppingOffers(const vector<int>& price, const vector<vector<int>>& special, const vector<int>& needs) {
        int result = inner_product(price.begin(), price.end(), needs.begin(), 0);
        for (const vector<int>& offer : special) {
            vector<int> r = can(needs, offer);
            if (r.empty()) continue;
            result = min(result, offer.back() + shoppingOffers(price, special, r));
        }
        return result;
    }
    vector<int> can(const vector<int>& needs, const vector<int>& offer) {
        vector<int> r(needs.size(), 0);
        for (int i = 0, n = needs.size(); i < n; ++i) {
            if (offer[i] > needs[i]) return vector<int>();
            r[i] = needs[i] - offer[i];
        }
        return r;
    }
};

//################################################### With Operator Overloading  ###################################################
void operator+=(vector<int> &a, const vector<int> &b) {
    for (int i = 0; i < a.size(); i++)
        a[i] += b[i];
}
void operator-=(vector<int> &a, const vector<int> &b) {
    for (int i = 0; i < a.size(); i++)
        a[i] -= b[i];
}
bool operator<(const vector<int> &a, const int &n) {
    for (int i : a)
        if (i < n)
            return true;
    return false;
}
int operator*(const vector<int> &a, const vector<int> &b) {
    int res = 0;
    for (int i = 0; i < a.size(); i++)
        res += a[i] * b[i];
    return res;
}
class Solution {
   public:
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs, int cost = 0) {
		if (needs < 0)
			return INT_MAX;
		int m = cost + needs * price;
		for (auto &offer : special) {
			if (cost + offer.back() >= m) // pruning
				continue;
			needs -= offer;
			m = min(m, shoppingOffers(price, special, needs, cost + offer.back()));
			needs += offer;
		}
		return m;
	}
};

//################################################### With Operator Overloading  ###################################################
class Solution {
public:
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        return helper(price, special, needs, 0);
    }

    long int helper(vector<int>& price, vector<vector<int>>& special, vector<int>& needs, int sIdx) { //sIdx : special offer idx
        if(sIdx >= special.size()) { //finished all offers
            int cost = 0;
            for(int i=0; i < needs.size(); ++i) {
				cost += price[i]*needs[i];
			}
            return cost;
        }
        long unused = helper(price, special, needs, sIdx+1); //pick next offer
        bool valid = true;
        for(int i = 0; i < needs.size(); ++i)  {
            needs[i] -= special[sIdx][i]; //update the neeeds
            valid = valid && needs[i] >= 0;
        }
        long used = INT_MAX;;
        if(valid) { //if got a valid offer backtrack
            used = special[sIdx].back() + helper(price, special, needs, sIdx);
        }
        for(int i = 0; i < needs.size(); ++i)  {
            needs[i] += special[sIdx][i]; //update the needs for to backtrack
        }
        return min(used, unused);
    }
};


//################################################### Backtrack + memory ###################################################
//
//The idea is to try every special offer using DFS, and memorize intermediate
//results, which is one type of DP.
//There is at most 6 items and each item is at most 6, so we can use a 6 digit
//int as the key.
//Test every special offer. If invalid, break.
//We have to pay for EXACTLY certain items, no more no less.
//Greedy doesn't work.
//One example is [3, 2], [[1, 2, 4] [2, 1, 5]], [6, 6]. We need 2 first offers
//and 2 second offers. Greedy would choose 3 first offers.
class Solution {
public:
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        // memorize intermediate results
        unordered_map<int, int> mp;
        return helper(price, special, mp, get_key(needs));
    }
private:
    int helper(vector<int>& price, vector<vector<int>>& special, unordered_map<int, int>& mp, int k) {
        if (mp.count(k)) return mp[k];
        int n = price.size(), ans = 0;
        // pows is to help get each digit of key
        vector<int> pows(n, 1);
        for (int i = n-2; i >= 0; i--) {
			pows[i] = pows[i+1]*10;
		}
        for (int i = 0; i < n; i++) {
			ans += ((k/pows[i])%10)*price[i];
		}
        for (auto spe:special) {
            int key = 0, i = 0;
            // check whether this offer is valid
            while (i < n) {
                int t = (k/pows[i])%10;
                if (t >= spe[i])
                    key = key*10+(t-spe[i++]);
                else
                    break;
            }
            if (i == n) ans = min(ans, spe[n]+helper(price, special, mp, key));
        }
        mp[k] = ans;
        return ans;
    }
    int get_key(vector<int>& needs) {
        int n = needs.size(), key = 0;
        for (int i = n-1, p = 1; i >= 0; i--, p *= 10)
            key += needs[i]*p;
        return key;
    }
};

//################################################### DP + 6D matrix ###################################################
//
//it seems very like the dynamic programming problem. But when I solve the dp
//problem such like knapsack problem. I need the end of this problem, i.e. the
//volume of knapsack. If I know this, then the problem totally a knapsack
//problem. luckily, I get this from
//There are at most 6 kinds of items, 100 special offers.
//1. For each item, you need to buy at most 6 of them.
//2. Then I add to 6 item for every input argument.
//3. This code have O(special offers size) time complex. When the input is
//small, it's not the best time complex. And it also not very general.
int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs)
{
	int n = price.size();
	for (int i = n; i < 6; i++)
	{
		price.push_back(0);
		needs.push_back(0);
	}
	for (int i = special.size() - 1; i >= 0; i--)  // fill special to 6 items
	{
		int t = special[i][n];
		special[i][n] = 0;
		for (int j = n + 1; j < 7; j++)
			special[i].push_back(0);
		special[i][6] = t;
	}
	vector<int> temp(7);
	for (int i = 0; i < 6; i++)   //treat every item as a special offer only have itself with its price
	{
		for (int j = 0; j < 6; j++)
		if (j != i)
			temp[j] = 0;
		else
			temp[j] = 1;
		temp[6] = price[i];
		special.push_back(temp);
	}
	int dp[7][7][7][7][7][7], m = special.size();
	//memset(dp, INT_MAX, 7 * 7 * 7 * 7 * 7 * 7);
       //I don't know why this memset useless, it just put every element to -1
	for (int j = 0; j < 7; j++)        // so I have initial it using loop
	{
		for (int k = 0; k < 7; k++)
		for (int p = 0; p < 7; p++)
		for (int q = 0; q < 7; q++)
		for (int r = 0; r < 7; r++)
		for (int s = 0; s < 7; s++)

			dp[j][k][p][q][r][s] = INT_MAX;
	}
	dp[0][0][0][0][0][0] = 0;
	for (int i = 0; i < m; i++)  // then it just a dynamic programming problem
	{
		for (int j = special[i][0]; j < 7; j++)
		for (int k = special[i][1]; k < 7; k++)
		for (int p = special[i][2]; p < 7; p++)
		for (int q = special[i][3]; q < 7; q++)
		for (int r = special[i][4]; r < 7; r++)
		for (int s = special[i][5]; s < 7; s++)
		{
		        int tt = dp[j-special[i][0]][k-special[i][1]][p-special[i][2]]
                              [q-special[i][3]][r-special[i][4]][s-special[i][5]];
		        if (tt != INT_MAX)
			        dp[j][k][p][q][r][s] = min(dp[j][k][p][q][r][s], tt + special[i][6]);
		}
	}
	return dp[needs[0]][needs[1]][needs[2]][needs[3]][needs[4]][needs[5]];
}


//################################################### DP + 6D matrix + JAVA ###################################################
public int shoppingOffers(List<Integer> price, List<List<Integer>> special, List<Integer> needs) {

        if (null == price || 0 == price.size() || null == needs || 0 == needs.size())
            return 0;

        int item0 = needs.get(0),
            item1 = needs.size() >= 2? needs.get(1) : 0,
            item2 = needs.size() >= 3? needs.get(2) : 0,
            item3 = needs.size() >= 4? needs.get(3) : 0,
            item4 = needs.size() >= 5? needs.get(4) : 0,
            item5 = needs.size() >= 6? needs.get(5) : 0;

        // 6 dimensional dp
        int[][][][][][] dp = new int[7][7][7][7][7][7];

        int price0 = price.get(0),
            price1 = price.size() >= 2? price.get(1) : 0,
            price2 = price.size() >= 3? price.get(2) : 0,
            price3 = price.size() >= 4? price.get(3) : 0,
            price4 = price.size() >= 5? price.get(4) : 0,
            price5 = price.size() >= 6? price.get(5) : 0;

        // fill special to length 7
        // the actual items listed in an offer
    	// *** fill special is different, as the price 2 3 5, should be 2 3 0 0 0 0 5 (the cost is 5)
        // not 2 3 5 0 0 0 0 (the cost is 0)
        if (special != null && special.size() > 0 && special.size() < 7) {
	        for (int i = 0; i < special.size(); i ++) {
	        	List<Integer> temp = special.get(i);
	        	for (int j = price.size(); j < 6; j ++) temp.add(j, 0);
	        }
        }

        // init dp array
        // dp[0][0][x][0][0][0], set as single price
        dp[0][0][0][0][0][0] = 0;

        for (int i = 0; i < 7; i ++)
            for (int j = 0; j < 7; j ++)
                for (int k = 0; k < 7; k ++)
                    for (int l = 0; l < 7; l ++)
                        for (int m = 0; m < 7; m ++)
                            for (int n = 0; n < 7; n ++) {
                                dp[i][j][k][l][m][n] = price0 * i + price1 * j + price2 * k
                                    + price3 * l + price4 * m + price5 * n;
                            }

        for (List<Integer> cur: special) {

            for (int i = cur.get(0); i < 7; i ++)
                for (int j = cur.get(1); j < 7; j ++)
                    for (int k = cur.get(2); k < 7; k ++)
                        for (int l = cur.get(3); l < 7; l ++)
                            for (int m = cur.get(4); m < 7; m ++)
                                for (int n = cur.get(5); n < 7; n ++) {
                                	dp[i][j][k][l][m][n] = Math.min(dp[i][j][k][l][m][n],
                                            dp[i - cur.get(0)][j - cur.get(1)][k - cur.get(2)][l - cur.get(3)]
                                                [m - cur.get(4)][n - cur.get(5)] + cur.get(6));
                                }
        }

        return dp[item0][item1][item2][item3][item4][item5];
    }


//################################################### Python  ###################################################
//################################################### Backtrack + memory  ###################################################
def shoppingOffers(self, price, special, needs):
        d = {}
        def dfs(cur):
            val = sum(cur[i]*price[i] for i in range(len(needs))) #cost without special
            for spec in special:
                tmp = [cur[j] - spec[j] for j in range(len(needs))]
                if min(tmp) >= 0: # skip deals that exceed needs
                    val = min(val, d.get(tuple(tmp), dfs(tmp)) + spec[-1]) # .get check the dictionary first for result, otherwise perform dfs.
            d[tuple(cur)] = val
            return val
        return dfs(needs)

//################################################### Backtrack + memory  ###################################################
//For convenience, let's think in terms of value, the discount each special
//offer gives from the nominal price. (The values in this array are
//non-positive.)
//Our goal is to minimize the sum of our discount. Our top-down dp function,
//discount, will do this.
//Suppose we are currently considering the ith special offer, and we have some
//order.
//We must use some legal number of this offer special[i]: if we use K of them,
//then we will get a discount of K * value[i], and in turn this will specify
//the candidates for our dp.
//Let's also memoize to reduce repeated work - there are up to 7^6 * 100 =
//about 11 million states, which will fit memory.
def shoppingOffers(self, price, special, needs):
    def nominal_price(offer):
        return sum(p * offer[i] for i, p in enumerate(price))

    value = [offer.pop() - nominal_price(offer) for offer in special]

    memo = {}
    def discount(i, *order):
        if i == len(special):
            return 0
        if (i, order) not in memo:
            ans = discount(i+1, *order)
            val = 0
            cur_order = order[:]
            while True:
                cur_order = map(operator.sub, cur_order, special[i])
                val += value[i]
                if any(x < 0 for x in cur_order): break
                ans = min(ans, val + discount(i+1, *cur_order))
            memo[i, order] = ans
        return memo[i, order]

    return nominal_price(needs) + discount(0, *needs)
