//Pacific Atlantic Water Flow
//Given an m x n matrix of non-negative integers representing the height of
//each unit cell in a continent, the "Pacific ocean" touches the left and top
//edges of the matrix and the "Atlantic ocean" touches the right and bottom
//edges.
//Water can only flow in four directions (up, down, left, or right) from a cell
//to another one with height equal or lower.
//Find the list of grid coordinates where water can flow to both the Pacific
//and Atlantic ocean.
//Note:
//The order of returned grid coordinates does not matter.
//Both m and n are less than 150.
//Example:
//Given the following 5x5 matrix:
//  Pacific ~   ~   ~   ~   ~
//       ~  1   2   2   3  (5) *
//       ~  3   2   3  (4) (4) *
//       ~  2   4  (5)  3   1  *
//       ~ (6) (7)  1   4   5  *
//       ~ (5)  1   1   2   4  *
//          *   *   *   *   * Atlantic
//Return:
//[[0, 4], [1, 3], [1, 4], [2, 2], [3, 0], [3, 1], [4, 0]] (positions with parentheses in above matrix).
//

//1. Two Queue and add all the Pacific border to one queue; Atlantic border to
//another queue.
//2. Keep a visited matrix for each queue. In the end, add the cell visited by
//two queue to the result.
//BFS: Water flood from ocean to the cell. Since water can only flow from
//high/equal cell to low cell,
//add the neighboor cell with height larger or equal to current cell to the
//queue and mark as visited.

//######################################### BFS #########################################
public class Solution {
    int[][]dir = new int[][]{{1,0},{-1,0},{0,1},{0,-1}};
    public List<int[]> pacificAtlantic(int[][] matrix) {
        List<int[]> res = new LinkedList<>();
        if(matrix == null || matrix.length == 0 || matrix[0].length == 0){
            return res;
        }
        int n = matrix.length, m = matrix[0].length;
        //One visited map for each ocean
        boolean[][] pacific = new boolean[n][m];
        boolean[][] atlantic = new boolean[n][m];

		Queue<int[]> pQueue = new LinkedList<>();
        Queue<int[]> aQueue = new LinkedList<>();
        for(int i=0; i<n; i++){ //left-right border
            pQueue.offer(new int[]{i, 0});
            aQueue.offer(new int[]{i, m-1});
			//matrix indicates that ocean water is reachable to borders
            pacific[i][0] = true;
            atlantic[i][m-1] = true;
        }
        for(int i=0; i<m; i++){ //top-downborder
            pQueue.offer(new int[]{0, i});
            aQueue.offer(new int[]{n-1, i});
            pacific[0][i] = true;
            atlantic[n-1][i] = true;
        }
        bfs(matrix, pQueue, pacific);
        bfs(matrix, aQueue, atlantic);
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(pacific[i][j] && atlantic[i][j])
                    res.add(new int[]{i,j});
            }
        }
        return res;
    }

    public void bfs(int[][]matrix, Queue<int[]> queue, boolean[][]visited){
        int n = matrix.length, m = matrix[0].length;
        while(!queue.isEmpty()){
            int[] cur = queue.poll();
            for(int[] d:dir){
                int x = cur[0]+d[0];
                int y = cur[1]+d[1];
                if(x<0 || x>=n || y<0 || y>=m || visited[x][y] || matrix[x][y] < matrix[cur[0]][cur[1]]){
                    continue;
                }
                visited[x][y] = true;
                queue.offer(new int[]{x, y});
            }
        }
    }
}

//######################################### DFS #########################################
public class Solution {
    public List<int[]> pacificAtlantic(int[][] matrix) {
        List<int[]> res = new LinkedList<>();
        if(matrix == null || matrix.length == 0 || matrix[0].length == 0){
            return res;
        }
        int n = matrix.length, m = matrix[0].length;
        boolean[][] pacific = new boolean[n][m];
        boolean[][] atlantic = new boolean[n][m];
        for(int i=0; i<n; i++){
            dfs(matrix, pacific, Integer.MIN_VALUE, i, 0);
            dfs(matrix, atlantic, Integer.MIN_VALUE, i, m-1);
        }
        for(int i=0; i<m; i++){
            dfs(matrix, pacific, Integer.MIN_VALUE, 0, i);
            dfs(matrix, atlantic, Integer.MIN_VALUE, n-1, i);
        }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (pacific[i][j] && atlantic[i][j])
                    res.add(new int[] {i, j});
        return res;
    }

    int[][]dir = new int[][]{{0,1},{0,-1},{1,0},{-1,0}};

    public void dfs(int[][]matrix, boolean[][]visited, int height, int x, int y){
        int n = matrix.length, m = matrix[0].length;
        if(x<0 || x>=n || y<0 || y>=m || visited[x][y] || matrix[x][y] < height)
            return;
        visited[x][y] = true;
        for(int[]d:dir){
            dfs(matrix, visited, matrix[x][y], x+d[0], y+d[1]);
        }
    }
}

//############################################ DFS ############################################
private :
  vector<pair<int, int>> res;
  vector<vector<int>> visited;
  void dfs(vector<vector<int>>& matrix, int x, int y, int pre, int preval){
      if (x < 0 || x >= matrix.size() || y < 0 || y >= matrix[0].size()
              || matrix[x][y] < pre || (visited[x][y] & preval) == preval)
          return;
      visited[x][y] |= preval;
      if (visited[x][y] == 3) res.push_back({x, y});
      dfs(matrix, x + 1, y, matrix[x][y], visited[x][y]);
      dfs(matrix, x - 1, y, matrix[x][y], visited[x][y]);
      dfs(matrix, x, y + 1, matrix[x][y], visited[x][y]);
      dfs(matrix, x, y - 1, matrix[x][y], visited[x][y]);
  }
public :
  vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
      if (matrix.empty()) return res;
      int m = matrix.size(), n = matrix[0].size();
      visited.resize(m, vector<int>(n, 0));
      //start with first and last column
      for (int i = 0; i < m; i++) {
          dfs(matrix, i, 0, INT_MIN, 1);
          dfs(matrix, i, n - 1, INT_MIN, 2);
      }
      //start with first and last row
      for (int i = 0; i < n; i++) {
          dfs(matrix, 0, i, INT_MIN, 1);
          dfs(matrix, m - 1, i, INT_MIN, 2);
      }
      return res;
  }
//######################### DFS with stack  #########################
vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
    vector<pair<int, int> > ret;
    stack <pair<int, int> > s1;
    stack <pair<int, int> > s2;
    vector <vector<int> > intermidiate;
    int hSize, vSize;
    vSize = matrix.size();
    if (vSize)
    {
      hSize = matrix[0].size();
      if (hSize)
      {
        intermidiate.resize(vSize, vector<int>(hSize, 0));
        for (int index = 0; index < vSize; index++)
        {
          s1.push(pair<int, int>(index, 0));
          s2.push(pair<int, int>(1, INT_MIN));
          s1.push(pair<int, int>(index, hSize - 1));
          s2.push(pair<int, int>(2, INT_MIN));
        }
        for (int index = 0; index < hSize; index++)
        {
          s1.push(pair<int, int>(0, index));
          s2.push(pair<int, int>(1, INT_MIN));
          s1.push(pair<int, int>(vSize - 1, index));
          s2.push(pair<int, int>(2, INT_MIN));
        }
        while (!s1.empty())
        {
          pair<int, int> pos = s1.top(), meta = s2.top();
          int vPos = pos.first, hPos = pos.second, previousValue = meta.second, flag = meta.first;
          s1.pop();
          s2.pop();
          if (vPos >= 0 && vPos < vSize && hPos >= 0 && hPos < hSize && matrix[vPos][hPos] >= previousValue &&
              (intermidiate[vPos][hPos]&flag) == 0)
          {
            intermidiate[vPos][hPos] = intermidiate[vPos][hPos] | flag;
            if (intermidiate[vPos][hPos] == 3)
            {
              cout << vPos << ' ' << hPos << endl;
              ret.push_back(pos);
            }
            s1.push(pair<int, int>(vPos - 1, hPos));
            s2.push(pair<int, int>(flag, matrix[vPos][hPos]));
            s1.push(pair<int, int>(vPos + 1, hPos));
            s2.push(pair<int, int>(flag, matrix[vPos][hPos]));
            s1.push(pair<int, int>(vPos, hPos - 1));
            s2.push(pair<int, int>(flag, matrix[vPos][hPos]));
            s1.push(pair<int, int>(vPos, hPos + 1));
            s2.push(pair<int, int>(flag, matrix[vPos][hPos]));
          }
        }
      }
    }
    return ret;
  }


//################################ BFS S : O(2n),T : ####################################
struct Node {
  int x, y;
  Node(){}
  Node(int xx, int yy): x(xx), y(yy){}
};
vector<int> dx = {-1, 0, 1, 0};
vector<int> dy = {0, 1, 0, -1};
class Solution {
public:
    int n, m;
    bool bound(int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < m;
    }
    void bfs(vector<vector<int>>& matrix, vector<vector<bool>> &vis, queue<Node> &q) {
        while(!q.empty()) {
            Node now = q.front();
            q.pop();
            for(int k = 0; k < 4; k++) { //iterave up,down,left and right
                int nx = now.x + dx[k], ny = now.y + dy[k];
                if(bound(nx, ny) && !vis[nx][ny]) {
                    if(matrix[nx][ny] >= matrix[now.x][now.y]) {
                        vis[nx][ny] = true;
                        q.push(Node(nx, ny));
                    }
                }
            }
        }
    }
    vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
        vector<pair<int, int>> ans;
        n = matrix.size();
        if(n == 0) return ans; //n : rows,m : cols
        m = matrix[0].size();
        queue<Node> q; // store the co-ordinates that are adjacent to either pacific/atlantic
        vector<vector<bool>> p(n, vector<bool>(m, 0)); //p : pacific , a : atlantic
        for(int i = 0; i < n; i++) {
            q.push(Node(i, 0));
            p[i][0] = true;
        }
        for(int j = 0; j < m; j++) {
            q.push(Node(0, j));
            p[0][j] = true;
        }
        bfs(matrix, p, q);
        while(!q.empty())
          q.pop();
        vector<vector<bool>> a(n, vector<bool>(m, 0));
        for(int i = 0; i < n; i++) {
            q.push(Node(i, m-1));
            a[i][m-1] = true;
        }
        for(int j = 0; j < m; j++) {
            q.push(Node(n-1, j));
            a[n-1][j] = true;
        }
        bfs(matrix, a, q);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(p[i][j] && a[i][j])
                    ans.push_back(make_pair(i, j));
            }
        }
        return ans;
    }
};

//###################################### BFS ##########################################
//Optimization : you can actually use just one visited and make it "+1" as pac,
//"+2" as atl. Then finally check whether the cell is 3. That saves some space
//(but very minor though)
class Solution {
public:
    void flow(int i, int j, vector<vector<int>>& map, vector<vector<int>>& visit) {
        if(visit[i][j]==1) return;
        queue<pair<int,int>> q;
        q.push({i,j});
        int m = map.size();
        int n = map[0].size();
        while(!q.empty()) {
            auto p = q.front();
            q.pop();
            int x = p.first;
            int y = p.second;
            if(visit[x][y] == 1) continue;
            visit[x][y] = 1;
            if(x>0 && map[x-1][y]>=map[x][y]) q.push({x-1,y});
            if(y>0 && map[x][y-1]>=map[x][y]) q.push({x,y-1});
            if(x<m-1 && map[x+1][y]>=map[x][y]) q.push({x+1,y});
            if(y<n-1 && map[x][y+1]>=map[x][y]) q.push({x,y+1});
        }
    }
    vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if(m==0) return {};
        int n = matrix[0].size();
        if(n==0) return {};
        vector<vector<int>> pac(m,vector<int>(n,0));
        vector<vector<int>> atl(m,vector<int>(n,0));
        vector<pair<int,int>> ans;

        for(int i=0;i<m;i++) {
            flow(i,0,matrix,pac);
            flow(i,n-1,matrix,atl);
        }

        for(int i=0;i<n;i++) {
            flow(0,i,matrix,pac);
            flow(m-1,i,matrix,atl);
        }

        for(int i=0;i<m;i++) {
            for(int j=0;j<n;j++) {
                if(pac[i][j]==1 && atl[i][j]==1) ans.push_back({i,j});
            }
        }

        return ans;
    }
};

//####################################### pytonic  #######################################
//class Solution(object):
//    def __init__(self):
//        self.res = []       # Stores the valid positions.
//        self.visited = []   # Stores the status, (1 = reachable to Pac, 2 = Atl, 3 = both)
//
//    def pacificAtlantic(self, matrix):
//        if not matrix or not matrix[0]: return self.res
//        height, width = len(matrix), len(matrix[0])
//        self.visited = [[0 for _ in xrange(width)] for _ in xrange(height)]
//        for i in xrange(height):
//            self.dfs(matrix, i, 0, float('-inf'), 1)
//            self.dfs(matrix, i, width - 1, float('-inf'), 2)
//        for j in xrange(width):
//            self.dfs(matrix, 0, j, float('-inf'), 1)
//            self.dfs(matrix, height - 1, j, float('-inf'), 2)
//        return self.res;
//
//    def dfs(self, mat, x, y, preh, prev):
//        # preh: height of previous position
//        # prev: visit status of previous position
//        # dfs stop when: out of boundary / current position is higher / two position has the same status
//        if x < 0 or x >= len(mat) or y < 0 or y >= len(mat[0]) or mat[x][y] < preh or (self.visited[x][y]&prev) == prev:
//            return
//        self.visited[x][y] |= prev     # we can see here case c will be simply useless.
//        if (self.visited[x][y] == 3): self.res += [x, y],
//        self.dfs(mat, x + 1, y, mat[x][y], self.visited[x][y])  # seek all four direction
//        self.dfs(mat, x - 1, y, mat[x][y], self.visited[x][y])
//        self.dfs(mat, x, y + 1, mat[x][y], self.visited[x][y])
//        self.dfs(mat, x, y - 1, mat[x][y], self.visited[x][y])
//

//####################################### pytonic  + like longest increasing sequence #######################################

//1. init a directions var like self.directions = [(1,0),(-1,0),(0,1),(0,-1)]
//so that when you want to explore from a node, you can just do
//for direction in self.directions:
//            x, y = i + direction[0], j + direction[1]
//
//2. this is a what I normally do for a dfs helper method for exploring a
//matrix
//def dfs(self, i, j, matrix, visited, m, n):
//  if visited:
//    # return or return a value
//  for dir in self.directions:
//    x, y = i + direction[0], j + direction[1]
//        if x < 0 or x >= m or y < 0 or y >= n or matrix[x][y] <= matrix[i][j] (or a condition you want to skip this round):
//           continue
//        # do something like
//        visited[i][j] = True
//        # explore the next level like
//        self.dfs(x, y, matrix, visited, m, n)
//
//class Solution(object):
//    def pacificAtlantic(self, matrix):
//        """
//        :type matrix: List[List[int]]
//        :rtype: List[List[int]]
//        """
//        if not matrix: return []
//        self.directions = [(1,0),(-1,0),(0,1),(0,-1)]
//        m = len(matrix)
//        n = len(matrix[0])
//        p_visited = [[False for _ in range(n)] for _ in range(m)]
//
//        a_visited = [[False for _ in range(n)] for _ in range(m)]
//        result = []
//
//        for i in range(m):
//            # p_visited[i][0] = True
//            # a_visited[i][n-1] = True
//            self.dfs(matrix, i, 0, p_visited, m, n)
//            self.dfs(matrix, i, n-1, a_visited, m, n)
//        for j in range(n):
//            # p_visited[0][j] = True
//            # a_visited[m-1][j] = True
//            self.dfs(matrix, 0, j, p_visited, m, n)
//            self.dfs(matrix, m-1, j, a_visited, m, n)
//
//        for i in range(m):
//            for j in range(n):
//                if p_visited[i][j] and a_visited[i][j]:
//                    result.append([i,j])
//        return result
//
//
//    def dfs(self, matrix, i, j, visited, m, n):
//        # when dfs called, meaning its caller already verified this point
//        visited[i][j] = True
//        for dir in self.directions:
//            x, y = i + dir[0], j + dir[1]
//            if x < 0 or x >= m or y < 0 or y >= n or visited[x][y] or matrix[x][y] < matrix[i][j]:
//                continue
//            self.dfs(matrix, x, y, visited, m, n)
//# 113 / 113 test cases passed.
//# Runtime: 196 ms
//
//
//###################### longest increasing path in matrix ######################
//class Solution(object):
//    def longestIncreasingPath(self, matrix):
//        """
//        :type matrix: List[List[int]]
//        :rtype: int
//        """
//        if not matrix: return 0
//        self.directions = [(1,0),(-1,0),(0,1),(0,-1)]
//        m = len(matrix)
//        n = len(matrix[0])
//        cache = [[-1 for _ in range(n)] for _ in range(m)]
//        res = 0
//        for i in range(m):
//            for j in range(n):
//                cur_len = self.dfs(i, j, matrix, cache, m, n)
//                res = max(res, cur_len)
//        return res
//
//    def dfs(self, i, j, matrix, cache, m, n):
//        if cache[i][j] != -1:
//            return cache[i][j]
//        res = 1
//        for direction in self.directions:
//            x, y = i + direction[0], j + direction[1]
//            if x < 0 or x >= m or y < 0 or y >= n or matrix[x][y] <= matrix[i][j]:
//                continue
//            length = 1 + self.dfs(x, y, matrix, cache, m, n)
//            res = max(length, res)
//        cache[i][j] = res
//        return res
//################# pytonic complex numbers #################
//
//moves = [1, -1, 1j, -1j]
//def pacificAtlantic(self, matrix):
//	m, n = len(matrix), len(zip(*matrix))
//	def bfs(matrix):
//		maps = {x + y*1j: matrix[x][y] for x in xrange(m) for y in xrange(n)}
//		visited = {x for x in xrange(m)} | {y * 1j for y in xrange(n)}
//		layer = set(visited)
//		while layer:
//			layer = {pos+mov    for pos in layer
//			                    for mov in moves
//						if	pos+mov in maps          and
//							pos+mov not in visited   and
//							maps[pos+mov] >= maps[pos]}
//			visited |= layer
//		return visited
//	points = bfs(matrix) & {m-1+n*1j-1j-pos for pos in bfs([row[::-1] for row in matrix[::-1]])}
//	return [[p.real, p.imag] for p in points]

//#################################### bit mask ####################################
//class Solution(object):
//    def pacificAtlantic(self, matrix):
//        """
//        :type matrix: List[List[int]]
//        :rtype: List[List[int]]
//        """
//        if not matrix:
//            return matrix
//        self.searchPath = [[0,1],[0,-1],[1,0],[-1,0]]
//        m = len(matrix)
//        n = len(matrix[0])
//        res = [[0 for _ in range(n)] for _ in range(m)] #Mask = 01, Top-left(Pacific), Mask = 10, Bottom-right(Atlantic), res[i][j] = 11
//        ans = []
//        for i in range(m):
//            self.dfs(matrix, res, i,  0, 1)
//            self.dfs(matrix, res, i, n-1, 2)
//        for i in range(n):
//            self.dfs(matrix, res, 0, i, 1)
//            self.dfs(matrix, res, m-1, i, 2)
//        for i in range(m):
//            for j in range(n):
//                if res[i][j] == 3:
//                    ans.append([i,j])
//        return ans
//
//    def dfs(self, matrix, res, i, j, mask):
//        res[i][j] = res[i][j]|mask
//        for p in self.searchPath:
//            x = i + p[0]
//            y = j + p[1]
//            if x >= 0 and x < len(matrix) and y>=0 and y < len(matrix[0]) and res[x][y]&mask == 0 and matrix[i][j]<=matrix[x][y]:
//                self.dfs(matrix, res, x, y, mask)
