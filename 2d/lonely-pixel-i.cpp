//Lonely Pixel I
//Given a picture consisting of black and white pixels, find the number of black lonely pixels.
//The picture is represented by a 2D char array consisting of 'B' and 'W', which means black and white pixels respectively.
//A black lonely pixel is character 'B' that located at a specific position where the same row and same column don't have any other black pixels.
//Example:
//Input:
//[['W', 'W', 'B'],
// ['W', 'B', 'W'],
// ['B', 'W', 'W']]
//Output: 3
//Explanation: All the three 'B's are black lonely pixels.
//Note:
//The range of width and height of the input 2D array is [1,500].
//

//["WWWWWWWWWWWWWWWWWWWWWWWWW"
//,"BWBBBBBBBBBBBBBBBBBBBBBWW"]
//o/p : 0


//################################################### T : O(mn), S = O(m+n)  ###################################################
/**
 * suppose matrix is m*n, there is at most min(m, n) lonely pixels, because there could be no more than 1 in each row, or column;
 * therefore, if we record num of black pixel on each row and column, we can easily tell whether each pixel is lonely or NO.
 *     _0_1_2_
 *  0 | 0 0 1   rows[0] = 1
 *  1 | 0 1 0   rows[1] = 1
 *  2 | 1 0 0   rows[2] = 1
 *
 * cols[0][1][2]
 *     1  1  1
 */
class Solution {
public:
    int findLonelyPixel(vector<vector<char>>& pic) {
        int m = pic.size();
        int n = pic[0].size();
        vector<int> rows = vector<int>(m, 0);
        vector<int> cols = vector<int>(n, 0);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                rows[i] += pic[i][j] == 'B';
                cols[j] += pic[i][j] == 'B';
            }
        }
        int lonely = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n && rows[i] > 0; j++) {
                lonely += pic[i][j] == 'B' && rows[i] == 1 && cols[j] == 1;
            }
        }
        return lonely;
    }
};

//################################################### T : O(mn), S = O(m+n) + One Pass  ###################################################
public class Solution {
    public int findLonelyPixel(char[][] picture) {
        int m = picture.length, n = picture[0].length;
        int[] row = new int[m];
        int[] col = new int[n];
        int res = 0;
        for(int i = 0; i < m; i ++) {
            for(int j = 0; j < n; j ++){
                if(picture[i][j] == 'B'){
                    col[j]++;
                    if(row[i] == 0) {
						row[i] = j + 1;
					} else {
						row[i] = -1;
					}
                }
            }
        }
        for(int r : row){
            if(r > 0 && col[r - 1] == 1) res++;
        }
        return res;
    }
}

//################################################### T : O(mn), S = O(1)  ###################################################
//mutate the first row and first column of the given matrix to store the counts of items in the row/column.
//W + 1 = X --> one item in the row/column
//B + 1 = C --> one item in the row/column, and the first row is the black pixel
//W + 2 = Y --> two items in the row/column
//W - 1 = V --> this prevents wrap-around past W if there are more than 255 black pixels in a row/column

public int findLonelyPixel(char[][] picture) {
    int n = picture.length, m = picture[0].length;


    int firstRowCount = 0;
    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++)
            if (picture[i][j] == 'B') {
                if (picture[0][j] < 'Y' && picture[0][j] != 'V') picture[0][j]++;
                if (i == 0) firstRowCount++;
                else if (picture[i][0] < 'Y' && picture[i][0] != 'V') picture[i][0]++;
            }

    int count = 0;
    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++)
            if (picture[i][j] < 'W' && (picture[0][j] == 'C' || picture[0][j] == 'X')) {
                if (i == 0) count += firstRowCount == 1 ? 1 : 0;
                else if (picture[i][0] == 'C' || picture[i][0] == 'X') count++;
            }

    return count;
}

//################################################### JAVA ###################################################
public class Solution {
    public int findLonelyPixel(char[][] pic) {
        int m = pic.length;
        int n = pic[0].length;
        int[] rows = new int[m];
        int[] cols = new int[n];

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                rows[i] += pic[i][j] == 'B' ? 1 : 0;
                cols[j] += pic[i][j] == 'B' ? 1 : 0;
            }
        }

        int lonely = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n && rows[i] > 0; j++) {
                lonely += (pic[i][j] == 'B' && rows[i] == 1 && cols[j] == 1) ? 1 : 0;
            }
        }

        return lonely;
    }
}

//################################################### Python ###################################################
///################################################### Omn) ###################################################
//go through the columns, count how many have exactly one black pixel and it's in a row that also has exactly one black pixel.
def findLonelyPixel(self, picture):
    return sum(col.count('B') == 1 == picture[col.index('B')].count('B') for col in zip(*picture))

