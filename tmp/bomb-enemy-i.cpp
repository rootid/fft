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
