//Design a hit counter which counts the number of hits received in the past 5
//minutes.
//Each function accepts a timestamp parameter (in seconds granularity) and you
//may assume that calls are being made to the system in chronological order
//(ie, the timestamp is monotonically increasing). You may assume that the
//earliest timestamp starts at 1.
//It is possible that several hits arrive roughly at the same time.
//Example:
//HitCounter counter = new HitCounter();
//// hit at timestamp 1.
//counter.hit(1);
//// hit at timestamp 2.
//counter.hit(2);
//// hit at timestamp 3.
//counter.hit(3);
//// get hits at timestamp 4, should return 3.
//counter.getHits(4);
//// hit at timestamp 300.
//counter.hit(300);
//// get hits at timestamp 300, should return 4.
//counter.getHits(300);
//// get hits at timestamp 301, should return 3.
//counter.getHits(301);
//Follow up:
//What if the number of hits per second could be very large? Does your design
//scale?


//#########################################  #########################################
//
//O(s) s is total seconds in given time interval, in this case 300.
//basic ideal is using buckets. 1 bucket for every second because we only need
//to keep the recent hits info for 300 seconds.
//hit[] array is wrapped around by mod operation. Each hit bucket is associated
//with times[] bucket which record current time. If it is not current time, it
//means it is 300s or 600s... ago and need to reset to 1.
//
public class HitCounter {
    private int[] times;
    private int[] hits;
    /** Initialize your data structure here. */
    public HitCounter() {
        times = new int[300];
        hits = new int[300];
    }

    /** Record a hit.
        @param timestamp - The current timestamp (in seconds granularity). */
    public void hit(int timestamp) {
        int index = timestamp % 300;
        if (times[index] != timestamp) {
            times[index] = timestamp;
            hits[index] = 1;
        } else {
            hits[index]++;
        }
    }

    /** Return the number of hits in the past 5 minutes.
        @param timestamp - The current timestamp (in seconds granularity). */
    public int getHits(int timestamp) {
        int total = 0;
        for (int i = 0; i < 300; i++) {
            if (timestamp - times[i] < 300) {
                total += hits[i];
            }
        }
        return total;
    }
}


//#########################################  #########################################
class HitCounter(object):

    def __init__(self):
        self.q = [(0, 0)] * 300

    def hit(self, timestamp):
        idx = timestamp % 300
        time, hit = self.q[idx]
        if time != timestamp:
            self.q[idx] = timestamp, 1
        else:
            self.q[idx] = time, hit + 1

    def getHits(self, timestamp):
        ans = 0
        for i in xrange(0, len(self.q)):
            time, hit = self.q[i]
            if timestamp - time < 300:
                ans += hit
        return ans
