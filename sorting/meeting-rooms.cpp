//Meeting Rooms
//Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), determine if a person could attend all meetings.
//For example,
//Given [[0, 30],[5, 10],[15, 20]],
//return false.

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
