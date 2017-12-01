//Given n points in the plane that are all pairwise distinct, a "boomerang" is a tuple of points (i, j, k) such that the distance between i and j equals the distance between i and k (the order of the tuple matters).
//Find the number of boomerangs. You may assume that n will be at most 500 and coordinates of points are all in the range [-10000, 10000] (inclusive).


//######################################### O(n^2) ######################################### 
//Number of permutations of size 2 from n different points is nP2 = n!/(n-2)! = n * (n-1).
public int numberOfBoomerangs(int[][] points) {
     int m = points.length;
     Map<Integer, Integer> map = new HashMap<>();
      int result = 0;
     for(int i=0;i<m;i++) {
         for(int j=0;j<m;j++) {
             if(i == j) continue;
             int dist = getDistance(points[i], points[j]);
             map.put(dist , map.getOrDefault(dist, 0) + 1);
             System.out.println(map.get(dist));
         }
         for(int tmp:map.values()) result += tmp * (tmp - 1);
         map.clear();
         
     } 
     return result;
 }
 
 private int getDistance(int[] a, int[] b) {
     int dx = a[0] - b[0];
     int dy = a[1] - b[1];
     return dx*dx + dy*dy;
 }

//######################################### O(n^2) ######################################### 
int numberOfBoomerangs(vector<pair<int, int>>& points) {
    int res = 0;
    for(auto &p:points) {
        unordered_map<double,int> cntr;
        for(auto &q:points) {
             int a = p.first - q.first;
             int b = p.second - q.second;
             cntr[a*a + b*b]++;
        }
        for(auto& c:cntr) {
            int tmp = c.second;
            res += tmp * (tmp-1);
        }
    }
    return res;
}
