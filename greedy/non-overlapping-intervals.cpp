//Non-overlapping Intervals
//Given a collection of intervals, find the minimum number of intervals you
//need to remove to make the rest of the intervals non-overlapping.
//Note:
//You may assume the interval's end point is always bigger than its start
//point.
//Intervals like [1,2] and [2,3] have borders "touching" but they don't overlap
//each other.
//Example 1:
//Input: [ [1,2], [2,3], [3,4], [1,3] ]
//Output: 1
//Explanation: [1,3] can be removed and the rest of intervals are
//non-overlapping.
//Example 2:
//Input: [ [1,2], [1,2], [1,2] ]
//Output: 2
//Explanation: You need to remove two [1,2] to make the rest of intervals
//non-overlapping.
//Example 3:
//Input: [ [1,2], [2,3] ]
//Output: 0
//Explanation: You don't need to remove any of the intervals since they're
//already non-overlapping.


//##################################  ##################################
int eraseOverlapIntervals(vector<Interval>& intervals) {
     auto comp = [](const Interval& i1, const Interval& i2){ return i1.start < i2.start; };
     sort(intervals.begin(), intervals.end(), comp);
     int res = 0, pre = 0;
     for (int i = 1; i < intervals.size(); i++) {
         //Overlapping interval
         if (intervals[i].start < intervals[pre].end) {
             res++;
             //Choose the interval with min end
             if (intervals[i].end < intervals[pre].end) {
               pre = i;
             }
         }
         else pre = i;
     }
     return res;
}

//################ Intervals.size - the answer for "minimum arrows to burst ballons"
struct CMP {
    bool operator () (const Interval &a, const Interval &b) {
        if (a.end == b.end) {
            return a.start > b.start;
        }
        return a.end < b.end;
    }
}cmp;

int eraseOverlapIntervals(vector<Interval>& intervals) {
    int ans = 0, pre_r = INT_MIN;
    sort(intervals.begin(), intervals.end(), cmp);
    for (int i = 0; i < intervals.size(); i++) {
        if (intervals[i].start < pre_r) {
            ans++;
        } else {
            pre_r = intervals[i].end;
        }
    }
    return ans;
}
