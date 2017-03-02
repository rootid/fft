//Trapping Rain Water II
//Given an m x n matrix of positive integers representing the height of each unit cell in a 2D elevation map, compute the volume of water it is able to trap after raining.
//Note:
//Both m and n are less than 110. The height of each unit cell is greater than 0 and is less than 20,000.
//Example:
//Given the following 3x6 height map:
//[
//  [1,4,3,1,3,2],
//  [3,2,1,3,2,4],
//  [2,3,3,2,3,1]
//]
//Return 4.

//####################################################  BFS ####################################################  
//1. Reduce height( Reduce the height untill it converges to empty. start and pick the smallest height)
//2. Update Water volume
int trapRainWater(vector<vector<int>>& heightMap) { 
  
  if(heightMap.empty() || heightMap.front().empty()) {
    return 0;
  }
  
  typedef pair<int,int> cell; //(height,co-ordinate)
  priority_queue<cell, vector<cell>, greater<cell>> q; //greater is used to get the min value
  
  int m = heightMap.size();
  int n = heightMap[0].size();
  vector<int> visited(m*n, false);
  //pick only border vertices 
  for (int i = 0; i < m; ++i)
  for (int j = 0; j < n; ++j) {
      if (i == 0 || i == m-1 || j == 0  || j == n-1) { 
        if (!visited[i*n+j]) {  //Trick : store only 2D vertices in 1D
          q.push(cell(heightMap[i][j], i*n+j)); 
        }
        visited[i*n+j] = true;
      }
  }
  
  int dir[4][2] = {{0,1}, {0, -1}, {1, 0}, {-1, 0}};
  int ans = 0;
  while(!q.empty()) {
      cell c = q.top();
      q.pop();
      int i = c.second/n, j = c.second%n;
      for (int r = 0; r < 4; ++r) {
          int ii = i+dir[r][0], jj = j+dir[r][1];
          if (ii < 0 || ii >= m || jj < 0 || jj >= n || visited[ii*n+jj]) {
              continue;
          }
          ans += max(0, c.first - heightMap[ii][jj]);
          q.push(cell(max(c.first, heightMap[ii][jj]), ii*n+jj)); //update the ht = max(current ht,nbr ht)
          visited[ii*n+jj] = true;
      }
  }
  return ans; 
}


//####################################################  BFS same as above but stores height as a negative ####################################################  
int trapRainWater(vector<vector<int> >& heightMap) { 
  if(heightMap.empty() || heightMap.front().empty()) {
    return 0;
  }
  int n = heightMap.size();
  int m = heightMap[0].size();
  int result = 0;
  vector<vector<bool>> isVisit(n, vector<bool>(m, false));
  
  priority_queue<pair<int, pair<int, int>> > myQueue;
  
  for(int i = 0; i < n; i++) {
      for(int j = 0; j < m; j++) {
          if(i == 0 || i == n-1 || j == 0 || j == m-1) {
              // we push all the boundary points into the myQueue
              isVisit[i][j] = true;
              // push negative height as the priority_queue is a big heap
              myQueue.push(make_pair(-heightMap[i][j], make_pair(i, j)));
          }
      }
  }
  const int go_x[4] = {1, -1, 0, 0};
  const int go_y[4] = {0, 0, 1, -1};
  while(!myQueue.empty()) {
      // We always extract the smallest block and try to extend it to its four neighbors.
      auto temp_front = myQueue.top();
      myQueue.pop();
      int temp_height = -temp_front.first;
      int fx = temp_front.second.first;
      int fy = temp_front.second.second;
      for(int d = 0; d < 4; d++) {
          int tx = fx + go_x[d];
          int ty = fy + go_y[d];
          if(tx < 0 || tx >=n || ty < 0 || ty >= m || isVisit[tx][ty]) continue;
          if(heightMap[tx][ty] < temp_height) {
              // if its neightbour's height is smallest than it, we fill water in it.
              result += (temp_height - heightMap[tx][ty]);
              heightMap[tx][ty] = temp_height;
          }
          isVisit[tx][ty] = true;
          myQueue.push(make_pair(-heightMap[tx][ty], make_pair(tx, ty)));
      }
  }
  return result;
}

int main(void) {
	vector<vector<int> > heightMap;
	int result = 0;
	heightMap = {{1, 4, 3, 1, 3, 2}, {3, 2, 1, 3, 2, 4}, {2, 3, 3, 2, 3, 1}};
	result = trapRainWater(heightMap);
	assert(4 == result);
	cout << "\nPassed All\n";
	return 0;
}
