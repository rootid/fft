//Insert Interval
//Given a set of non-overlapping intervals, insert a new interval into the
//intervals (merge if necessary).
//You may assume that the intervals were initially sorted according to their
//start times.
//Example 1:
//Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].
//Example 2:
//Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as
//[1,2],[3,10],[12,16].
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

//######################################### In-place  #########################################
public static ArrayList<Interval> insertRange(ArrayList<Interval> intervals, Interval newInterval) {
      int i=0;
	  //When no change occurred
      while(i<intervals.size() && intervals.get(i).end < newInterval.start) i++;
	  //remove old interval and prepare new interval
      while(i<intervals.size() && intervals.get(i).start <= newInterval.end){
          newInterval = new Interval(Math.min(intervals.get(i).start, newInterval.start), Math.max(intervals.get(i).end, newInterval.end));
          intervals.remove(i);
      }
	  //Add new interval
      intervals.add(i,newInterval);
      return intervals;
}

//######################################### Xtra-place  #########################################
public List<Interval> insert(List<Interval> intervals, Interval newInterval) {
    List<Interval> result = new LinkedList<>();
    int i = 0;
    // add all the intervals ending before newInterval starts
    while (i < intervals.size() && intervals.get(i).end < newInterval.start)
        result.add(intervals.get(i++));
    // merge all overlapping intervals to one considering newInterval
    while (i < intervals.size() && intervals.get(i).start <= newInterval.end) {
        newInterval = new Interval( // we could mutate newInterval here also
                Math.min(newInterval.start, intervals.get(i).start),
                Math.max(newInterval.end, intervals.get(i).end));
        i++;
    }
    result.add(newInterval); // add the union of intervals we got
    // add all the rest
    while (i < intervals.size()) result.add(intervals.get(i++));
    return result;
}

//######################################### Two Pass #########################################
//Collect the intervals strictly left or right of the new interval,
// then merge the new one with the middle ones (if any) before inserting it between left and right ones.
def insert(self, intervals, newInterval):
    s, e = newInterval.start, newInterval.end
    left = [i for i in intervals if i.end < s]
    right = [i for i in intervals if i.start > e]
    if left + right != intervals:
        s = min(s, intervals[len(left)].start)
        e = max(e, intervals[~len(right)].end)
    return left + [Interval(s, e)] + right

//######################################### One Pass #########################################
//same algorithm as solution 1, but different implementation with only one pass
//and explicitly collecting the to-be-merged intervals.
def insert(self, intervals, newInterval):
    s, e = newInterval.start, newInterval.end
    parts = merge, left, right = [], [], []
    for i in intervals:
        parts[(i.end < s) - (i.start > e)].append(i)
    if merge:
        s = min(s, merge[0].start)
        e = max(e, merge[-1].end)
    return left + [Interval(s, e)] + right

//######################################### One Pass #########################################
//Same algo but collect and merge while going over the intervals once.
def insert(self, intervals, newInterval):
    s, e = newInterval.start, newInterval.end
    left, right = [], []
    for i in intervals:
        if i.end < s:
            left += i,
        elif i.start > e:
            right += i,
        else:
            s = min(s, i.start)
            e = max(e, i.end)
    return left + [Interval(s, e)] + right





int main() {

}
