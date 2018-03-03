//Number Of Corner Rectangles
//Given a grid where each entry is only 0 or 1, find the number of corner
//rectangles.
//A corner rectangle is 4 distinct 1s on the grid that form an axis-aligned
//rectangle. Note that only the corners need to have the value 1. Also, all
//four 1s used must be distinct.
//Example 1:
//Input: grid =
//[[1, 0, 0, 1, 0],
// [0, 0, 1, 0, 1],
// [0, 0, 0, 1, 0],
// [1, 0, 1, 0, 1]]
//Output: 1
//Explanation: There is only one corner rectangle, with corners grid[1][2],
//grid[1][4], grid[3][2], grid[3][4].
//Example 2:
//Input: grid =
//[[1, 1, 1],
// [1, 1, 1],
// [1, 1, 1]]
//Output: 9
//Explanation: There are four 2x2 rectangles, four 2x3 and 3x2 rectangles, and
//one 3x3 rectangle.
//Example 3:
//Input: grid =
//[[1, 1, 1, 1]]
//Output: 0
//Explanation: Rectangles must have four distinct corners.
//Note:
//    The number of rows and columns of grid will each be in the range [1, 200].
//    Each grid[i][j] will be either 0 or 1.
//    The number of 1s in the grid will be at most 6000
//
//#########################################  #########################################
class Solution {
    public int countCornerRectangles(int[][] grid) {
        int m = grid.length, n = grid[0].length, cnts = 0;
        for (int i0 = 0; i0 < m; i0++)
            for (int j0 = 0; j0 < n; j0++)
                for (int i = i0 + 1; i < m && grid[i0][j0] != 0; i++)
                    for (int j = j0 + 1; j < n && grid[i][j0] != 0; j++)
                        cnts += grid[i][j] * grid[i0][j];
        return cnts;
    }
}

//######################################### Approach #1: Count Corners  #########################################
//Intuition
//We ask the question: for each additional row, how many more rectangles are
//added?
//For each pair of 1s in the new row (say at new_row[i] and new_row[j]), we
//could create more rectangles where that pair forms the base. The number of
//new rectangles is the number of times some previous row had row[i] = row[j] =
//1.
//Algorithm
//Let's maintain a count count[i, j], the number of times we saw row[i] =
//row[j] = 1. When we process a new row, for every pair new_row[i] = new_row[j]
//= 1, we add count[i, j] to the answer, then we increment count[i, j].
// TC : O(R * C^2)
// SC : O(C^2)
class Solution {
    public int countCornerRectangles(int[][] grid) {
        Map<Integer, Integer> count = new HashMap();
        int ans = 0;
        for (int[] row: grid) {
            for (int c1 = 0; c1 < row.length; ++c1) if (row[c1] == 1) {
                for (int c2 = c1+1; c2 < row.length; ++c2) if (row[c2] == 1) {
                    int pos = c1 * 200 + c2;
                    int c = count.getOrDefault(pos, 0);
                    ans += c;
                    count.put(pos, c+1);
                }
            }
        }
        return ans;
    }
}


//######################################### Approach #2: Heavy and Light Rows #########################################
//Intuition and Algorithm
//Can we improve on the ideas in Approach #1? When a row is filled with XXX 1s,
//we do O(X2)O(X^2)O(X​2​​) work to enumerate every pair of 1s.
//This is okay when XXX is small, but expensive when XXX is big.
//Say the entire top row is filled with 1s. When looking at the next row with
//say, f 1s that match the top row, the number of rectangles created is just
//the number of pairs of 1s, which is f * (f-1) / 2. We could find each f
//quickly using a Set and a simple linear scan of each row.
//Let's call a row to be heavy if it has more than N\sqrt
//N√​N​​​ points. The above algorithm changes the
//complexity of counting a heavy row from O(C2)O(C^2)O(C​2​​) to
//O(N)O(N)O(N), and there are at most N\sqrt N√​N​​​ heavy
//rows.
//
//
//Time Complexity: O(NN)O(N \sqrt N) where NNN is the number of ones in the
//grid.
//Space Complexity: O(N+R+C^2) in additional space, for rows, target, and
//count.

class Solution {
    public int countCornerRectangles(int[][] grid) {
        List<List<Integer>> rows = new ArrayList();
        int N = 0;
        for (int r = 0; r < grid.length; ++r) {
            rows.add(new ArrayList());
            for (int c = 0; c < grid[r].length; ++c)
                if (grid[r][c] == 1) {
                    rows.get(r).add(c);
                    N++;
                }
        }

        int sqrtN = (int) Math.sqrt(N);
        int ans = 0;
        Map<Integer, Integer> count = new HashMap();

        for (int r = 0; r < grid.length; ++r) {
            if (rows.get(r).size() >= sqrtN) {
                Set<Integer> target = new HashSet(rows.get(r));

                for (int r2 = 0; r2 < grid.length; ++r2) {
                    if (r2 <= r && rows.get(r2).size() >= sqrtN)
                        continue;
                    int found = 0;
                    for (int c2: rows.get(r2))
                        if (target.contains(c2))
                            found++;
                    ans += found * (found - 1) / 2;
                }
            } else {
                for (int i1 = 0; i1 < rows.get(r).size(); ++i1) {
                    int c1 = rows.get(r).get(i1);
                    for (int i2 = i1 + 1; i2 < rows.get(r).size(); ++i2) {
                        int c2 = rows.get(r).get(i2);
                        int ct = count.getOrDefault(200*c1 + c2, 0);
                        ans += ct;
                        count.put(200*c1 + c2, ct + 1);
                    }
                }
            }
        }
        return ans;
    }
}
