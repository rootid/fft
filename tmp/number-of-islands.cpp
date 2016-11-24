
//Number of Islands
//Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.
//Example 1:
//11110
//11010
//11000
//00000
//Answer: 1
//Example 2:
//11000
//11000
//00100
//00011
//Answer: 3

int numIslands(vector<vector<char>>& grid) {
    vector<int> to_be_visited;
    int m = grid.size();
    int n;
    int cnt = 0;
    unordered_set<int> visited;
    if(m > 0) {
         n = grid[0].size();
    }
    for(int i=0;i<m;i++) {
        for(int j=0;j<n;j++){
            if(grid[i][j] == '1') {
                to_be_visited.push_back(i+j*m);  //2,3 2+15=17/5 = (5,8)
            }
        }
    }
    for(int i=0;i<to_be_visited.size();i++) {
        
        int v = to_be_visited[i];
        if(visited.find(v) == visited.end()) {
            queue<int> bfsq;
            cnt += 1;
            bfsq.push(v);
            //cout << "INSERTED ELE " << v   << endl;
            while(!bfsq.empty()) {
                int idx = bfsq.front();
                bfsq.pop();
                visited.insert(idx);
                int y = idx / m;
                int x = idx % m;
                //cout << "ADDED ELE " << x << " y = " << y  << endl;
                if( x+1 < m && x+1 >=0 && y < n) {
                    if(grid[x+1][y] == '1' && visited.find( x+1+y*m ) == visited.end()) {
                        bfsq.push(x+1+y*m );
                        visited.insert(x+1+y*m);
                    }
                }
                if(x < m && y-1 < n && y-1 >= 0) {
                     if(grid[x][y-1] == '1' && visited.find(x+ (y-1)*m ) == visited.end() ) {
                         bfsq.push(x+ (y-1)*m );
                         visited.insert(x+ (y-1)*m);
                    }
                }
                if(x-1 >=0 && x-1 < m && y < n) {
                    if(grid[x-1][y] == '1' && visited.find( x-1+y*m ) == visited.end() ) {
                         bfsq.push(x-1+y*m );
                         visited.insert(x-1+y*m);
                    }
                }
                if(x >= 0 && y+1 < n && y+1 >= 0) {
                      if(grid[x][y+1] == '1' && visited.find( x+ (y+1)*m  ) == visited.end()) {
                          bfsq.push(x+ (y+1)*m );
                          visited.insert(x+ (y+1)*m);
                    }
                }
                
            }
            }
    }
    return cnt;
    
    
}
