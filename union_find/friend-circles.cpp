//Friend Circles
//There are N students in a class. Some of them are friends, while some are
//not. Their friendship is transitive in nature. For example, if A is a direct
//friend of B, and B is a direct friend of C, then A is an indirect friend of
//C. And we defined a friend circle is a group of students who are direct or
//indirect friends.
//Given a N*N matrix M representing the friend relationship between students in
//the class. If M[i][j] = 1, then the ith and jth students are direct friends
//with each other, otherwise not. And you have to output the total number of
//friend circles among all the students.
//Example 1:
//Input:
//[[1,1,0],
// [1,1,0],
// [0,0,1]]
//Output: 2
//Explanation:The 0th and 1st students are direct friends, so they are in a
//friend circle.
//The 2nd student himself is in a friend circle. So return 2.
//Example 2:
//Input:
//[[1,1,0],
// [1,1,1],
// [0,1,1]]
//Output: 1
//Explanation:The 0th and 1st students are direct friends, the 1st and 2nd
//students are direct friends,
//so the 0th and 2nd students are indirect friends. All of them are in the same
//friend circle, so return 1.
//Note:
//N is in range [1,200].
//M[i][i] = 1 for all students.
//If M[i][j] = 1, then M[j][i] = 1.

//######################################### UF ##########################################
class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
      if (M.empty()) return 0;
      int n = M.size();
      vector<int> leads(n, 0); //parents
      for (int i = 0; i < n; i++) {
        leads[i] = i;  //[1,2,....,n]
      }   // initialize leads for every kid as themselves
      int groups = n; //At most n groups exists
      for (int i = 0; i < n; i++) {
          for (int j = i + 1; j < n; j++) {   // avoid recalculate M[i][j], M[j][i]
              if (M[i][j]) {
                  int lead1 = find(i, leads); //Always j > i,lead2 > lead1
                  int lead2 = find(j, leads);
                  if (lead1 != lead2) {       // if 2 group belongs 2 different leads, merge 2 group to 1
                      leads[lead1] = lead2;
                      groups--;
                  }
              }
          }
      }
      return groups;
    }

private:
    //Recurive parent find
    int find(int x, vector<int>& parents) {
        return parents[x] == x ? x : find(parents[x], parents);
    }
};

//######################################### DFS  ##########################################
class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        if (M.empty()) return 0;
        int n = M.size();
        vector<bool> visited(n, false);
        int groups = 0;
        for (int i = 0; i < visited.size(); i++) {
            groups += !visited[i] ? dfs(i, M, visited), 1 : 0;
        }
        return groups;
    }

private:
    void dfs(int i, vector<vector<int>>& M, vector<bool>& visited) {
        visited[i] = true;
        for (int j = 0; j < visited.size(); j++) {
            if (i != j && M[i][j] && !visited[j]) {
                dfs(j, M, visited);
            }
        }
    }
};


//######################################### DFS-1 ##########################################
class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        if (M.empty()) return 0;
        int n = M.size();
        vector<bool> visited(n, false);
        int groups = 0;
        for (int i = 0; i < visited.size(); i++) {
            groups += dfs(i, M, visited) > 0;
        }
        return groups;
    }

private:
    int dfs(int i, vector<vector<int>>& M, vector<bool>& visited) {
        if (visited[i]) {
            return 0;
        }

        int ppl = 1;
        visited[i] = true;
        for (int j = 0; j < visited.size(); j++) {
            if (i != j && M[i][j]) {
                ppl += dfs(j, M, visited);
            }
        }

        return ppl;
    }
};


//################################# pytonic  ################################
//import scipy.sparse
//
//class Solution(object):
//    def findCircleNum(self, M):
//        return scipy.sparse.csgraph.connected_components(M)[0]

//compute the transitive closure of the (boolean) matrix and count the number
//of different rows:
//import numpy as np
//class Solution(object):
//    def findCircleNum(self, M):
//        return len(set(map(tuple, (np.matrix(M, dtype='bool')**len(M)).A)))
//
//#################################### DFS recursive  ####################################
//def findCircleNum(self, A):
//    N = len(A)
//    seen = set()
//    def dfs(node):
//        for nei, adj in enumerate(A[node]):
//            if adj and nei not in seen:
//                seen.add(nei)
//                dfs(nei)
//
//    ans = 0
//    for i in xrange(N):
//        if i not in seen:
//            dfs(i)
//            ans += 1
//    return ans

//#################################### DFS iterative  ####################################
//class Solution(object):
//    def findCircleNum(self, M):
//        seen = set([])
//        res = 0
//        for i in range(len(M)):
//            if i not in seen:
//                toSee = [i]
//                while len(toSee):
//                    cur = toSee.pop()
//                    if cur not in seen:
//                        seen.add(cur)
//                        toSee = [j for j,v in enumerate(M[cur]) if v and j not in seen] + toSee
//                res += 1
//        return res
//
//
//#################################### DFS queue  ####################################
//class Solution(object):
//    def findCircleNum(self, M):
//        """
//        :type M: List[List[int]]
//        :rtype: int
//        """
//        if len(M) == 0: return 0
//        s = set(range(len(M)))
//        count = 0
//        q = []
//        while True:
//            if len(q) == 0:
//                if s:
//                    q.append(s.pop())
//                    count += 1
//                else:
//                    break
//            item, q = q[0], q[1:]
//            for i in list(s):
//                if M[item][i]:
//                    q.append(i)
//                    s.remove(i)
//        return count
