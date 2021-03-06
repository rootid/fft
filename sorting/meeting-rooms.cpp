//Meeting Rooms
//Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), determine
//if a person could attend all meetings.
//For example,
//Given [[0, 30],[5, 10],[15, 20]],
//return false.


//######################################### O(n log n) #########################################
public boolean canAttendMeetings(Interval[] intervals) {
    if(intervals == null || intervals.length <= 1) return true;
    Arrays.sort(intervals, (a,b) -> a.start - b.start);
    for(int i=1;i<intervals.length;i++) {
         if (intervals[i].start < intervals[i - 1].end) return false;
    }
    return true;
}

//######################################### O(n log n) #########################################
struct comp {
     bool operator() (Interval &a,Interval &b) {
         return a.start < b.start;
     }
};
bool canAttendMeetings(vector<Interval>& intervals) {
    sort(intervals.begin(),intervals.end(),comp());
    int len = intervals.size();
    for(int i=1;i<len;i++) {
        if(intervals[i-1].end > intervals[i].start) {
            return false;
        }
    }
    return true;
}

/* vim: set ts=2 sw=2 sts=2 tw=120 et: */
