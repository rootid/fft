//Island Perimeter
//You are given a map in form of a two-dimensional integer grid where 1
//represents land and 0 represents water. Grid cells are connected
//horizontally/vertically (not diagonally). The grid is completely surrounded
//by water, and there is exactly one island (i.e., one or more connected land
//cells). The island doesn't have "lakes" (water inside that isn't connected to
//the water around the island). One cell is a square with side length 1. The
//grid is rectangular, width and height don't exceed 100. Determine the
//perimeter of the island.
//Example:
//[[0,1,0,0],
// [1,1,1,0],
// [0,1,0,0],
// [1,1,0,0]]
//Answer: 16
//Explanation: The perimeter is the 16 yellow stripes in the image below:

int islandPerimeter(vector<vector<int> >& grid) {

//         (0,1)
//  (-1,0)        (1,0)
//         (0,-1)
        const vector<int>dirs({0,1,0,-1,0});
        int peri = 0;
        int m = grid.size();
        if(m == 0) {
            return peri;
        }
        int n = grid[0].size();
        for(int i=0;i<m;i++) {
            for(int j=0;j<n;j++) {
                if(grid[i][j] == 1) {
                    peri += 4;
                    int nbr = 0;
                    for(int d=0;d<4;d++) {
                        if(dirs[d] + i >=0 && dirs[d]+ i < m && dirs[d+1] + j >=0 && dirs[d+1]+ j < n ) {
                                if(grid[dirs[d] + i] [dirs[d+1] + j] == 1) {
                                    nbr += 1;
                                }
                        }
                    }
                    peri -= nbr;
                }
            }
        }
        return peri;
}


int main() {

}
