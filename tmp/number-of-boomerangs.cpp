//Given n points in the plane that are all pairwise distinct, a "boomerang" is a tuple of points (i, j, k) such that the distance between i and j equals the distance between i and k (the order of the tuple matters).
//Find the number of boomerangs. You may assume that n will be at most 500 and coordinates of points are all in the range [-10000, 10000] (inclusive).


int numberOfBoomerangs(vector<pair<int, int>>& points) {
     int len = points.size(), res = 0;
     unordered_map<int, int> m;
     for(auto &p:points) {
       for(auto &q:points) {
           int x = p.first - q.first;
           int y = p.second - q.second;
           m[x * x + y * y]++;
       }
     }
    unordered_map<int, int> :: iterator it;
    for (it = m.begin(); it != m.end(); it++) {
        int tmp = it->second;
        res += tmp * (tmp - 1);
    }
    m.clear();
  }

  return res;
}
