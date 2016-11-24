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

