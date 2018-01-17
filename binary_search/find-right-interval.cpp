//Given a set of intervals, for each of the interval i, check if there exists an interval j whose start point is bigger than or equal to the end point of the interval i, which can be called that j is on the "right" of i.
//For any interval i, you need to store the minimum interval j's index, which means that the interval j has the minimum start point to build the "right" relationship for interval i. If the interval j doesn't exist, store -1 for the interval i. Finally, you need output the stored value of each interval as an array.
//Note:
//You may assume the interval's end point is always bigger than its start point.
//You may assume none of these intervals have the same start point.
//Example 1:
//Input: [ [1,2] ]
//Output: [-1]
//Explanation: There is only one interval in the collection, so it outputs -1.
//Example 2:
//Input: [ [3,4], [2,3], [1,2] ]
//Output: [-1, 0, 1]
//Explanation: There is no satisfied "right" interval for [3,4].
//For [2,3], the interval [3,4] has minimum-"right" start point;
//For [1,2], the interval [2,3] has minimum-"right" start point.
//Example 3:
//Input: [ [1,4], [2,3], [3,4] ]
//Output: [-1, 2, -1]
//Explanation: There is no satisfied "right" interval for [1,4] and [3,4].
//For [2,3], the interval [3,4] has minimum-"right" start point.
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
//############################################# Good ############################################# 
vector<int> findRightInterval(vector<Interval>& intervals) {
    //NOTE : unordered_map does not have lower_bound
    map<int, int> hash;
    vector<int> res;
    int n = intervals.size();
    for (int i = 0; i < n; ++i) {
        hash[intervals[i].start] = i;
    }
    for (auto in : intervals) {
        //Binary search with end
        auto itr = hash.lower_bound(in.end);
        //No eleme found
        if (itr == hash.end()) {
          res.push_back(-1);
        } else {
          res.push_back(itr->second);
        }
    }
    return res;
}


//############################################# Bad ############################################# 
vector<int> findRightInterval(vector<Interval>& intervals) { 
  if(intervals.empty()) return {};
  int n = intervals.size();
  vector<int> res(n);
  unordered_map<int, int> mp;
  for(int i = 0; i < n; ++i) {
    mp[intervals[i].start] = i;
  }
  sort(intervals.begin(), intervals.end(), [](Interval a, Interval b){
      return a.start < b.start || (a.start == b.start && a.end <= b.end);}
  );
  
  for(int i = 0; i < n; ++i) {
      int k = mp[intervals[i].start];// the previous index
      int target = intervals[i].end;
      // binary search:
      if(target <= intervals[n-1].start){
     //Because we have sorted the intervals, so the start point of binary search should be i, no need to search for range [0, i-1].
          int l = i, r = n - 1;
          while(l <= r){
              int m = (l + r)/2;
              if(intervals[m].start < target){l = m + 1;}
              else if(intervals[m].start >= target){r = m - 1;}
          }
          res[k] = mp[intervals[l].start];
      }else{
          res[k] = -1;
      }
  }
  return res;
}

//############################################# Ugly  ############################################# 
vector<int> findRightInterval(vector<Interval>& intervals) {
    vector<int> res(intervals.size(), 0);
    if(intervals.empty()) {
        return res;
    }
    map<int, int> m;
    for(int i=0;i<intervals.size();i++)
        m[intervals[i].start] = i;
    auto f = [](Interval a, Interval b) {
        return (a.start<b.start);
    };
    sort(intervals.begin(), intervals.end(), f);
    for(int i=0;i<intervals.size();i++){
        int right = bifind(intervals, intervals[i].end, 0, intervals.size()-1);
        right<intervals.size()?res[m[intervals[i].start]] = m[intervals[right].start]:res[m[intervals[i].start]] = -1;
    }
    return res;
}
int bifind(vector<Interval>& intervals, int val, int l, int r){
    if(val>intervals[r].start)
        return r+1;
    else if(val==intervals[r].start)
        return r;
    else if(val<=intervals[l].start)
        return l;
    if(l==r)
        return l;
    int mid = (l+r)/2;
    if(intervals[mid].start>=val)
        return bifind(intervals, val, l, mid);
    else
        return bifind(intervals, val, mid+1, r);
}
