//The Maze
//There is a ball in a maze with empty spaces and walls. The ball can go through empty spaces by
//rolling up, down, left or right, but it won't stop rolling until hitting a wall. When the ball
//stops, it could choose the next direction.
//Given the ball's start position, the destination and the maze, determine whether the ball could
//stop at the destination.
//The maze is represented by a binary 2D array. 1 means the wall and 0 means the empty space. You
//may assume that the borders of the maze are all walls. The start and destination coordinates are
//represented by row and column indexes.
//Example 1
//Input 1: a maze represented by a 2D array
//0 0 1 0 0
//0 0 0 0 0
//0 0 0 1 0
//1 1 0 1 1
//0 0 0 0 0
//Input 2: start coordinate (rowStart, colStart) = (0, 4)
//Input 3: destination coordinate (rowDest, colDest) = (4, 4)
//Output: true
//Explanation: One possible way is : left -> down -> left -> down -> right -> down -> right.
//Example 2
//Input 1: a maze represented by a 2D array
//0 0 1 0 0
//0 0 0 0 0
//0 0 0 1 0
//1 1 0 1 1
//0 0 0 0 0
//Input 2: start coordinate (rowStart, colStart) = (0, 4)
//Input 3: destination coordinate (rowDest, colDest) = (3, 2)
//Output: false
//Explanation: There is no way for the ball to stop at the destination.
//Note:
//There is only one ball and one destination in the maze.
//Both the ball and the destination exist on an empty space, and they will not be at the same
//position initially.
//The given maze does not contain border (like the red rectangle in the example pictures), but you
//could assume the border of the maze are all walls.
//The maze contains at least 2 empty spaces, and both the width and height of the maze won't exceed
//100.
//


//################################################### DFS  ###################################################
//TC : O(nm)
//SC : O(nm)
public class Solution {
    public boolean hasPath(int[][] maze, int[] start, int[] destination) {
        boolean[][] visited = new boolean[maze.length][maze[0].length];
        return dfs(maze, start, destination, visited);
    }
    public boolean dfs(int[][] maze, int[] start, int[] destination, boolean[][] visited) {
        if (visited[start[0]][start[1]])
            return false;
        if (start[0] == destination[0] && start[1] == destination[1])
            return true;
        visited[start[0]][start[1]] = true;
        int r = start[1] + 1, l = start[1] - 1, u = start[0] - 1, d = start[0] + 1;
        while (r < maze[0].length && maze[start[0]][r] == 0) // right
            r++;
        if (dfs(maze, new int[] {start[0], r - 1}, destination, visited))
            return true;
        while (l >= 0 && maze[start[0]][l] == 0) //left
            l--;
        if (dfs(maze, new int[] {start[0], l + 1}, destination, visited))
            return true;
        while (u >= 0 && maze[u][start[1]] == 0) //up
            u--;
        if (dfs(maze, new int[] {u + 1, start[1]}, destination, visited))
            return true;
        while (d < maze.length && maze[d][start[1]] == 0) //down
            d++;
        if (dfs(maze, new int[] {d - 1, start[1]}, destination, visited))
            return true;
        return false;
    }
}

//################################################### BFS ###################################################
//TC : O(nm)
//SC : O(nm)
public class Solution {
    public boolean hasPath(int[][] maze, int[] start, int[] destination) {
        boolean[][] visited = new boolean[maze.length][maze[0].length];
        int[][] dirs={{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
        Queue < int[] > queue = new LinkedList < > ();
        queue.add(start);
        visited[start[0]][start[1]] = true;
        while (!queue.isEmpty()) {
            int[] s = queue.remove();
            if (s[0] == destination[0] && s[1] == destination[1])
                return true;
            for (int[] dir: dirs) {
                int x = s[0] + dir[0];
                int y = s[1] + dir[1];
                while (x >= 0 && y >= 0 && x < maze.length && y < maze[0].length && maze[x][y] == 0) {
                    x += dir[0];
                    y += dir[1];
                }
                if (!visited[x - dir[0]][y - dir[1]]) {
                    queue.add(new int[] {x - dir[0], y - dir[1]});
                    visited[x - dir[0]][y - dir[1]] = true;
                }
            }
        }
        return false;
    }
}

//################################################### DFS ###################################################
int[][] dirs = new int[][]{ {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

public boolean hasPath(int[][] maze, int[] start, int[] destination) {
    boolean[][] visited = new boolean[maze.length][maze[0].length];
    return dfs(maze, start, destination, visited);
}

private boolean dfs(int[][] maze, int[] p, int[] destination, boolean[][] visited) {
    if (visited[p[0]][p[1]]) {
        return false;
    }
    if (p[0] == destination[0] && p[1] == destination[1]) {
        return true;
    }
    visited[p[0]][p[1]] = true;
    for (int i = 0; i < dirs.length; i++) {
        int[] d = dirs[i];
        int row = p[0];
        int col = p[1];
        while (isValid(maze, row + d[0], col + d[1])) {
            row += d[0];
            col += d[1];
        }
        if (dfs(maze, new int[]{ row, col }, destination, visited)) {
            return true;
        }
    }
    return false;
}

private boolean isValid(int[][] maze, int row, int col) {
    return row >= 0 && row < maze.length && col >= 0 && col < maze[0].length && maze[row][col] != 1;
}

//################################################### DFS ###################################################
class Solution {
public:
   bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        set<vector<int>> visited;
        return helper(maze, start, destination, visited);
    }

private :
    bool helper(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination, set<vector<int>>& visited) {
        if(start == destination) return true;
        if(visited.find(start) != visited.end()) return false;
        visited.insert(start);
        vector<vector<int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for(int i = 0; i < 4; i++) {
            vector<int> res = go2End(maze, start, dirs[i]);
            if(res == destination || helper(maze, res, destination, visited)) return true;
        }
        return false;
    }
    vector<int> go2End(vector<vector<int>>& maze, vector<int>& start, vector<int>& dir) {
        int i = start[0] + dir[0];
        int j = start[1] + dir[1];
        int m = maze.size();
        int n = maze[0].size();
        if(i < 0 || i >= m || j < 0 || j >= n || maze[i][j] == 1) {
            return start;
        }
        vector<int> newStart = {i, j};
        return go2End(maze, newStart, dir);
    }
}


//################################################### DFS ###################################################
class Solution {
    int m, n; // maze dimension
    unordered_set<int> visited; // global index of visited cells(i,j) = i*n+j

    bool hasPath(vector<vector<int>>& maze, const vector<int>& s/*start*/, vector<int>& e/*end*/) {
        if(s == e) return true;
        if (visited.empty()){
			m = maze.size(), n = maze[0].size();
		}
        if(!visited.insert(s[0]*n+s[1]).second) {
			return false; // if already visited
		}
        for(int d: {1, -1, n, -n} ) { // global index of each directional vector
          int i=s[0], j=s[1];
          while(i*(i-m+1)<=0 && j*(j-n+1)<=0 && !maze[i][j]) {
			  i+=d/n, j+=d%n; // go straight
		  }
          if(hasPath(maze, {i-=d/n,j-=d%n}, e)) {
			  return true; // start from new location (i,j)
		  }
        }
        return false;
    }
};

//T : O(mn), S : O(mn)
//################################################### BFS ###################################################
public boolean hasPath(int[][] maze, int[] start, int[] destination) {
    if (start[0] == destination[0] && start[1] == destination[1]) {
		return true;
	}
    Queue<int[]> queue = new LinkedList<int[]>();
	final int[][] dir = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    queue.offer(start);
    int m = maze.length;
    int n = maze[0].length;
    boolean[][] visited = new boolean[m][n];
    visited[start[0]][start[1]] = true;
    while (!queue.isEmpty()) {
        int[] cur = queue.poll();
        for (int k = 0; k < dir.length; k++) {
            int x = cur[0];
            int y = cur[1];
			//Traverse untill hit the wall
            while (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == 0) {
                x += dir[k][0];
                y += dir[k][1];
            }
			//Take a step back
            x -= dir[k][0];
            y -= dir[k][1];
            if (visited[x][y]){
				continue;
			}
            visited[x][y] = true;
            if (x == destination[0] && y == destination[1]) {
				return true;
			}
            queue.offer(new int[] {x, y});
        }
    }
}


//################################################### Pythonic ###################################################
//################################################### BFS ###################################################
def hasPath(self, maze, start, destination):

        Q = [start]
        n = len(maze)
        m = len(maze[0])
        dirs = ((0, 1), (0, -1), (1, 0), (-1, 0))
        while Q:
            # Use Q.pop() as DFS or Q.popleft() with deque from collections library for better performance. Kudos to @whglamrock
            i, j = Q.pop(0)
            maze[i][j] = 2

            if i == destination[0] and j == destination[1]:
                return True

            for x, y in dirs:
                row = i + x
                col = j + y
                while 0 <= row < n and 0 <= col < m and maze[row][col] != 1:
                    row += x
                    col += y
                row -= x
                col -= y
                if maze[row][col] == 0:
                    Q.append([row, col])

        return False
