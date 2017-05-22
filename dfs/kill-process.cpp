//Kill Process
//Given n processes, each process has a unique PID (process id) and its PPID (parent process id).
//Each process only has one parent process, but may have one or more children processes. This is just like a tree structure. Only one process has PPID that is 0, which means this process has no parent process. All the PIDs will be distinct positive integers.
//We use two list of integers to represent a list of processes, where the first list contains PID for each process and the second list contains the corresponding PPID.
//Now given the two lists, and a PID representing a process you want to kill, return a list of PIDs of processes that will be killed in the end. You should assume that when a process is killed, all its children processes will be killed. No order is required for the final answer.
//Example 1:
//Input: 
//pid =  [1, 3, 10, 5]
//ppid = [3, 0, 5, 3]
//kill = 5
//Output: [5,10]
//Explanation: 
//           3
//         /   \
//        1     5
//             /
//            10
//Kill 5 will also kill 10.
//Note:
//The given kill id is guaranteed to be one of the given PIDs.
//n >= 1.

//##################################################  BFS ##################################################  
vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) { 
  vector<int> killed;
  map<int, set<int>> children;
  for (int i = 0; i < pid.size(); i++) {
      children[ppid[i]].insert(pid[i]);
  }
  queue<int> q;
  q.push(kill);
  while (!q.empty()) {
      int p = q.front(); 
      q.pop();
      killed.push_back(p);
      for (int child : children[p]) {
          q.push(child);
      }
  }
  return killed; 
}

//##################################################  DFS  ##################################################  
vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
    vector<int> killed;
    map<int, set<int>> children;
    for (int i = 0; i < pid.size(); i++) {
        children[ppid[i]].insert(pid[i]);
    }
    killAll(kill, children, killed);
    return killed;
}
void killAll(int pid, map<int, set<int>>& children, vector<int>& killed) {
    killed.push_back(pid);
    for (int child : children[pid]) {
        killAll(child, children, killed);
    }
}


//##################################################  Pytonic  ##################################################  
//Build a (int parent: list[int] children)hashMap
//def killProcess(self, pid, ppid, kill):
//  d = collections.defaultdict(list)
//  for c, p in zip(pid, ppid): 
//    d[p].append(c)
//  bfs = [kill]
//  for i in bfs: bfs.extend(d.get(i, []))
//  return bfs
//
//########################### DFS ######################## 
//def killProcess(self, A, pA, kill):
//    graph = collections.defaultdict(set)
//    for child, parent in zip(A, pA):
//        graph[parent].add(child)
//    
//    seen = set()
//    def dfs(node):
//        seen.add(node)
//        for nei in graph[node]:
//            if nei not in seen:
//                dfs(nei)
//    
//    dfs(kill)
//    return list(seen)
//
//########################## BFS  ########################## 
//from collections import deque
//class Solution(object):
//    def killProcess(self, pid, ppid, kill):
//        """
//        :type pid: List[int]
//        :type ppid: List[int]
//        :type kill: int
//        :rtype: List[int]
//        """
//        ans = [kill]
//        ppDict = collections.defaultdict(list)
//        for i, p in enumerate(ppid):
//            ppDict[p].append(i)
//        queue = deque([kill])
//        while queue:
//            for procIdx in ppDict[queue.popleft()]:
//                ans.append(pid[procIdx])
//                queue.append(pid[procIdx])
//        return ans
