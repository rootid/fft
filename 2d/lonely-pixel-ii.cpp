//Lonely Pixel II
//Given a picture consisting of black and white pixels, and a positive integer N, find the number of
//black pixels located at some specific row R and column C that align with all the following rules:
//Row R and column C both contain exactly N black pixels.
//For all rows that have a black pixel at column C, they should be exactly the same as row R The
//picture is represented by a 2D char array consisting of ‘B’ and ‘W’, which means black and white
//pixels respectively.
//Example:
//Input:
//[['W', 'B', 'W', 'B', 'B', 'W'],
// ['W', 'B', 'W', 'B', 'B', 'W'],
// ['W', 'B', 'W', 'B', 'B', 'W'],
// ['W', 'W', 'B', 'W', 'B', 'W']]
//N = 3
//Output: 6
//Explanation: All the bold 'B' are the black pixels we need (all 'B's at column 1 and 3).
//        0    1    2    3    4    5         column index
//0    [['W', 'B', 'W', 'B', 'B', 'W'],
//1     ['W', 'B', 'W', 'B', 'B', 'W'],
//2     ['W', 'B', 'W', 'B', 'B', 'W'],
//3     ['W', 'W', 'B', 'W', 'B', 'W']]
//row index
//Take 'B' at row R = 0 and column C = 1 as an example:
//Rule 1, row R = 0 and column C = 1 both have exactly N = 3 black pixels.
//Rule 2, the rows have black pixel at column C = 1 are row 0, row 1 and row 2. They are exactly the
//same as row R = 0.
//Note:
//1. The range of width and height of the input 2D array is [1,200].

//######################################### O(mn) + S: O (m+n) + Set #########################################
public class Solution {
    public int findBlackPixel(char[][] pic, int N) {
        int m = pic.length;
        int n = pic[0].length;
        Map<Integer, Set<Integer>> rows = new HashMap<Integer, Set<Integer>>(); // black pixels in each row;
        Map<Integer, Set<Integer>> cols = new HashMap<Integer, Set<Integer>>(); // black pixels in each col;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (pic[i][j] == 'B') {
                    if (!rows.containsKey(i)) { rows.put(i, new HashSet<Integer>()); }
                    if (!cols.containsKey(j)) { cols.put(j, new HashSet<Integer>()); }
                    rows.get(i).add(j);
                    cols.get(j).add(i);
                }
            }
        }
        int lonelys = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n && rows.containsKey(i); j++) {
                if (pic[i][j] == 'B' && rows.get(i).size() == N && cols.containsKey(j) && cols.get(j).size() == N) {   // rule 1 fulfilled
                    int lonely = 1;
                    for (int row : cols.get(j)) { // Set.equals() is an O(n) operation. Use map instead of set
                        if (!rows.get(i).equals(rows.get(row))) {
                            lonely = 0; break;
                        }
                    }
                    lonelys += lonely;
                }
            }
        }
        return lonelys;
    }
}

//######################################### O(mn) + S: O (m+n) + Map #########################################
public int findBlackPixel(char[][] picture, int N) {
        if (picture == null || picture.length == 0 || picture[0].length == 0) return 0;
        int m = picture.length, n = picture[0].length;
        int[] cols = new int[n];
        Map<String, Integer> map = new HashMap<>();

        for (int i = 0; i < m; i++) {
            int count = 0;
            StringBuilder sb = new StringBuilder();
            for (int j = 0; j < n; j++) {
                if (picture[i][j] == 'B') {
                    cols[j]++;
                    count++;
                }
                sb.append(picture[i][j]);
            }
            if (count == N) {
                String curRow = sb.toString();
                map.put(curRow, map.getOrDefault(curRow, 0) + 1);
            }
        }

        int res = 0;
        for (String row : map.keySet()) {
            if (map.get(row) != N) continue;
            for (int i = 0; i < n; i++) {
                if (row.charAt(i) == 'B' && cols[i] == N) {
                    res += N;
                }
            }
        }
        return res;
    }

//######################################### Python #########################################
//Group and count equal rows.
//Look for rows that appear N times and that have N black pixels.
//If you find one, add N for each of its black columns that doesn't have extra black pixels (in
//other rows)
def findBlackPixel(self, picture, N):
    ctr = collections.Counter(map(tuple, picture))
    cols = [col.count('B') for col in zip(*picture)]
    return sum(N * zip(row, cols).count(('B', N))
               for row, count in ctr.items()
               if count == N == row.count('B'))


//######################################### O(mn) + S: O (m+n) #########################################
 int findBlackPixel(vector<vector<char>>& picture, int N) {
	 if(picture.empty()) {
		 return 0;
	 }
     int m = picture.size();
     int n = picture[0].size();
     if(!n) return 0;
     vector<int> rows(m,0), cols(n,0);
     unordered_map<string,int> um;
     vector<string> srows;
     for(int i = 0; i < m; ++i){
         string s;
         for(int j = 0; j < n; ++j){
             if(picture[i][j] == 'B') {
                 rows[i]++;
                 cols[j]++;
             }
             s.push_back(picture[i][j]);
         }
         um[s]++; //WWB
         srows.push_back(s);
     }
     int res = 0;
     for(int i = 0; i < m; ++i) {
         if(rows[i] == N && um[srows[i]] == N) { //count + rows compare
             for(int j = 0; j < n; ++j) {
                  if(picture[i][j] == 'B' && cols[j] == N) ++res;
			 }
		 }
	 }
     return res;
 }

//######################################### O(mn) + S: O (m+n) #########################################
/**
 * Steps:
 * >> 1. create map<int, set<int>> cols, rows; -- to store black dots on that row;
 *	 Store indices of black pixel
 *     _0_1_2_3_4_5_
 *  0 | 0 1 0 1 1 0     rows[0] = {1, 3, 4}
 *  1 | 0 1 0 1 1 0     rows[1] = {1, 3, 4}
 *  2 | 0 1 0 1 1 0     rows[2] = {1, 3, 4}
 *  3 | 0 0 1 0 1 0     rows[3] = {  2,  4}
 *
 * >> 2. for every pixel meet rule 1, that is: pic[i][j] == 'B' && rows[i].size() == N && cols[j].size() == N
 *       check rule2: for every row k in cols[j];  check that row[k] = row[i];
 *
 * We can tell the 6 black pixel in col 1 and col 3 are lonely pixels
 *     _0_1_2_3_4_5_
 *  0 | 0 L 0 L 1 0     rows[0] = {1, 3, 4}  =
 *  1 | 0 L 0 L 1 0     rows[1] = {1, 3, 4}  =
 *  2 | 0 L 0 L 1 0     rows[2] = {1, 3, 4}
 *  3 | 0 0 1 0 1 0     rows[3] = {  2,  4}
 *
 */
class Solution {
public:
    int findBlackPixel(vector<vector<char>>& pic, int N) {
        int m = pic.size();
        int n = pic[0].size();
        unordered_map<int, set<int>> rows;  // black pixels in each row
        unordered_map<int, set<int>> cols;  // black pixels in each col
        /* 1. create map<int, set<int>> cols, rows; -- to store black dots on that row; */
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (pic[i][j] == 'B') {
                    rows[i].insert(j);
                    cols[j].insert(i);
                }
            }
        }
        /* 2. for every pixel meet rule 1: pic[i][j] == 'B' && rows[i].size() == N && cols[j].size() == N */
        int lonelys = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n && rows.count(i); j++) {
                if (pic[i][j] == 'B' && rows[i].size() == N && cols[j].size() == N) {   // rule 1 fulfilled
                    /* check rule2: for every row k in cols[j];  check that row[k] = row[i]; */
                    bool lonely = true;
                    for (int r : cols[j]) {
                        if (rows[r] != rows[i]) {
                            lonely = false; break;
                        }
                    }
                    lonelys += lonely;
                }
            }
        }
        return lonelys;
    }
};


