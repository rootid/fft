//Merge Intervals
//Given a collection of intervals, merge all overlapping intervals.
//For example,
//Given [1,3],[2,6],[8,10],[15,18],
//return [1,6],[8,10],[15,18].
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
    
private :
    struct IComparator {
          bool operator() (const Interval &a,const Interval &b) {
              return (a.start < b.start);
          }  
    };
    //used when don't want to use  comparator
    static bool wo_struct_comp(Interval interval1, Interval interval2) { 
           return interval1.start < interval2.start;
    }
public:
    vector<Interval> merge(vector<Interval>& intervals) {
         vector<Interval> res;
         int len = intervals.size();
         if(len == 0) {
             return res;
         }
         sort(intervals.begin(), intervals.end(), IComparator());
         res.push_back(Interval(intervals[0].start,intervals[0].end) );
         for(int i=1;i<len;i++) {
             //if(res[res.size() - 1].end >= intervals[i].start) {
             // res[res.size() - 1].end = max(intervals[i].end, res[res.size() - 1].end);
              if(res.back().end >= intervals[i].start) {
                 res.back().end = max(intervals[i].end, res.back().end);
             } else {
                 res.push_back(Interval(intervals[i].start,intervals[i].end));
             }
         }
        
         return res;
    }
};

//######################################### Python  ######################################### 
def merge(self, intervals):
    out = []
    for i in sorted(intervals, key=lambda i: i.start):
        if out and i.start <= out[-1].end:
            out[-1].end = max(out[-1].end, i.end)
        else:
            out += i,
    return out
