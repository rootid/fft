//Course Schedule II
//There are a total of n courses you have to take, labeled from 0 to n - 1.
//Some courses may have prerequisites, for example to take course 0 you have to
//first take course 1, which is expressed as a pair: [0,1]
//Given the total number of courses and a list of prerequisite pairs, return
//the ordering of courses you should take to finish all courses.
//There may be multiple correct orders, you just need to return one of them. If
//it is impossible to finish all courses, return an empty array.
//For example:
//2, [[1,0]]
//There are a total of 2 courses to take. To take course 1 you should have
//finished course 0. So the correct course order is [0,1]
//4, [[1,0],[2,0],[3,1],[3,2]]
//There are a total of 4 courses to take. To take course 3 you should have
//finished both courses 1 and 2. Both courses 1 and 2 should be taken after you
//finished course 0. So one correct course order is [0,1,2,3]. Another correct
//ordering is[0,2,1,3].
//Note:
//The input prerequisites is a graph represented by a list of edges, not
//adjacency matrices. Read more about how a graph is represented.
//You may assume that there are no duplicate edges in the input prerequisites

vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
  vector<vector<int> > adjList( numCourses,vector<int>() );
    vector<int> inDegrees(numCourses,0);
    vector<int> pOrderResult;
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
    return pOrderResult;
  }
  while(!zeroInDegStack.empty()) {
    pOrderResult.push_back(zeroInDegStack.top());
    zeroInDegStack.pop();
    for (auto j : adjList[pOrderResult.back()]) {
        inDegrees[j]--;
        if (inDegrees[j] == 0) {
            zeroInDegStack.push(j);
        }
    }
  }
  if(pOrderResult.size() == numCourses) {
        return pOrderResult;
  }
  return vector<int>{};
}
