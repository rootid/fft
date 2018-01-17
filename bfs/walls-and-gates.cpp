//You are given a m x n 2D grid initialized with these three possible values.
//-1 - A wall or an obstacle.
//0 - A gate.
//INF - Infinity means an empty room. We use the value 231 - 1 = 2147483647 to represent INF as you may assume that the distance to a gate is less than 2147483647.
//Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.
//For example, given the 2D grid:
//INF  -1  0  INF
//INF INF INF  -1
//INF  -1 INF  -1
//  0  -1 INF INF
//After running your function, the 2D grid should be:
//  3  -1   0   1
//  2   2   1  -1
//  1  -1   2  -1
//  0  -1   3   4
#include "../headers/global.hpp"


//######################################### BFS ######################################### 
public static final int[] d = {0, 1, 0, -1, 0};
public void wallsAndGates(int[][] rooms) {
    if (rooms.length == 0) return;
    int m = rooms.length, n = rooms[0].length;

    Deque<Integer> queue = new ArrayDeque<>();
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (rooms[i][j] == 0) queue.offer(i * n + j); // Put gates in the queue

    while (!queue.isEmpty()) {
        int x = queue.poll();
        int i = x / n, j = x % n;
        for (int k = 0; k < 4; ++k) {
            int p = i + d[k], q = j + d[k + 1]; // empty room
            if (0 <= p && p < m && 0 <= q && q < n && rooms[p][q] == Integer.MAX_VALUE) {
                rooms[p][q] = rooms[i][j] + 1;
                queue.offer(p * n + q);
            }
        }
    }
}

//######################################### Naive BFS ######################################### 
//Naive BFS : Find/update all paths when gate is found

public static final int[] d = {0, 1, 0, -1, 0};

public void wallsAndGates(int[][] rooms) {
    if (rooms.length == 0) return;
    for (int i = 0; i < rooms.length; ++i)
        for (int j = 0; j < rooms[0].length; ++j)
            if (rooms[i][j] == 0) bfs(rooms, i, j); 
}

private void bfs(int[][] rooms, int i, int j) {
    int m = rooms.length, n = rooms[0].length;
    Deque<Integer> queue = new ArrayDeque<>();
    queue.offer(i * n + j); // Put gate in the queue
    while (!queue.isEmpty()) {
        int x = queue.poll();
        i = x / n; j = x % n;
        for (int k = 0; k < 4; ++k) {
            int p = i + d[k], q = j + d[k + 1];
            if (0 <= p && p < m && 0 <= q && q < n && rooms[p][q] > rooms[i][j] + 1) {
                rooms[p][q] = rooms[i][j] + 1;
                queue.offer(p * n + q);
            }
        }
    }
}

//######################################### Naive BFS ######################################### 
void wallsAndGates(vector<vector<int>>& rooms) {
    const int row = rooms.size();
    if (row  == 0) return;
    const int col = rooms[0].size();
    queue<int> canReach;  // save all element reachable
    vector<pair<int, int>> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; // four directions for each reachable
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            if(0 == rooms[i][j])
                canReach.push(i*col + j); 
        }
    }
    while(!canReach.empty()){
      int pos = canReach.front(); 
      int r = pos/col, c = pos%col;
      cout << "r "  << r << " c " << c << endl; 
      canReach.pop();
      for (auto dir : dirs) {
          int x = r + dir.first,  y = c + dir.second;
          if (x < 0 || y < 0 || x >= row || y >= col || rooms[x][y] <= rooms[r][c]+1) 
            continue;
          rooms[x][y] = rooms[r][c] + 1;
          canReach.push(x*col + y);
      }
    }
}

//######################################### DFS -1 ######################################### 
class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        for (int i = 0; i < rooms.size(); ++i) {
            for (int j = 0; j < rooms[i].size(); ++j) {
                if (rooms[i][j] == 0) {
                    dfs(rooms, i + 1, j, 1);
                    dfs(rooms, i - 1, j, 1);
                    dfs(rooms, i, j + 1, 1);
                    dfs(rooms, i, j - 1, 1);
                }
            }
        }
    }
    void dfs(vector<vector<int>> &rooms, int i, int j, int val) {
        if (i < 0 || i >= rooms.size() || j < 0 || j >= rooms[i].size()) return;
        if (rooms[i][j] > val) {
            rooms[i][j] = val;
            dfs(rooms, i + 1, j, val + 1);
            dfs(rooms, i - 1, j, val + 1);
            dfs(rooms, i, j + 1, val + 1);
            dfs(rooms, i, j - 1, val + 1);
        }
    }
};


//######################################### DFS-2 ######################################### 
class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        for (int i = 0; i < rooms.size(); ++i) {
            for (int j = 0; j < rooms[i].size(); ++j) {
                if (rooms[i][j] == 0) {
                    dfs(rooms, i, j, 0);
                }
            }
        }
    }
    void dfs(vector<vector<int>> &rooms, int i, int j, int val) {
        if (i < 0 || i >= rooms.size() || j < 0 || j >= rooms[i].size() || rooms[i][j] < val) return;
        rooms[i][j] = val;
        dfs(rooms, i + 1, j, val + 1);
        dfs(rooms, i - 1, j, val + 1);
        dfs(rooms, i, j + 1, val + 1);
        dfs(rooms, i, j - 1, val + 1);
    }
};



int main() {
    
  pair<int,int> co_ord = pair<int,int> ( {0,7} );
  int row = co_ord.first + 1;
  int col = co_ord.second + 1;
  for(int i= 0 ;i<row;i++) {
    for(int j= 0 ;j<col;j++) {
      int cnt = i*col + j;
      cout  << "cnt = " << cnt << " (" << cnt/col  << "," << cnt%col << ")" << endl;
    }
  }
}

