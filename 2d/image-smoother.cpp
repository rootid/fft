//Image Smoother
//Given a 2D integer matrix M representing the gray scale of an image, you need
//to design a smoother to make the gray scale of each cell becomes the average
//gray scale (rounding down) of all the 8 surrounding cells and itself. If a
//cell has less than 8 surrounding cells, then use as many as you can.  Example
//1:
//Input:
//[[1,1,1],
// [1,0,1],
// [1,1,1]]
//Output:
//[[0, 0, 0],
// [0, 0, 0],
// [0, 0, 0]]
//Explanation:
//For the point (0,0), (0,2), (2,0), (2,2): floor(3/4) = floor(0.75) = 0
//For the point (0,1), (1,0), (1,2), (2,1): floor(5/6) = floor(0.83333333) = 0
//For the point (1,1): floor(8/9) = floor(0.88888889) = 0
//Note:
//The value in the given matrix is in the range of [0, 255].
//The length and width of the given matrix are in the range of [1, 150].


//######################################### nbr check  #########################################
//check function to check the boundary and a inner double loop to traverse the 9 potential
//candidates:
public class ImageSmoother {

    public int[][] imageSmoother(int[][] M) {
        if (M == null) return null;
        int rows = M.length;
        if (rows == 0) return new int[0][];
        int cols = M[0].length;

        int result[][] = new int[rows][cols];

        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                int count = 0;
                int sum = 0;
                for (int incR : new int[]{-1, 0, 1}) {
                    for (int incC : new int[]{-1, 0, 1}) {
                        if (isValid(row + incR, col + incC, rows, cols)) {
                            count++;
                            sum += M[row + incR][col + incC];
                        }
                    }
                }
                result[row][col] = sum / count;
            }
        }

        return result;

    }

    private boolean isValid(int x, int y, int rows, int cols) {
        return x >= 0 && x < rows && y >= 0 && y < cols;
    }
}


//###############################  Count 8 nbrs + sum  ###############################
//  (x-1,y-1)| (x-1,y) |(x-1,y+1)
//  (x, y-1) |  {x,y}  |(x-1,y+1)
//  (x+1,y-1)| (x+1,y) |(x+1,y+1)
//
public int[][] imageSmoother(int[][] M) {
        int row = M.length, col = M[0].length;
        int[][] result = new int[row][col];
        for(int i=0;i<row;++i){
            for(int j=0;j<col;++j){
                int total = 0, points = 0;
                     for(int k=i-1;k<i+2;++k){
                         if(k>-1 && k<row){
                             for(int l=j-1;l<j+2;++l){
                                  if (l>-1 && l<col){
                                      total+=M[k][l];
                                      ++points;
                                  }
                              }
                         }
                     }
                result[i][j] = (int) Math.floor(total/(double)points);
            }
        }

        return result;
    }

//###############################  count 8 nbrs + sum  ###############################
class Solution {
    public int[][] imageSmoother(int[][] M) {
        if(M==null||M.length==0) return new int[][];
        int n=M.length;
        int m=M[0].length;
        int res[][]=new int[n][m];

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                res[i][j]=avg(M,i,j,n,m);
            }
        }
        return res;
    }

    public int avg(int[][] M,int x,int y,int n,int m){
        int sum=0;
        int count=0;
        int[] valueAndCount=new int[]{0,0};

        for(int[] co:new int[][]{{x,y},{x,y-1},{x,y+1},{x-1,y},{x+1,y},{x+1,y-1},{x+1,y+1},{x-1,y-1},{x-1,y+1}}){
            valueAndCount=valueAndCount(M,co[0],co[1],n,m);
            sum+=valueAndCount[0];
            count+=valueAndCount[1];
        }
        return sum/count;
    }

    public int[] valueAndCount(int[][] M,int x,int y,int n,int m){
        boolean valid=x>=0&&x<n&&y>=0&&y<m;
        return new int[]{valid?M[x][y]:0,valid?1:0};
    }
}

//######################################### Bits #########################################
//Derived from StefanPochmann's idea in "game of life": the board has ints in [0, 255], hence only
//8-bit is used, we can use the middle 8-bit to store the new state (average value), replace the old
//state with the new state by shifting all values 8 bits to the right.
vector<vector<int>> imageSmoother(vector<vector<int>>& M) {
     int m = M.size(), n = M[0].size();
     if (m == 0 || n == 0) return {{}};
     vector<vector<int>> dirs = {{0,1},{0,-1},{1,0},{-1,0},{-1,-1},{1,1},{-1,1},{1,-1}};
     for (int i = 0; i < m; i++) {
         for (int j = 0; j < n; j++) {
             int sum = M[i][j], cnt = 1;
             for (int k = 0; k < dirs.size(); k++) {
                 int x = i + dirs[k][0], y = j + dirs[k][1];
                 if (x < 0 || x > m - 1 || y < 0 || y > n - 1) continue;
                 sum += (M[x][y] & 0xFF);
                 cnt++;
             }
             M[i][j] |= ((sum / cnt) << 8);
         }
     }
      for (int i = 0; i < m; i++) {
         for (int j = 0; j < n; j++) {
             M[i][j] >>= 8;
         }
      }
     return M;
 }

//############################### Enlarge matrix ###############################
class Solution(object):
    def imageSmoother(self, M):
        """
        :type M: List[List[int]]
        :rtype: List[List[int]]
        """
        N = [[0]*len(M[0]) for i in range(len(M))]
        M.insert(0,[-1]*(len(M[0])+2))
        M.append([-1]*len(M[0]))
        for i in range(1,len(M)-1):
            M[i].insert(0,-1)
            M[i].append(-1)
        for i in range(1,len(M)-1):
            for j in range(1,len(M[0])-1):
                count = 0
                Sum = 0
                for k in range(-1,2):
                    for l in range(-1,2):
                        if M[i+k][j+l] != -1:
                            count += 1
                            Sum += M[i+k][j+l]
                N[i-1][j-1] = int(Sum/count)
        return N
