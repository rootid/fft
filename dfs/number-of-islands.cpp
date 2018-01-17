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

//#################### Union Find  ######################################
//convert 2-D points to 1-D

class Solution {
    int[][] distance = {{1,0},{-1,0},{0,1},{0,-1}};
    public int numIslands(char[][] grid) {  
        if (grid == null || grid.length == 0 || grid[0].length == 0)  {
            return 0;  
        }
        UnionFind uf = new UnionFind(grid);  
        int rows = grid.length;  
        int cols = grid[0].length;  
        for (int i = 0; i < rows; i++) {  
            for (int j = 0; j < cols; j++) {  
                if (grid[i][j] == '1') {  
                    for (int[] d : distance) {
                        int x = i + d[0];
                        int y = j + d[1];
                        if (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == '1') {  
                            int id1 = i*cols+j; //convert 2-D points to 1-D
                            int id2 = x*cols+y;
                            uf.union(id1, id2);  
                        }  
                    }  
                }  
            }  
        }  
        return uf.count;  
    }
}

class UnionFind {
        int[] father;  
        int m, n;
        int count = 0;
        UnionFind(char[][] grid) {  
            m = grid.length;  
            n = grid[0].length;  
            father = new int[m*n]; //Convert 2D array to 1D
            for (int i = 0; i < m; i++) {  
                for (int j = 0; j < n; j++) {  
                    if (grid[i][j] == '1') {
                        int id = i * n + j;
                        father[id] = id;
                        count++;
                    }
                }  
            }  
        }
        public void union(int node1, int node2) {  
            int find1 = find(node1);
            int find2 = find(node2);
            if(find1 != find2) {
                father[find1] = find2;
                count--;
            }
        }
        public int find (int node) {  
            if (father[node] == node) {  
                return node;
            }
            father[node] = find(father[node]);  
            return father[node];
        }
    }

//#################### DFS ######################################
class Solution {
    public int numIslands(char[][] grid) {
        int m = grid.length;
        if(m <= 0) return 0;
        int n = grid[0].length;
        if(n <= 0) return 0;
        int cnt = 0;
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
                if(grid[i][j] == '1') {
                    dfs(grid,i,j);
                    cnt++;
                }
        return cnt;
    }
    
    private void dfs(char grid[][],int i,int j) {
        int[] dirs = {0,1,0,-1,0};
        int m = grid.length;
        int n = grid[0].length;
        if(grid[i][j] == '1') {
            grid[i][j] = '0';
            for(int l=0;l<dirs.length-1;l++) {
                int dx = i+ dirs[l];
                int dy = j + dirs[l+1];
                if(dx < m && dy < n && dx >=0 && dy >=0) dfs(grid,dx,dy);
            }   
        }
    }
}

//#################### DFS  ######################################3
int numIslands(vector<vector<char>> &grid) {
     int m = grid.size();
     if (m==0) return 0;
     int n = grid[0].size();
     int count = 0;
     for (int i = 0; i < m; ++i) {
         for (int j = 0; j < n; ++j) {
             if (grid[i][j]=='1') {
                 helper(grid,i,j,m,n);
                 count++;
             }
         }
     }
     return count;
 }

void helper(vector<vector<char> >& a, int i, int j, int m, int n) {
     a[i][j] = 0;
     if (i > 0 && a[i-1][j]=='1') helper(a,i-1,j,m,n);
     if (j > 0 && a[i][j-1]=='1') helper(a,i,j-1,m,n);
     if (i < m-1 && a[i+1][j]=='1') helper(a,i+1,j,m,n);
     if (j < n-1 && a[i][j+1]=='1') helper(a,i,j+1,m,n);
}

//#################### Ugly ######################################3
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

