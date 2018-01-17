//Design Log Storage System
//You are given several logs that each log contains a unique id and timestamp. Timestamp is a string that has the following format: Year:Month:Day:Hour:Minute:Second, for example, 2017:01:01:23:59:59. All domains are zero-padded decimal numbers.
//Design a log storage system to implement the following functions:
//void Put(int id, string timestamp): Given a log's unique id and timestamp, store the log in your storage system.
//int[] Retrieve(String start, String end, String granularity): Return the id of logs whose timestamps are within the range from start to end. Start and end all have the same format as timestamp. However, granularity means the time level for consideration. For example, start = "2017:01:01:23:59:59", end = "2017:01:02:23:59:59", granularity = "Day", it means that we need to find the logs within the range from Jan. 1st 2017 to Jan. 2nd 2017.
//Example 1:
//put(1, "2017:01:01:23:59:59");
//put(2, "2017:01:01:22:59:59");
//put(3, "2016:01:01:00:00:00");
//retrieve("2016:01:01:01:01:01","2017:01:01:23:00:00","Year"); // return [1,2,3], because you need to return all logs within 2016 and 2017.
//retrieve("2016:01:01:01:01:01","2017:01:01:23:00:00","Hour"); // return [1,2], because you need to return all logs start from 2016:01:01:01 to 2017:01:01:23, where log 3 is left outside the range.
//Note:
//1. There will be at most 300 operations of Put or Retrieve.
//2. Year ranges from [2000,2017]. Hour ranges from [00,23].
//3. Output for Retrieve has no order required.
//
//
//######################################### O(n) #########################################
class LogSystem {
private:
    unordered_map<string, int> map{{"Year",4},{"Month",7},{"Day",10},{"Hour",13},{"Minute",16},{"Second",19}};
    vector<string> logs;
    vector<int> ids;
public:
    LogSystem() {
        
    }
    
    void put(int id, string timestamp) {
        ids.push_back(id);
        logs.push_back(timestamp);
    }
    
    vector<int> retrieve(string s, string e, string gra) {
        int n = map[gra];
        auto ss = s.substr(0, n);
        auto se = e.substr(0, n);
        vector<int> r;
        for (int i = 0; i < logs.size(); i++){
            auto s = logs[i].substr(0, n);
            if (s >= ss && s <= se){
                r.push_back(ids[i]);
            }
        }
        return r;
    }
};

//###################### Compare only the timestamps upto the level of granularity ###################### 
//O(n log n) : sort
//O(log n) : search
//class LogSystem(object):
//    def __init__(self):
//        self.logs = []
//
//    def put(self, tid, timestamp):
//        self.logs.append((tid, timestamp))
//        
//    def retrieve(self, s, e, gra):
//        index = {'Year': 5, 'Month': 8, 'Day': 11, 
//                 'Hour': 14, 'Minute': 17, 'Second': 20}[gra]
//        start = s[:index]
//        end = e[:index]
//         
//        return sorted(tid for tid, timestamp in self.logs
//                      if start <= timestamp[:index] <= end)
//#2016:01:01:00:00:00

//##################################### Use of dictionary   ##################################### 
//same idea of truncating/pruning the timestamp as per granularity, but converted the timestamp to a tuple by splitting at : before storing/comparing so thinking of which index to prune the tuple as it was simple to think of. (For Year, prune the timestamp tuple from index 1 and onwards, for Month prune from index 2 and onwards...).
//lexicographic comparison of elements in the tuple will work as intended because year/month/... are all padded to the same length in the given input. And since each of year/month/day, etc have the same length we could even directly slice the string without converting to tuple which brings us to back to your solution.
//# Map of granularity to index at which the timestamp should be pruned for respective granularity
//gmap = { 'Year': 1, 'Month': 2, 'Day': 3, 'Hour': 4, 'Minute': 5, 'Second': 6 }
//
//class LogSystem:
//    def __init__(self):
//        self.d = {}
//        
//    def put(self, id, timestamp):
//        t = tuple(timestamp.split(':'))
//        self.d[t] = id
//
//    def retrieve(self, s, e, gra):
//        idx = gmap[gra]     # Prune from this index onwards
//        s = tuple(s.split(':')[:idx])
//        e = tuple(e.split(':')[:idx])
//
//        ans = []
//        for t in self.d.keys():
//            if s <= t[:idx] <= e:
//                ans.append(self.d[t])
//        return ans


/**
 * Your LogSystem object will be instantiated and called as such:
 * LogSystem obj = new LogSystem();
 * obj.put(id,timestamp);
 * vector<int> param_2 = obj.retrieve(s,e,gra);
 */

// vim: set sw=2 sts=2 tw=120 et nospell : 
