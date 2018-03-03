//Maximum Distance in Arrays
//Given m arrays, and each array is sorted in ascending order. Now you can pick up two integers from two different
//arrays (each array picks one) and calculate the distance. We define the distance between two integers a and b to be
//their absolute difference |a-b|. Your task is to find the maximum distance.
//
//Example 1:
//Input:
//[[1,2,3],
// [4,5],
// [1,2,3]]
//Output: 4
//Explanation:
//One way to reach the maximum distance 4 is to pick 1 in the first or third array and pick 5 in the second array.
//Note:
//Each given array will have at least 1 number. There will be at least two non-empty arrays.
//The total number of the integers in all the m arrays will be in the range of [2, 10000].
//The integers in the m arrays will be in the range of [-10000, 10000].
//

//###################################### traversal ###########################################
int maxDistance(vector<vector<int>>& arrays) {
  int maxDif = 0, curMin = 10000, curMax = -10000;
  for (auto& a : arrays) {
      maxDif = max(maxDif, max(a.back()-curMin, curMax-a.front()));
      curMin = min(curMin, a.front());
      curMax = max(curMax, a.back());
  }
  return maxDif;
}

//###################################### bad ###########################################
int maxDistance(vector<vector<int>>& aa) {
    int minid = 0;
    int maxid = 0;
    for (int i = 0; i < aa.size(); i++) {
        minid = aa[minid].front() <= aa[i].front() ? minid : i;
        maxid = aa[maxid].back() >= aa[i].back() ? maxid : i;
    }
    if (minid != maxid) {
        return aa[maxid].back() - aa[minid].front();
    }

    int maxdist = INT_MIN;
    for (int i = 0; i < aa.size(); i++) {
        if (i != minid) {
            maxdist = max(maxdist, aa[i].back() - aa[minid].front());
            maxdist = max(maxdist, aa[maxid].back() - aa[i].front());
        }
    }
    return maxdist;
}


//###################################### pytonic ###########################################
//def maxDistance(self, arrays):
//  res, curMin, curMax = 0, 10000, -10000
//  for a in arrays :
//      res = max(res, max(a[-1]-curMin, curMax-a[0]))
//      curMin = min(curMin, a[0])
//      curMax = max(curMax, a[-1])
//    return res
//
//
//MAX and MIN from the head and the tail. Remember keep track of the index of MAX and MIN since the two numbers can NOT
//be in the same array.
//class Solution(object):
//    def maxDistance(self, arrays):
//        """
//        :type arrays: List[List[int]]
//        :rtype: int
//        """
//        m = len(arrays)
//        MAX, max_i = max([(arrays[i][-1], i) for i in range(m)])
//        MIN, min_i = min([(arrays[i][0], i) for i in range(m)])
//        a = max(abs(arrays[i][0] - MAX) for i in range(m) if i != max_i)
//        b = max(abs(arrays[i][-1] - MIN) for i in range(m) if i != min_i)
//        return max(a, b)
//
//
//
// vim: set sw=2 sts=2 tw=120 et nospell :
