//Remove Boxes
//Given several boxes with different colors represented by different positive
//numbers.
//You may experience several rounds to remove boxes until there is no box left.
//Each time you can choose some continuous boxes with the same color (composed
//of k boxes, k >= 1), remove them and get k*k points.
//Find the maximum points you can get.
//Example 1:
//Input:
//[1, 3, 2, 2, 2, 3, 4, 3, 1]
//Output:
//23
//Explanation:
//[1, 3, 2, 2, 2, 3, 4, 3, 1]
//----> [1, 3, 3, 4, 3, 1] (3*3=9 points)
//----> [1, 3, 3, 3, 1] (1*1=1 points)
//----> [1, 1] (3*3=9 points)
//----> [] (2*2=4 points)
//Note: The number of boxes n would not exceed 100.
//LC 312 Burst Balloons
http://poj.org/problem?id=1390

//######################################### DP - 3D #########################################
//When facing this problem, I am keeping thinking how to simulate the case when
//boxes[i] == boxes[j] when i and j are not consecutive.
// It turns out that the dp matrix needs one more dimension to store such state. So we are going to define the state as
//dp[i][j][k] represents the max points from box[i] to box[j] with k boxes
//whose values equal to box[i]
//The transformation function is as below
//dp[i][j][k] = max(dp[i+1][m-1][1] + dp[m][j][k+1]) when box[i] = box[m]

//dp[i][j][k] represents the max points from box[i] to box[j] with k boxes
//whose values equal to box[i]
//However, I think dp[i][j][k] should mean the max points from box[i] to box[j]
//with k boxes of value box[i] merged.
//And also the DP
//We have two condition
//We choose to merge k boxes
//this mean we would have score = dp(i+1, j, 1) + k * k ...............(1)
//We don't merge k boxes
//so, we can continue to find box which is the same
//this means when we find box m equal to box i, we can have one more box, so k
//become k + 1
//So we have dp(i+1, m-1, 1) + dp (m, j, k + 1) ...............(2)
//the first term is the other boxes
//and the second term contain information of the same boxes(box[i] or box[m])
//we have found till now
//dp[i][j][k] = max ((1), (2))

public int removeBoxes(int[] boxes) {
    if (boxes == null || boxes.length == 0) {
        return 0;
    }
    int size = boxes.length;
    int[][][] dp = new int[size][size][size];
    return get(dp, boxes, 0, size-1, 1);
}

private int get(int[][][] dp, int[] boxes, int i, int j, int k) {
    if (i > j) {
        return 0;
    } else if (i == j) {
        return k * k;
    } else if (dp[i][j][k] != 0) {
        return dp[i][j][k];
    } else {
        int temp = get(dp, boxes, i + 1, j, 1) + k * k;
        for (int m = i + 1; m <= j; m++) {
            if (boxes[i] == boxes[m]) {
                temp = Math.max(temp, get(dp, boxes, i + 1, m - 1, 1) + get(dp, boxes, m, j, k + 1));
            }
        }
        dp[i][j][k] = temp;
        return temp;
    }
}

//######################################### DP #########################################
//Let A be the array of boxes.
//One natural approach is to consider dp(i, j) = the answer for A[i: j+1]. But
//this isn't flexible enough for divide and conquer style strategies. For
//example, with [1,2,2,2,1], we don't have enough information when
//investigating things like [1,2,2,2] and [1] separately.
//Let dp(i, j, k) = the maximum value of removing boxes if we have k extra
//boxes of color A[i] to the left of A[i: j+1]. (We would have at most k <
//len(A) extra boxes.) Let m <= j be the largest value so that A[i], A[i+1],
//... A[m] are all the same color. Because a^2 + b^2 < (a+b)^2, any block of
//contiguous boxes of the same color must be removed at the same time, so in
//fact dp(i, j, k) = dp(m, j, k+(m-i)).
//Now, we could remove the k boxes we were carrying plus box A[i] (value:
//(k+1)**2), then remove the rest (value: dp(i+1, j, 0)). Or, for any point m
//in [i+1, j] with A[i] == A[m], we could remove dp(i+1, m-1) first, then [m,
//j] would have k+1 extra boxes of color A[m] behind, which has value dp(m, j,
//k+1).
//The "i, k = m, k + m - i" part skips order (m-i)*(j-i) calls to dp, and is
//necessary to get this kind of solution to pass in Python.

def removeBoxes(self, A):
    N = len(A)
    memo = [[[0]*N for _ in xrange(N) ] for _ in xrange(N) ]

    def dp(i, j, k):
        if i > j: return 0
        if not memo[i][j][k]:
            m = i
            while m+1 <= j and A[m+1] == A[i]:
                m += 1
            i, k = m, k + m - i
            ans = dp(i+1, j, 0) + (k+1) ** 2
            for m in xrange(i+1, j+1):
                if A[i] == A[m]:
                    ans = max(ans, dp(i+1, m-1, 0) + dp(m, j, k+1))
            memo[i][j][k] = ans
        return memo[i][j][k]

    return dp(0, N-1, 0)

//######################################### DFS + DP #########################################
//======================= Explanation ===========================
//First Attempt
//The initial thought is straightforward, try every possible removal and
//recursively search the rest. No doubt it will be a TLE answer. Obviously
//there are a lot of recomputations involved here. Memoization is the key then.
//But how to design the memory is tricky. I tried to use a string of 0s and 1s
//to indicate whether the box is removed or not, but still getting TLE.
//One step further
//I think the problem of the approach above is that there are a lot of
//unnecessary computations (not recomputations). For example, if there is a
//formation of ABCDAA, we know the optimal way is B->C->D->AAA. On the other
//hand, if the formation is BCDAA, meaning that we couldn't find an A before D,
//we will simply remove AA, which will be the optimal solution for removing
//them. Note this is true only if AA is at the end of the array. With naive
//memoization approach, the program will search a lot of unnecessary paths,
//such as C->B->D->AA, D->B->C->AA.
//Therefore, I designed the memoization matrix to be memo[l][r][k], the largest
//number we can get using lth to rth (inclusive) boxes with k same colored
//boxes as rth box appended at the end. Example, memo[l][r][3] represents the
//solution for this setting: [b_l, ..., b_r, A,A,A] with b_r==A.
//The transition function is to find the maximum among all b_i==b_r for
//i=l,...,r-1:
//memo[l][r][k] = max(memo[l][r][k], memo[l][i][k+1] + memo[i+1][r-1][0])
//Basically, if there is one i such that b_i==b_r, we partition the array into
//two: [b_l, ..., b_i, b_r, A, ..., A], and [b_{i+1}, ..., b_{r-1}]. The
//solution for first one will be memo[l][i][k+1], and the second will be
//memo[i+1][r-1][0]. Otherwise, we just remove the last k+1 boxes (including
//b_r) and search the best solution for lth to r-1th boxes. (One optimization
//here: make r as left as possible, this improved the running time from 250ms
//to 35ms)
//The final solution is stored in memo[0][n-1][0] for sure.
//I didn't think about this question for a long time in the contest because the
//time is up. There will be a lot of room for time and space optimization as
//well. Thus, if you find any flaws or any improvements, please correct me.

class Solution {
public:
    int removeBoxes(vector<int>& boxes) {
        int n=boxes.size();
        int memo[100][100][100] = {0};
        return dfs(boxes,memo,0,n-1,0);
    }

    int dfs(vector<int>& boxes,int memo[100][100][100], int l,int r,int k){
        if (l>r) return 0;
        if (memo[l][r][k]!=0) return memo[l][r][k];

        while (r>l && boxes[r]==boxes[r-1]) {r--;k++;}
        memo[l][r][k] = dfs(boxes,memo,l,r-1,0) + (k+1)*(k+1);
        for (int i=l; i<r; i++){
            if (boxes[i]==boxes[r]){
                memo[l][r][k] = max(memo[l][r][k], dfs(boxes,memo,l,i,k+1) + dfs(boxes,memo,i+1,r-1,0));
            }
        }
        return memo[l][r][k];
    }
};

//######################################### DFS + DP #########################################
class Solution {
private :
	int cache[100][100][100] = { 0, };
	int dp(vector<int>& boxes, int l, int r, int choiced)//choiced means the num of boxes user choose which is same color with boxes[l] in range [0,  l)
	{
		if (l > r)	return 0;
		int& ret = cache[l][r][choiced];
		if (ret)return ret;
		ret = (choiced + 1) * (choiced + 1) + dp(boxes, l + 1, r, 0);// remove boxes user choose which are same color with left most box(boxes[l])
		for (int mid = l + 1; mid <= r; mid++)
		{
			if (boxes[mid] != boxes[l])continue;
			ret = max(ret, (dp(boxes, l + 1, mid - 1, 0) + dp(boxes,mid, r, choiced + 1)));
			//dp(boxes, l + 1, mid - 1, 0) new dp in range [l+1,mid - 1]
			//dp(boxes,mid, r, choiced + 1) inc choiced box(boxes[l]) and dp in range[mid,r]
			//ㄴ>(boxes[l] == boxes[mid]) so, choiced is increased in range [0,mid)
		}
		return ret;
	}
public:
	int removeBoxes(vector<int>& boxes)
	{
		return dp(boxes,0, boxes.size() - 1, 0);
	}
};
