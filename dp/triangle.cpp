//Triangle
//Given a triangle, find the minimum path sum from top to bottom. Each step you
//may move to adjacent numbers on the row below.
//For example, given the following triangle
//[
//     [2],
//    [3,4],
//   [6,5,7],
//  [4,1,8,3]
//]
//The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
//Note:
//Bonus point if you are able to do this using only O(n) extra space, where n
//is the total number of rows in the triangle.

int minimumTotal(vector<vector<int> > &triangle) {
    for(int i=triangle.size()-2;i>=0;i--) {
            for(int j=0;j<=i;j++) {
                //TAke the minimum value from row below
                triangle[i][j] += min(triangle[i+1][j],triangle[i+1][j+1]);
            }
        }
        return triangle[0][0];
}


//extra space
//minpath[k][i] = min( minpath[k+1][i], minpath[k+1][i+1]) + triangle[k][i];
//For the kth level:
//minpath[i] = min( minpath[i], minpath[i+1]) + triangle[k][i];
int minimumTotal(vector<vector<int> > &triangle) {
    int n = triangle.size();
    vector<int> minlen(triangle.back());
    for (int layer = n-2; layer >= 0; layer--) // For each layer
    {
        for (int i = 0; i <= layer; i++) // Check its every 'node'
        {
            // Find the lesser of its two children, and sum the current value in the triangle with it.
            minlen[i] = min(minlen[i], minlen[i+1]) + triangle[layer][i];
        }
    }
    return minlen[0];
}


//Problemetic top-down approach
int minimumTotal(vector<vector<int> > &triangle) {

    int m = triangle.size();
    int n;
    if (m > 0) {
        n =  triangle[0].size();
    }
    for (int i=1;i<m;i++) {
        for (int j=0;j<triangle[i].size();i++) {
            int ele = triangle[i][j];
            if (triangle[i-1].size() <= j) {
                int up = triangle[i][j] + triangle[i-1][j];
            }
            if (triangle[i-1].size() <= j-1 ) {
                int left_up = triangle[i][j] + triangle[i-1][j-1];
            }
            if (triangle[i-1].size() <= j+1) {
                int right_up = triangle[i][j] + triangle[i-1][j+1];
            }

        }
    }
}


//Given triangle find the minimum value path

//  [2],
//  [3,4],
//  [6,5,7],
//  [4,1,8,3]
//]

int minimumTotal(vector<vector<int> > &triangle) {

    int ht = tri.size();
    int minV = INT_MAX;
    for (int i = ht - 2;i>=0 ;i--) {
        int width = tri[i].size();
        for (int j = 0;j<width;j++) {
            int tmp = min(tri[i][j] + tri[i-1][j],tri[i][j] + tri[i-1][j+1]);
            minV = min(tmp,minV);
        }
    }
    return minV;
}
