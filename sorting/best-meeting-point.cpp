//Best Meeting Point
//A group of two or more people wants to meet and minimize the total travel
//distance. You are given a 2D grid of values 0 or 1, where each 1 marks the
//home of someone in the group. The distance is calculated using Manhattan
//Distance, where distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|.
//For example, given three people living at (0,0), (0,4), and (2,2):
//1 - 0 - 0 - 0 - 1
//|   |   |   |   |
//0 - 0 - 0 - 0 - 0
//|   |   |   |   |
//0 - 0 - 1 - 0 - 0
//The point (0,2) is an ideal meeting point, as the total travel distance of
//2+2+2=6 is minimal. So return 6.
//Hint:
//Try to solve it in one dimension first. How can this solution apply to the
//two dimension case?

//######################################### #########################################
//TC : O(nm)
//SC : O(nm)
public int minTotalDistance(int[][] grid) {
    List<Integer> rows = collectRows(grid);
    List<Integer> cols = collectCols(grid);
    return minDistance1D(rows) + minDistance1D(cols);
}

private int minDistance1D(List<Integer> points) {
    int distance = 0;
    int i = 0;
    int j = points.size() - 1;
    while (i < j) {
        distance += points.get(j) - points.get(i);
        i++;
        j--;
    }
    return distance;
}


//######################################### O(mn log(mn)) #########################################
//1 traverse + 2 sorts + 2 traverses = 3mn + 2mn log(mn)
public int minTotalDistance(int[][] grid) {
    int m = grid.length;
    int n = grid[0].length;

    List<Integer> rows = new ArrayList<>(m);
    List<Integer> cols = new ArrayList<>(n);

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(grid[i][j] == 1){
                rows.add(i); //0,0,2 //NOTE : rows are already sorted no need to invoke collections.sort()
                cols.add(j); //0,4,2
            }
        }
    }
    return getMin(rows) + getMin(cols);
}

private int getMin(List<Integer> list){
    int ret = 0;
    Collections.sort(list);
    int i = 0;
    int j = list.size() - 1;
    while(i < j){
        ret += list.get(j--) - list.get(i++);
    }
    return ret;
}

//######################################### O(mn) #########################################
public int minTotalDistance(int[][] grid) {
    int m = grid.length, n = grid[0].length;

    List<Integer> I = new ArrayList<Integer>();
    List<Integer> J = new ArrayList<Integer>();

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                I.add(i);
            }
        }
    }
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i ++) {
            if (grid[i][j] == 1) {
                J.add(j);
            }
        }
    }
    return minTotalDistance(I) + minTotalDistance(J);
}

public int minTotalDistance(List<Integer> grid) {
    int i = 0, j = grid.size() - 1, sum = 0;
    while (i < j) {
        sum += grid.get(j--) - grid.get(i++);
    }
    return sum;
}


//As long as you have different numbers of people on your left and on your
//right, moving a little to the side with more people decreases the sum of
//distances. So to minimize it, you must have equally many people on your left
//and on your right. Same with above/below.
//Two O(mn) solutions, both take 2ms.
//The neat total += Z[hi--] - Z[lo++]-style summing is from larrywang2014's
//solution.
//Originally I used total += abs(Z[i] - median)-style.

//######################################### O(mn) #########################################
//Collect people in sorted order
public int minTotalDistance(int[][] grid) {
    int m = grid.length, n = grid[0].length;
    int total = 0, Z[] = new int[m*n];
    for (int dim=0; dim<2; ++dim) {
        int i = 0, j = 0;
        if (dim == 0) {
            for (int x=0; x<n; ++x)
                for (int y=0; y<m; ++y)
                    if (grid[y][x] == 1)
                        Z[j++] = x;
        } else {
            for (int y=0; y<m; ++y)
                for (int g : grid[y])
                    if (g == 1)
                        Z[j++] = y;
        }
        while (i < --j)
            total += Z[j] - Z[i++];
    }
    return total;
}

//################################################### O(m+n) ###################################################
//BucketSort-ish. Count how many people live in each row and each column. Only
//O(m+n) space.
public int minTotalDistance(int[][] grid) {
    int m = grid.length, n = grid[0].length;
    int[] I = new int[m], J = new int[n];
    for (int i=0; i<m; ++i)
        for (int j=0; j<n; ++j)
            if (grid[i][j] == 1) {
                ++I[i];
                ++J[j];
            }

    int total = 0;
    for (int[] K : new int[][]{ I, J }) {
        int i = 0, j = K.length - 1;
        while (i < j) {
            int k = Math.min(K[i], K[j]);
            total += k * (j - i);
            if ((K[i] -= k) == 0) ++i;
            if ((K[j] -= k) == 0) --j;
        }
    }
    return total;
}


//################################################### python ###################################################
def minTotalDistance(self, grid):
    row_sum = map(sum, grid)
    col_sum = map(sum, zip(*grid)) # syntax sugar learned from stefan :-)

    def minTotalDistance1D(vec):
        i, j = -1, len(vec)
        d = left = right = 0
        while i != j:
            if left < right:
                d += left
                i += 1
                left += vec[i]
            else:
                d += right
                j -= 1
                right += vec[j]
        return d

    return minTotalDistance1D(row_sum) + minTotalDistance1D(col_sum)
