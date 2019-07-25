//Meeting Rooms II
//Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the
//minimum number of conference rooms required.
//For example,
//Given [[0, 30],[5, 10],[15, 20]],
//return 2.
//


//######################################### Sort by start time and store the meetings by increasing order of end time #########################################
public int minMeetingRooms(Interval[] intervals) {
    if(intervals == null || intervals.length == 0) return 0;
    int rooms = 0;
    int len = intervals.length;
    Arrays.sort(intervals, (a,b) -> a.start - b.start);
    //pQ - acts like building store the valid meetings
    PriorityQueue<Interval> pQ = new PriorityQueue<>(len, (a,b) -> a.end - b.end);
    for(int i=0;i<len;i++) {
        while(!pQ.isEmpty() && intervals[i].start >= pQ.peek().end)
            pQ.poll();
        pQ.offer(intervals[i]);
        rooms = Math.max(rooms, pQ.size());
    }
    return rooms;
}


//######################################### 2 Vectors + Sort #########################################
//# Very similar with what we do in real life. Whenever you want to start a meeting,
//# you go and check if any empty room available (available > 0) and
//# if so take one of them ( available -=1 ). Otherwise,
//# you need to find a new room someplace else ( numRooms += 1 ).
//# After you finish the meeting, the room becomes available again ( available += 1 ).
def minMeetingRooms(self, intervals):
       starts = []
       ends = []
       for i in intervals:
           starts.append(i.start)
           ends.append(i.end)
       starts.sort()
       ends.sort()
       s = e = 0
       numRooms = available = 0
       while s < len(starts):
           if starts[s] < ends[e]:
               if available == 0:
                   numRooms += 1
               else:
                   available -= 1
               s += 1
           else:
               available += 1
               e += 1
       return numRooms



//######################################### Dictionary #########################################
def minMeetingRooms(intervals):

    mp = collections.defaultdict(int)
    for item in intervals:
        mp[item.start] += 1
        mp[item.end] -= 1

    ret = cnt = 0
    for i in sorted(mp.keys()):
        cnt += mp[i]
        ret = max(ret, cnt)
    return ret
//######################################### Min Heap #########################################
static bool cmpStart(Interval x, Interval y){
    return x.start < y.start;
}
int minMeetingRooms(vector<Interval>& intervals) {
    if(intervals.size() == 0) return 0;
    sort(intervals.begin(), intervals.end(), cmpStart);
    int cnt = 1;
    priority_queue<int, vector<int>, std::greater<int>> pq;
    pq.push(intervals[0].end);
    for(int i = 1; i < intervals.size(); ++i){
        if(pq.top() <= intervals[i].start)
            pq.pop();
        pq.push(intervals[i].end);
        cnt = max(cnt, (int)pq.size());
    }
    return cnt;
}

//######################################### Min Heap #########################################
//min heap, average time complexity is O(nlogn)
public int minMeetingRooms(Interval[] intervals) {
    if (intervals == null || intervals.length == 0)
        return 0;

    // Sort the intervals by start time
    Arrays.sort(intervals, new Comparator<Interval>() {
        public int compare(Interval a, Interval b) { return a.start - b.start; }
    });
    // Use a min heap to track the minimum end time of merged intervals
    PriorityQueue<Interval> heap = new PriorityQueue<Interval>(intervals.length, new Comparator<Interval>() {
        public int compare(Interval a, Interval b) { return a.end - b.end; }
    });

    // start with the first meeting, put it to a meeting room
    heap.offer(intervals[0]);
    for (int i = 1; i < intervals.length; i++) {
        // get the meeting room that finishes earliest
        Interval interval = heap.poll();
        if (intervals[i].start >= interval.end) {
            // if the current meeting starts right after
            // there's no need for a new room, merge the interval
            interval.end = intervals[i].end;
        } else {
            // otherwise, this meeting needs a new room
            heap.offer(intervals[i]);
        }
        // don't forget to put the meeting room back
        heap.offer(interval);
    }
    return heap.size();
}


//#########################################  Map  #########################################
//First collect the changes: at what times the number of meetings goes up or down and by how much.
//Then go through those changes in ascending order and keep track of the current and maximum number
//of rooms needed.
//Given [[0, 30],[5, 10],[15, 20]],
//return 2.
int minMeetingRooms(vector<Interval>& intervals) {
    map<int, int> changes;
    for (auto i : intervals) {
        changes[i.start] += 1;
        changes[i.end] -= 1;
    }
    int rooms = 0, maxrooms = 0;
    for (auto change : changes)
        maxrooms = max(maxrooms, rooms += change.second);
    return maxrooms;
}


//######################################### vector  #########################################
int minMeetingRooms(vector<Interval>& intervals) {
    vector<pair<int, int>> changes;
    for (auto i : intervals) {
        changes.push_back({i.start, 1});
        changes.push_back({i.end, -1});
    };
    sort(begin(changes), end(changes));
    int rooms = 0, maxrooms = 0;
    for (auto change : changes)
        maxrooms = max(maxrooms, rooms += change.second);
    return maxrooms;
}

//######################################### 2 vectors  #########################################
//Uses separate vectors for start and end times, which ends up consistently being fastest. I'm guessing it's mostly
//because working with ints is simpler than working with pairs of ints. The initial sorting also needs fewer steps,
//2(nlogn) instead of (2n)log(2n), but I think the added merging in the later loop cancels that advantage out.
int minMeetingRooms(vector<Interval>& intervals) {
    vector<int> starts, ends;
    for (auto i : intervals) {
        starts.push_back(i.start);
        ends.push_back(i.end);
    }
    sort(begin(starts), end(starts));
    sort(begin(ends), end(ends));
    int e = 0, rooms = 0, available = 0;
    for (int start : starts) {
        while (ends[e] <= start) {
            ++e;
            ++available;
        }
        available ? --available : ++rooms;
    }
    return rooms;
}
/* vim: set ts=2 sw=2 sts=2 tw=120 et: */
