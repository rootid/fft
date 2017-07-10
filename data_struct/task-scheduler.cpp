//Given a char array representing tasks CPU need to do. It contains capital letters A to Z where different letters represent different tasks.Tasks could be done without original order. Each task could be done in one interval. For each interval, CPU could finish one task or just be idle.
//However, there is a non-negative cooling interval n that means between two same tasks, there must be at least n intervals that CPU are doing different tasks or just be idle.
//You need to return the least number of intervals the CPU will take to finish all the given tasks.
//Example 1:
//Input: tasks = ['A','A','A','B','B','B'], n = 2
//Output: 8
//Explanation: A -> B -> idle -> A -> B -> idle -> A -> B.
//Note:
//The number of tasks is in the range [1, 10000].
//The integer n is in the range [0, 100].
//

//######################################### O(N) + S = O(26) ######################################### 
// (c[25] - 1) * (n + 1) + 25 - i  is frame size
// when inserting chars, the frame might be "burst", then tasks.length takes precedence
// when 25 - i > n, the frame is already full at construction, the following is still valid.
//
//c[25]-1: the most frequent letter happen time minus 1
//*(n+1): count for the loops for above
//+25-i: count for the less frequence letters.
////
//For example:
//tasks = ['A','A','A','B','B','B'], n = 2
//
//most frequent letter : A (happen 3 times, let it minus 1= 2)
//count loops: (n+1) =3
//plus the letters left: A,B.
//[A -> B -> idle]*loop1* -> [A -> B -> idle]*loop2* -> A -> B.

//AAAABBBEEFFGG 3
//here X represents a space gap:
//Frame: "AXXXAXXXAXXXA"
//insert 'B': "ABXXABXXABXXA" <--- 'B' has higher frequency than the other characters, insert it first.
//insert 'E': "ABEXABEXABXXA"
//insert 'F': "ABEFABEXABFXA" <--- each time try to fill the k-1 gaps as full or evenly as possible.
//insert 'G': "ABEFABEGABFGA"
//AACCCBEEE 2
//
//3 identical chunks "CE", "CE CE CE" <-- this is a frame
//insert 'A' among the gaps of chunks since it has higher frequency than 'B' ---> "CEACEACE"
//insert 'B' ---> "CEABCEACE" <----- result is tasks.length;
//AACCCDDEEE 3
//
//3 identical chunks "CE", "CE CE CE" <--- this is a frame.
//Begin to insert 'A'->"CEA CEA CE"
//Begin to insert 'B'->"CEABCEABCE" <---- result is tasks.length;
//ACCCEEE 2
//
//3 identical chunks "CE", "CE CE CE" <-- this is a frame
//Begin to insert 'A' --> "CEACE CE" <-- result is (c[25] - 1) * (n + 1) + 25 -i = 2 * 3 + 2 = 8

int leastInterval(vector <char> &tasks, int n) {
  vector<int> c(26,0);
  for(auto t : tasks){
      c[t - 'A']++;
  }
 sort(c.begin(),c.end());
  int i = 25;
  while(i >= 0 && c[i] == c[25]) { //compute all the processes that share the same frquency as the MOST frequenst occuring freq
    i--;
  }
  int t = tasks.size();
  return max( t , (c[25] - 1) * (n + 1) + 25 - i );
}

//######################################### One Pass  ######################################### 
public class Solution {
    public int leastInterval(char[] tasks, int n) {
        int len = tasks.length;
        int[] count = new int[26];
        int max = 0, maxNum = 0;
        for (char c : tasks) {
            count[c - 'A']++;
            if (count[c - 'A'] > max) {
                max = count[c - 'A'];
                maxNum = 1;
            } else if (count[c - 'A'] == max) {
                maxNum++;
            }
        }
        return Math.max(len, (max - 1) * (n + 1) + maxNum);
    }
}


//################################ Map + Priority Queue ############################### 
//map<task, totalTaskCount>
//priority_queue<task, count>
//
//1. To work on the same task again, CPU has to wait for time n, therefore we can think of as if there is a cycle, of time n+1, regardless whether you schedule some other task in the cycle or not.
//2. To avoid leave the CPU with limited choice of tasks and having to sit there cooling down frequently at the end, it is critical the keep the diversity of the task pool for as long as possible.
//3. In order to do that, we should try to schedule the CPU to always try round robin between the most popular tasks at any time.
int leastInterval(vector<char>& tasks, int n) { 
  unordered_map<char, int> counts;
  for (char t : tasks) {
      counts[t]++;
  }
  priority_queue<pair<int, char> > pq;
  for (pair<char, int> count : counts) {
      pq.push(make_pair(count.second, count.first));
  }
  int alltime = 0;
  int cycle = n + 1;
  while (!pq.empty()) {
      int time = 0;
      vector<pair<int, char> > tmp;
      //iterate over cycle
      for (int i = 0; i < cycle; i++) {
          if (!pq.empty()) {
              tmp.push_back(pq.top()); //given all equal tasks
              pq.pop();
              time++; //each task took 1 unit time
          }
      }
      for (auto t : tmp) {
          if (--t.first) {
              pq.push(t); //update the priority queue
          }
      }
      //if all elements are equal then waiting time += cycle else waiting time += time
      alltime += !pq.empty() ? cycle : time;
  }
  return alltime;
}

//#################################################### store only count #################################################### 
//priority_queue<count> : Only store the count instead of <task,count>
int leastInterval(vector<char>& tasks, int n) {
    unordered_map<char, int> counts;
    for (char t : tasks) {
        counts[t]++;
    }
    priority_queue<int> pq;
    for (pair<char, int> count : counts) {
        pq.push(count.second);
    }
    int alltime = 0;
    int cycle = n + 1;
    while (!pq.empty()) {
        int time = 0;
        vector<int> tmp;
        for (int i = 0; i < cycle; i++) {
            if (!pq.empty()) {
                tmp.push_back(pq.top());
                pq.pop();
                time++;
            }
        }
        for (int cnt : tmp) {
            if (--cnt) {
                pq.push(cnt);
            }
        }
        alltime += !pq.empty() ? cycle : time;
    }
    return alltime;
}


//################################################### pytonic ################################################### 


//################################################### O(N) ################################################### 
//def leastInterval(self, tasks, N):
//    task_counts = collections.Counter(tasks).values()
//    M = max(task_counts) #Most frequent tasks
//    Mct = task_counts.count(M) # # of tasks which share the same frquency
//    return max(len(tasks), (M - 1) * (N + 1) + Mct)

//https://discuss.leetcode.com/topic/92952/python-straightforward-with-explanation

//################################################### O(N log N) ################################################### 
//class Solution(object):
//    
//    # O(nlogn) greedy to place most popular and distinct tasks first
//    # Actually, I don't think this is greedy
//    # We always place different tasks in a cycle which will minimize steps
//    # If not different tasks can be placed in a cycle, place an `idle`.
//    
//    def _leastInterval(self, tasks, n):
//        """
//        :type tasks: List[str]
//        :type n: int
//        :rtype: int
//        """
//        n += 1
//        ans = 0
//        d = collections.Counter(tasks)
//        heap = [-c for c in d.values()]
//        heapq.heapify(heap)
//        while heap:
//            stack = []
//            cnt = 0
//            for _ in range(n):
//                if heap:
//                    c = heapq.heappop(heap)
//                    cnt += 1
//                    if c < -1:
//                        stack.append(c + 1)
//            for item in stack:
//                heapq.heappush(heap, item)
//            ans += heap and n or cnt # == if heap then n else cnt
//        return ans
//        
    
//################################################### O(N ) ################################################### 
//    # O(n) # of the most frequent tasks, say longest, will determine the legnth
//    # to void counting idle intervals, we count (longest - 1) * (n + 1)
//    # then count how many will in the last cycle which means finding ties
//    # if counted number is less than # of tasks which means 
//    # less frequent tasks can be always placed in such cycle
//    # and it won't cause any conflicts with requirement since even most frequent can be settle
//    # finally, return max(# of task, total counted number)
//    
//    def leastInterval(self, tasks, n):
//        d = collections.Counter(tasks)
//        counts = d.values()
//        longest = max(counts)
//        ans = (longest - 1) * (n + 1)
//        for count in counts:
//            ans += count == longest and 1 or 0
//        return max(len(tasks), ans)
//

// vim: set sw=2 sts=2 tw=120 et nospell : 

