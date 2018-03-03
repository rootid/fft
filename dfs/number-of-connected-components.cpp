//Number of Connected Components in an Undirected Graph
//Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each
//edge is a pair of nodes), write a function to find the number of connected
//components in an undirected graph.
//Example 1:
//     0          3
//     |          |
//     1 --- 2    4
//Given n = 5 and edges = [[0, 1], [1, 2], [3, 4]], return 2.
//Example 2:
//     0           4
//     |           |
//     1 --- 2 --- 3
//Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [3, 4]], return 1.
//Note:
//You can assume that no duplicate edges will appear in edges. Since all edges
//are undirected, [0, 1] is the same as [1, 0] and thus will not appear
//together in edges.

//######################################### Union Find + Path Compression  #########################################
//M quick union + path compression on N objects should be N + MlgN, In this
//problem, M = 2E, N = V, so O(V + 2ElgV),
//1. n points = n islands = n trees = n roots.
//2. With each edge added, check which island is e[0] or e[1] belonging to.
//3. If e[0] and e[1] are in same islands, do nothing.
//4. Otherwise, union two islands, and reduce islands count by 1.
//5. Bonus: path compression can reduce time by 50%.
public int countComponents(int n, int[][] edges) {
	//In all connected components return n.
    int[] roots = new int[n];
	//initialization to add the roots
    for(int i = 0; i < n; i++) {
		roots[i] = i;
	}
    for(int[] e : edges) {
        int from = findRoot(roots, e[0]); //from
        int to = findRoot(roots, e[1]); //to
        if(from != to) {   //no parent found
            roots[from] = to;  // union or join
            n--;
        }
    }
    return n;
}

public int findRoot(int[] roots, int id) {
    while(roots[id] != id) { //find "to" value in case of connected components.
        roots[id] = roots[roots[id]];  // optional: path compression
        id = roots[id];
    }
    return id;
}

//######################################### DFS #########################################
//1. start dfsVisit with sources 0-n-1,
//2. count number of unvisited sources.
public class Solution {
    public int countComponents(int n, int[][] edges) {
        if (n <= 1)
            return n;
        Map<Integer, List<Integer> > map = new HashMap<>();
        for (int i = 0; i < n; i++) {
            map.put(i, new ArrayList<>()); //<edge_id, List<adj_next_edge>>
        }
        for (int[] edge : edges) {
            map.get(edge[0]).add(edge[1]);
            map.get(edge[1]).add(edge[0]);
        }
        Set<Integer> visited = new HashSet<>(); //keep track of visited vertices
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (visited.add(i)) {  //if newly added vertex returns true, existing or repated vertex return false
                dfsVisit(i, map, visited);
                count++;
            }
        }
        return count;
    }

	//TODO :NEED to check visited set updates or not
    private void dfsVisit(int i, Map<Integer, List<Integer>> map, Set<Integer> visited) {
		//retrieve adjacent vertices from the list
        for (int j : map.get(i)) {
            if (visited.add(j)) { //check already visited vertex
				dfsVisit(j, map, visited);
			}
        }
    }
}

//######################################### DFS traversal #########################################
//SC : O(n)
//TC : O(n)
class Solution {
public:
    int countComponents(int n, vector<pair<int, int>>& edges) {
        unordered_map<int, vector<int> > graph;
        unordered_set<int> visited;
        int counter = 0;
        for (auto e : edges) {
            graph[e.first].push_back(e.second);
            graph[e.second].push_back(e.first);
        }
        for (int node = 0; node < n; node++) {
            if (!visited.count(node)) {
                counter++;
                dfs(graph, visited, node);
            }
        }
        return counter;
    }
    void dfs(unordered_map<int, vector<int>> &graph, unordered_set<int> &visited, int node) {
        for (int neigh : graph[node]) {
            if (visited.count(neigh)) continue;
            visited.insert(neigh);
            dfs(graph, visited, neigh);
        }
    }
};

//######################################### DFS #########################################
def countComponents(n, edges):
        def dfs(n, g, visited):
            if visited[n]:
                return
            visited[n] = 1
            for x in g[n]:
                dfs(x, g, visited)

        visited = [0] * n
        g = {x:[] for x in xrange(n)}
        for x, y in edges:
            g[x].append(y)
            g[y].append(x)

        ret = 0
        for i in xrange(n):
            if not visited[i]:
                dfs(i, g, visited)
                ret += 1
        return ret

//######################################### BFS  #########################################
def countComponents(n, edges):
        g = {x:[] for x in xrange(n)}
        for x, y in edges:
            g[x].append(y)
            g[y].append(x)

        ret = 0
        for i in xrange(n):
            queue = [i]
            ret += 1 if i in g else 0
            for j in queue:
                if j in g:
                    queue += g[j]
                    del g[j]

        return ret

//######################################### Union Find  #########################################
def countComponents(n, edges):
        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]

        def union(xy):
            x, y = map(find, xy)
            if rank[x] < rank[y]:
                parent[x] = y
            else:
                parent[y] = x
                if rank[x] == rank[y]:
                    rank[x] += 1

        parent, rank = range(n), [0] * n
        map(union, edges)
        return len({find(x) for x in parent})

//######################################### Union Find  #########################################
def countComponents(self, n, edges):
    p = range(n)
    def find(v):
        if p[v] != v:
            p[v] = find(p[v])
        return p[v]
    for v, w in edges:
        p[find(v)] = find(w)
    return len(set(map(find, p)))


//######################################### Union Find  #########################################
def countComponents(self, n, edges):
    p = range(n)
    def find(v):
        if p[v] != v:
            p[v] = find(p[v])
        return p[v]
    for e in edges:
        v, w = map(find, e)
        p[v] = w
        n -= v != w
    return n

//######################################### Union Find  #########################################
int countComponents(int n, vector<pair<int, int>>& edges) {
    vector<int> p(n);
    iota(begin(p), end(p), 0);
    for (auto& edge : edges) {
        int v = edge.first, w = edge.second;
        while (p[v] != v) v = p[v] = p[p[v]];
        while (p[w] != w) w = p[w] = p[p[w]];
        p[v] = w;
        n -= v != w;
    }
    return n;
}

//######################################### Union Find  #########################################
int countComponents(int n, vector<pair<int, int>>& edges) {
    vector<int> p(n);
    iota(begin(p), end(p), 0);
    function<int (int)> find = [&](int v) {
        return p[v] == v ? v : p[v] = find(p[v]);
    };
    for (auto& edge : edges) {
        int v = find(edge.first), w = find(edge.second);
        p[v] = w;
        n -= v != w;
    }
    return n;
}
