//Number of Distinct Islands
//Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's
//(representing land) connected 4-directionally (horizontal or vertical.) You
//may assume all four edges of the grid are surrounded by water.
//Count the number of distinct islands. An island is considered to be the same
//as another if and only if one island can be translated (and not rotated or
//reflected) to equal the other.
//Example 1:
//11000
//11000
//00011
//00011
//Given the above grid map, return 1.
//Example 2:
//11011
//10000
//00001
//11011
//Given the above grid map, return 3.
//Notice that:
//11
//1
//and
// 1
//11
//are considered different island shapes, because we do not consider reflection
/// rotation.
//Note: The length of each dimension in the given grid does not exceed 50.
//######################################### Hash By Local Coordinates #########################################
//Intuition and Algorithm
//At the beginning, we need to find every island, which we can do using a
//straightforward depth-first search. The hard part is deciding whether two
//islands are the same.
//Since two islands are the same if one can be translated to match another,
//let's translate every island so the top-left corner is (0, 0) For example, if
//an island is made from squares [(2, 3), (2, 4), (3, 4)], we can think of this
//shape as [(0, 0), (0, 1), (1, 1)] when anchored at the top-left corner.
//From there, we only need to check how many unique shapes there ignoring
//permutations (so [(0, 0), (0, 1)] is the same as [(0, 1), (1, 0)]). We use
//sets directly as we have showcased below, but we could have also sorted each
//list and put those sorted lists in our set structure shapes.
//In the Java solution, we converted our tuples (r - r0, c - c0) to integers.
//We multiplied the number of rows by 2 * grid[0].length instead of
//grid[0].length because our local row-coordinate could be negative.
//Time Complexity: O(R∗C), where RRR is the number of rows in the given grid,
//and CCC is the number of columns. We visit every square once.
//Space complexity: O(R∗C), the space used by seen to keep track of visited
//squares, and shapes.
class Solution {
    int[][] grid;
    boolean[][] seen;
    Set<Integer> shape;

    public void explore(int r, int c, int r0, int c0) {
        if (0 <= r && r < grid.length && 0 <= c && c < grid[0].length &&
                grid[r][c] == 1 && !seen[r][c]) {
            seen[r][c] = true;
            shape.add((r - r0) * 2 * grid[0].length + (c - c0));
            explore(r+1, c, r0, c0);
            explore(r-1, c, r0, c0);
            explore(r, c+1, r0, c0);
            explore(r, c-1, r0, c0);
        }
    }
    public int numDistinctIslands(int[][] grid) {
        this.grid = grid;
        seen = new boolean[grid.length][grid[0].length];
        Set shapes = new HashSet<HashSet<Integer>>();

        for (int r = 0; r < grid.length; r++) {
            for (int c = 0; c < grid[0].length; c++) {
                shape = new HashSet<Integer>();
                explore(r, c, r, c);
                if (!shape.isEmpty()) {
                    shapes.add(shape);
                }
            }
        }

        return shapes.size();
    }
}


//######################################### Approach #2: Hash By Path Signature #########################################
//Intuition and Algorithm
//When we start a depth-first search on the top-left square of some island, the
//path taken by our depth-first search will be the same if and only if the
//shape is the same. We can exploit this by recording the path we take as our
//shape - keeping in mind to record both when we enter and when we exit the
//function. The rest of the code remains as in Approach #1.
//Time and Space Complexity: O(R∗C). The analysis is the same as in Approach
//#1.
class Solution {
    int[][] grid;
    boolean[][] seen;
    ArrayList<Integer> shape;

    public void explore(int r, int c, int di) {
        if (0 <= r && r < grid.length && 0 <= c && c < grid[0].length &&
                grid[r][c] == 1 && !seen[r][c]) {
            seen[r][c] = true;
            shape.add(di);
            explore(r+1, c, 1);
            explore(r-1, c, 2);
            explore(r, c+1, 3);
            explore(r, c-1, 4);
            shape.add(0);
        }
    }
    public int numDistinctIslands(int[][] grid) {
        this.grid = grid;
        seen = new boolean[grid.length][grid[0].length];
        Set shapes = new HashSet<ArrayList<Integer>>();

        for (int r = 0; r < grid.length; r++) {
            for (int c = 0; c < grid[0].length; c++) {
                shape = new ArrayList<Integer>();
                explore(r, c, 0);
                if (!shape.isEmpty()) {
                    shapes.add(shape);
                }
            }
        }

        return shapes.size();
    }
}



//######################################### DFS + HashTable #########################################
class Solution {
    private static int[][] delta = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
    public int numDistinctIslands(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        Set<List<List<Integer>>> islands = new HashSet<>();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                List<List<Integer>> island = new ArrayList<>();
                if (dfs(i, j, i, j, grid, m, n, island))
                    islands.add(island);
            }
        }
        return islands.size();
    }
    private boolean dfs(int i0, int j0, int i, int j, int[][] grid, int m, int n, List<List<Integer>> island) {
        if (i < 0 || m <= i || j < 0 || n <= j || grid[i][j] <= 0) return false;
        island.add(Arrays.asList(i - i0, j - j0));
        grid[i][j] *= -1;
        for (int d = 0; d < 4; d++) {
            dfs(i0, j0, i + delta[d][0], j + delta[d][1], grid, m, n, island);
        }
        return true;
    }
}
