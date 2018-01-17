//Bomb Enemy
//Given a 2D grid, each cell is either a wall 'W', an enemy 'E' or empty '0' (the number zero), return the maximum enemies you can kill using one bomb.
//The bomb kills all the enemies in the same row and column from the planted point until it hits the wall since the wall is too strong to be destroyed.
//Note that you can only put the bomb at an empty cell.
//Example:
//For the given grid
//0 E 0 0
//E 0 W E
//0 E 0 0
//return 3. (Placing a bomb at (1,1) kills 3 enemies)
//
#include "../headers/global.hpp"

//############################################# Good #################################################################
int maxKilledEnemies(vector<vector<char>>& grid) {
    const int row = grid.size();
    if( row == 0) {
      return row;
    }
    const int col = grid[0].size();
    int mx_enemy_killed = 0;
    int row_hit = 0;
    vector<int> col_hit(col,0);
    for(int i=0;i<row;i++) {
      for(int j=0;j<col;j++) { 
          
          if(!i || grid[i-1][j] == 'W') { //last_row : found wall
             col_hit[j] = 0; 
             for(int k = i; k < row && grid[k][j]!= 'W'; k++) {  //go downwards
                  col_hit[j] +=  grid[k][j] == 'E';  
              }
          }
          
          if(!j || grid[i][j-1] == 'W') {
               row_hit = 0;
               for(int k = j; k < col && grid[i][k]!='W'; k++)  { //go rightwards
                  row_hit += grid[i][k] == 'E';  
               }
          }
          if(grid[i][j] == '0') { 
              mx_enemy_killed = max(mx_enemy_killed, row_hit+col_hit[j]);
          }
      }
    }
    return mx_enemy_killed;
}

//############################################# Bad #################################################################
bool is_wall(int i,int j,vector<vector<char>>& grid) {
  return grid[i][j] == 'W';
}
bool is_enemy(int i,int j,vector<vector<char>>& grid) {
  return grid[i][j] == 'E';
}

int dfs_bomb_enemy(int r,int c,vector<vector<char>>& grid,int row,int col) {
  int mx_enemy_killed = 0;
  vector< pair<int,int> > dirs( { {1,0},{-1,0},{0,1},{0,-1} } );
  for(int i=0;i<dirs.size();i++) {
    int last_r = r;
    int last_c = c;
    while(last_r < row && last_r >= 0 && last_c < col && last_c >= 0) {
        if( is_enemy(last_r,last_c,grid) ) {
          mx_enemy_killed++;
        } else if(is_wall(last_r,last_c,grid) ) {
          break;
        }
        last_r += dirs[i].first;
        last_c += dirs[i].second;
    }
  }
  return mx_enemy_killed;
}

int maxKilledEnemies(vector<vector<char>>& grid) {
  const int row = grid.size();
  if( row == 0) {
    return row;
  }
  const int col = grid[0].size();
  int mx_enemy_killed = 0;
  for(int i=0;i<row;i++) {
    for(int j=0;j<col;j++) { 
      if(grid[i][j] == '0') {
          mx_enemy_killed = max(mx_enemy_killed,dfs_bomb_enemy(i,j,grid,row,col));
      }
    }
  }
  return mx_enemy_killed;
}
