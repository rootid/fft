//Insert Interval
//Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).
//You may assume that the intervals were initially sorted according to their start times.
//Example 1:
//Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].
//Example 2:
//Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].
//This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
//
vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
    int ns = newInterval.start;
    int ne = newInterval.end;
    vector<Interval> left;
    vector<Interval> right;
    for(auto &i:intervals) {
        if(i.end < ns) {
            left.push_back(i);
        } else if(i.start > ne) {
            right.push_back(i);
        }
    }
    if(left.size() + right.size() != intervals.size()) {
        ns = min(ns,intervals[left.size()].start);
        ne = max(ne,intervals[intervals.size()-right.size()-1].end);
    }
    Interval mid(ns,ne);
    left.push_back(mid);
    left.insert(left.end(),right.begin(),right.end());
    return left;
}

int main() {

}
