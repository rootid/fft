//Shortest Distance from All Buildings
//You want to build a house on an empty land which reaches all buildings in the
//shortest amount of distance. You can only move up, down, left and right. You
//are given a 2D grid of values 0, 1 or 2, where:
//Each 0 marks an empty land which you can pass by freely.
//Each 1 marks a building which you cannot pass through.
//Each 2 marks an obstacle which you cannot pass through.
//For example, given three buildings at (0,0), (0,4), (2,2), and an obstacle at
//(0,2):
//1 - 0 - 2 - 0 - 1
//|   |   |   |   |
//0 - 0 - 0 - 0 - 0
//|   |   |   |   |
//0 - 0 - 1 - 0 - 0
//The point (1,2) is an ideal empty land to build a house, as the total travel
//distance of 3+3+1=7 is minimal. So return 7.
//Note:
//There will be at least one building. If it is not possible to build such
//house according to the above rules, return -1
//
#include "../headers/global.hpp"

int shortestDistance(vector<vector<int>> grid) {
         if (grid.size()==0 || grid[0].size()== 0) {
           return -1;
         }
         int m = grid.size();
         int n = grid[0].size();
         int houseNum = 0;
         const vector<int> dirs( { 0, 1, 0, -1, 0} );
         vector<vector<int> > dist(m, vector<int>(n));
         vector<vector<int> > reach(m, vector<int>(n));
         for (int i=0; i<m; i++) {
             for (int j=0; j<n; j++) {
                 if (grid[i][j] == 1) {
                     houseNum++;
                     int level = 0;
                     vector<vector<bool> > visited(m, vector<bool>(n));
                     queue<int> bfs_q;
                     bfs_q.push(i*n+j);
                     visited[i][j] = true;
                     while (!bfs_q.empty()) {
                         int size = bfs_q.size();
                         for (int t=0; t<size; t++) {
                             int cur = bfs_q.front();
                             bfs_q.pop();
                             int x = cur/n;
                             int y = cur%n;
                             for (int i=0;i<4;++i) {
                                 int xnew = x + dirs[i];
                                 int ynew = y + dirs[i+1];
                                 if (xnew>=0 && xnew<m && ynew>=0 && ynew<n
                                     && !visited[xnew][ynew] && grid[xnew][ynew]==0) {
                                     bfs_q.push(xnew*n+ynew);
                                     visited[xnew][ynew] = true;
                                     dist[xnew][ynew] += level+1;
                                     reach[xnew][ynew]++;
                                 }
                             }
                         }
                         level++;
                     }
                 }
             }
         }

         int minDist = INT_MAX;
         for (int i=0; i<m; i++) {
             for (int j=0; j<n; j++) {
                 if (grid[i][j]==0 && reach[i][j] == houseNum) {
                     minDist = min(minDist, dist[i][j]);
                 }
             }
         }
         return minDist == INT_MAX ? -1 : minDist;
}

int main() {
}
