//Graph Valid Tree
//Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), write a function to check whether these edges make up a valid tree.
// Notice
//You can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.
//Example
//Given n = 5 and edges = [[0, 1], [0, 2], [0, 3], [1, 4]], return true.
//Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [1, 3], [1, 4]], return false.

//######################################### Union Find ######################################### 
//Tree must have unique parent,if node shares 2 parent then graph is not a valid tree
//TODO : In case of self loop find will recursively iterate over the same recursive function. (Req fix).
public class Solution {
    public boolean validTree(int n, int[][] edges) {
        // initialize n isolated islands
        int[] nums = new int[n];
        Arrays.fill(nums, -1);
        
        // perform union find
        for (int i = 0; i < edges.length; i++) {
            int x = find(nums, edges[i][0]);
            int y = find(nums, edges[i][1]);
            
            // if two vertices happen to be in the same set
            // then there's a cycle
            if (x == y) return false; 
            
            // union
            nums[x] = y;
        }
        
        return edges.length == n - 1;
    }
    
    private int find(int nums[], int i) {
        if (nums[i] == -1) return i; //first visit of the vertex
        return find(nums, nums[i]);  
    }
}

//######################################### Cycle Test ######################################### 
//To tell whether a graph is a valid tree, we have to: (necessary and sufficient condition)
//1. Make sure there is no cycle in the graph - this has to be a none-cyclic graph;
//2. Make sure every node is reached - this has to be a connected graph;
//Modified version of union find
//
//1. To test cyclic, we can make an array for each node (as array index), and the array will store the parent of the node (as array index). Every time we fetch a new pair of nodes, we trace the root node (the deepest parent node) of these two nodes, if it has the same root, then is will be a cycle; otherwise, we set the parent of second node to be the first node;
//2. After we make sure there is node cycle in the graph, we simple test if there is enough edges to make this graph connected.
bool validTree(int n, vector<pair<int, int>>& edges) {
    vector<int> nodes(n,0);
    for(int i=0; i<n; i++) nodes[i] = i;
    for(int i=0; i<edges.size(); i++){
		//pick the vertices
        int f = edges[i].first;
        int s = edges[i].second;
		//Improve the speed by path compression 
		//if using compatization by adding nodes[f] = nodes[nodes[f]]; // and similar for s in the root searching loops.
        while(nodes[f] != f) f = nodes[f]; //find the parent of vertiex f
        while(nodes[s] != s) s = nodes[s]; //find the parent of vertiex s
        if(nodes[f] == nodes[s]) return false; //if both the vertices share the same parent then graph is not tree
        nodes[s] = f; //union
    } 
	//For given valid tree # of edges = n-1 where n = # of vertices 
	return edges.size() == n-1; 
}

//######################################### Union Find ######################################### 
//In all of them, I check one of these tree characterizations:
//Has n-1 edges and is acyclic.
//Has n-1 edges and is connected.
//Solution 1 ... Union-Find

def validTree(self, n, edges):
    parent = range(n)
    def find(x):
        return x if parent[x] == x else find(parent[x])
    def union(xy):
        x, y = map(find, xy)
        parent[x] = y
        return x != y
    return len(edges) == n-1 and all(map(union, edges))

//A version without using all(...), to be closer to other programming languages:

//######################################### Union Find ######################################### 
def validTree(self, n, edges):
    parent = range(n)
    def find(x):
        return x if parent[x] == x else find(parent[x])
    for e in edges:
        x, y = map(find, e)
        if x == y:
            return False
        parent[x] = y
    return len(edges) == n - 1
//A version checking len(edges) != n - 1 first, as parent = range(n) could fail for huge n:

//######################################### Union Find ######################################### 
def validTree(self, n, edges):
    if len(edges) != n - 1:
        return False
    parent = range(n)
    def find(x):
        return x if parent[x] == x else find(parent[x])
    def union(xy):
        x, y = map(find, xy)
        parent[x] = y
        return x != y
    return all(map(union, edges))

//######################################### DFS ######################################### 
def validTree(self, n, edges):
    neighbors = {i: [] for i in range(n)}
    for v, w in edges:
        neighbors[v] += w,
        neighbors[w] += v,
    def visit(v):
        map(visit, neighbors.pop(v, []))
    visit(0)
    return len(edges) == n-1 and not neighbors

//######################################### Fast DFS ######################################### 
//Or check the number of edges first, to be faster and to survive unreasonably huge n:

def validTree(self, n, edges):
    if len(edges) != n - 1:
        return False
    neighbors = {i: [] for i in range(n)}
    for v, w in edges:
        neighbors[v] += w,
        neighbors[w] += v,
    def visit(v):
        map(visit, neighbors.pop(v, []))
    visit(0)
    return not neighbors
//For an iterative version, just replace the three "visit" lines with
    stack = [0]
    while stack:
        stack += neighbors.pop(stack.pop(), [])

//######################################### BFS ######################################### 
//Just like DFS above, but replace the three "visit" lines with
    queue = [0]
    for v in queue:
        queue += neighbors.pop(v, [])
or, since that is not guaranteed to work, the safer

    queue = collections.deque([0])
    while queue:
        queue.extend(neighbors.pop(queue.popleft(), []))

//######################################### Union Find cpp  ######################################### 

class Solution {
public:
    bool validTree(int n, vector<pair<int, int>>& edges) {
        if(edges.size() != n-1) return false;
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        for(auto e : edges) {
            auto x = find(e.first), y = find(e.second);
            if(x == y) return false;
            parent[x] = y;
        }
        return true;
    }
private:
    vector<int> parent;
    int find(int x) {
        return parent[x] == x ? x : find(parent[x]);
    }
};
