//Course Schedule
//There are a total of n courses you have to take, labeled from 0 to n - 1.
//Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]
//Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?
//For example:
//2, [[1,0]] 1<- 0
//There are a total of 2 courses to take. To take course 1 you should have finished course 0. So it is possible.
//2, [[1,0],[0,1]]
//There are a total of 2 courses to take. To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.
//Note:
//The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.
//You may assume that there are no duplicate edges in the input prerequisites.

//######################################### O(V^2) ######################################### 
 public boolean canFinish(int numCourses, int[][] prerequisites) {
        //1. Create AdjGraph
        //2. Use O(v^2) traversal
        Map<Integer, List<Integer>> adjMap = new HashMap<>();
        int[] inDeg = new int[numCourses];
        for(int[] edge: prerequisites) {
            inDeg[edge[1]]++;
            adjMap.computeIfAbsent(edge[0], k-> new ArrayList()).add(edge[1]);
        }
        for(int i=0;i<inDeg.length;i++) {
            int j = 0;
            for(;j < inDeg.length; j++) 
                if(inDeg[j] == 0) break;
             if (j == numCourses) return false;
             inDeg[j] = -1; //Mark selected vertex as visted or Remove from vertexxList
             List<Integer> outNbrs = adjMap.get(j);
             if(outNbrs != null) {
                 for(Integer v : outNbrs) {
                    inDeg[v]--;
                 }
             }
        }
        return true;    
    }


//Kahn's Algo
//http://www.geeksforgeeks.org/topological-sorting-indegree-based-solution/
//############################## Kahn's algo ############################## 
bool canFinish(int numCourses, vector<pair<int, int> > &prerequisites) {
  vector<vector<int> > adjList( numCourses,vector<int>() );
    vector<int> inDegrees(numCourses,0);
    int sum = 0;
    for (auto i : prerequisites) { 
    adjList[i.second].push_back(i.first);
        inDegrees[i.first]++;
    }
    stack<int> zeroInDegStack;
    for(auto i=0;i<inDegrees.size();i++){ 
        if(inDegrees[i] == 0) { 
            zeroInDegStack.push(i); 
        }
  }
  if(zeroInDegStack.size() == 0) { 
    return false;
  }
  stack<int> pOrderResult;
  while(!zeroInDegStack.empty()) { 
    pOrderResult.push(zeroInDegStack.top());
    zeroInDegStack.pop();
    for (auto j : adjList[pOrderResult.top()]) {
        inDegrees[j]--;
        if (inDegrees[j] == 0) {
            zeroInDegStack.push(j); 
        }
    } 
  }
  if(pOrderResult.size() != numCourses) {
        return false;
  }
  return true;
}

//######################################### BFS ############################## 
bool canFinish(int numCourses, vector<pair<int, int> > &prerequisites) {
    vector<unordered_set<int> > dg(numCourses);
    for(auto &i:prerequisites) {
            dg[i.second].insert(i.first);
    }
    vector<int> indegree(numCourses,0);
    for (int i = 0; i != numCourses; i++) {
        for(auto it = dg[i].begin(); it != dg[i].end(); it++) {
           indegree[*it]++;
      }
    }
    queue<int> zeros;
    for (int i = 0; i != numCourses; ++i) { 
    if (indegree[i] == 0) {
        zeros.push(i);
      } 
    }
    while (!zeros.empty()) { 
      int seq = zeros.front();
          zeros.pop();
          for (auto it = dg[seq].begin(); it != dg[seq].end(); ++it) {
              if (--indegree[*it] == 0) {
                  zeros.push(*it);
        } 
      } 
      --numCourses;
    } 
    return numCourses == 0; 
}

//#################################### DFS ################################### 
//Deepness will cause the issue (0->1->2->4->........-> 1)
bool canFinish(int numCourses, vector<pair<int, int>>& prer) {
    vector<vector<int> > dig(numCourses);
    vector<int> visited(numCourses, 0); // White at initialization
    for (int i = 0; i < prer.size(); i++) {
        dig[prer[i].second].push_back(prer[i].first);
    }
    bool cycle = false;
    for (int i = 0; i < numCourses; i++) {
        if (cycle) return false;
        if (visited[i] == 0) {
          dfs_top(i, dig, visited, cycle);
        }
    }
    return !cycle;
}
void dfs_top(int node, vector<vector<int>> &dig, vector<int> &visited, bool &cycle) {
    if (visited[node] == 1) {
      cycle = true; 
      return;
    } // cycle occurs, break the dfs chain and all return
    visited[node] = 1; //Gray, searching
    for (int i = 0; i < dig[node].size(); i++) {
        dfs_top(dig[node][i], dig, visited, cycle);
        if (cycle) {
          return; // do some pruning here
        }
    }
    visited[node] = 2; //Black Once finished.
}
