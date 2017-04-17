//Brick Wall
//There is a brick wall in front of you. The wall is rectangular and has several rows of bricks. The bricks have the same height but different width. You want to draw a vertical line from the top to the bottom and cross the least bricks.
//The brick wall is represented by a list of rows. Each row is a list of integers representing the width of each brick in this row from left to right.
//If your line go through the edge of a brick, then the brick is not considered as crossed. You need to find out how to draw the line to cross the least bricks and return the number of crossed bricks.
//You cannot draw a line just along one of the two vertical edges of the wall, in which case the line will obviously cross no bricks.
//Example:
//Input: 
//[[1,2,2,1],
// [3,1,2],
// [1,3,2],
// [2,4],
// [3,1,2],
// [1,3,1,1]]
//Output: 2
//Explanation: 
//Note:
//The width sum of bricks in different rows are the same and won't exceed INT_MAX.
//The number of bricks in each row is in range [1,10,000]. The height of wall is in range [1,10,000]. Total number of bricks of the wall won't exceed 20,000.


//#############################################################################
//The max number of bricks to cross =  the number of rows, whenever we see a edge, the number of crossed bricks reduce by 1. Thus we just need keep track of the location where we see maximum number of edges.
int leastBricks(vector<vector<int>>& wall) {
  int maxCnt = 0;
  unordered_map<int, int> map; 
  for(auto row:wall) {
    int edge = 0;
    for(int i=0;i<row.size() - 1;i++) { //max edges drawn inside single row
      edge += row[i];
      maxCnt = max(maxCnt,++map[edge]);
    }
  }
 return wall.size()-maxCnt;
}

//#############################################################################
int leastBricks(vector<vector<int>>& wall) { 
  int maxCnt = 0;
  unordered_map<int, int> cnt;
  for (auto row : wall) { //1,2,2,1
    int w = 0;
    for (int i = 0; i < row.size() - 1; i++) { //traverse column
      w += row[i];
      maxCnt = max(maxCnt, ++cnt[w]);
    }
  }
  return wall.size() - maxCnt; 
}



   
   
   
   
   
   
   
   
   
   
   
   
   
