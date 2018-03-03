//Redundant Connection
//In this problem, a tree is an undirected graph that is connected and has no
//cycles.
//The given input is a graph that started as a tree with N nodes (with distinct
//values 1, 2, ..., N), with one additional edge added. The added edge has two
//different vertices chosen from 1 to N, and was not an edge that already
//existed.
//The resulting graph is given as a 2D-array of edges. Each element of edges is
//a pair [u, v] with u < v, that represents an undirected edge connecting nodes
//u and v.
//Return an edge that can be removed so that the resulting graph is a tree of N
//nodes. If there are multiple answers, return the answer that occurs last in
//the given 2D-array. The answer edge [u, v] should be in the same format, with
//u < v.
//Example 1:
//Input: [[1,2], [1,3], [2,3]]
//Output: [2,3]
//Explanation: The given undirected graph will be like this:
//  1
// / \
//2 - 3
//Example 2:
//Input: [[1,2], [2,3], [3,4], [1,4], [1,5]]
//Output: [1,4]
//Explanation: The given undirected graph will be like this:
//5 - 1 - 2
//    |   |
//    4 - 3
//Note:
//The size of the input 2D-array will be between 3 and 1000.
//Every integer represented in the 2D-array will be between 1 and N, where N is
//the size of the input array.
//
//Update (2017-09-26):
//We have overhauled the problem description + test cases and specified clearly
//the graph is an undirected graph. For the directed graph follow up please see
//Redundant Connection II). We apologize for any inconvenience causede

//############################### Union find  ###############################
public int[] findRedundantConnection(int[][] edges) {
    int[] parent = new int[2001];
    for (int i = 0; i < parent.length; i++) parent[i] = i;
    for (int[] edge: edges){
        int f = edge[0], t = edge[1];
        if (find(parent, f) == find(parent, t)) return edge;
        else parent[find(parent, f)] = find(parent, t);
    }
    return new int[2];
}
private int find(int[] parent, int f) {
    if (f != parent[f]) {
      parent[f] = find(parent, parent[f]);
    }
    return parent[f];
}

//############################### Union find  ###############################
class Solution {
    public int[] findRedundantConnection(int[][] edges) {
        int[] parent = new int[20001];
        for(int i=0;i<parent.length;i++){
            parent[i] = i;
        }

        for(int[] ele:edges){
            int index1 = findparent(parent,ele[0]);
            int index2 = findparent(parent,ele[1]);
            if(index1==index2){
                return ele;
            }else{
                parent[index1] = index2;
            }
        }

        return new int[0];
    }

    public int findparent(int[] parent,int index){
        while(index!=parent[index]){
            parent[index] = parent[parent[index]];
            index = parent[index];
        }
        return index;
    }
}


//###############################  Union find + Path Compression  ###############################
 vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        vector<int> p(2000, 0);
        for(int i = 0; i < p.size(); i++ )
            p[i] = i;
        vector<int> res;
        for(auto v : edges ){
            int n1 = v[0], n2 = v[1];
            while(n1 != p[n1]) n1 = p[n1];
            while(n2 != p[n2]) n2 = p[n2];
            if( n1 == n2 )
                res = v;
            else
                p[n1] = n2;
        }
        return res;
    }

//############################### Python Union find  ###############################
class UnionFind:

    def __init__(self, N=1001):
        self.N = N
        self.id = [i for i in range(self.N)]
        self._rank = [1] * self.N

    def __root(self, x):
        while x != self.id[self.id[x]]:
            self.id[x] = self.id[self.id[x]]
            x = self.id[x]
        return x

    def find(self, p, q):
        return self.__root(p) == self.__root(q)

    def unite(self, p, q):
        i = self.__root(p)
        j = self.__root(q)
        if self._rank[j] > self._rank[i]:
            i, j = j, i
        self.id[j] = i
        self._rank[i] += self._rank[j]


class Solution:

    def findRedundantConnection(self, edges):
        """
        :type edges: List[List[int]]
        :rtype: List[int]
        """
        unionfind = UnionFind()
        for u, v in edges:
            if unionfind.find(u, v):
                return [u, v]
            unionfind.unite(u, v

