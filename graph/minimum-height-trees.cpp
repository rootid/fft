//Minimum Height Trees
//For a undirected graph with tree characteristics, we can choose any node as
//the root. The result graph is then a rooted tree. Among all possible rooted
//trees, those with minimum height are called minimum height trees (MHTs).
//Given such a graph, write a function to find all the MHTs and return a list
//of their root labels.
//Format
//The graph contains n nodes which are labeled from 0 to n - 1. You will be
//given the number n and a list of undirected edges (each edge is a pair of
//labels).
//You can assume that no duplicate edges will appear in edges. Since all edges
//are undirected, [0, 1] is the same as [1, 0] and thus will not appear
//together in edges.
//Example 1:
//Given n = 4, edges = [[1, 0], [1, 2], [1, 3]]
//        0
//        |
//        1
//       / \
//      2   3
//return [1]
//Example 2:
//Given n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]
//     0  1  2
//      \ | /
//        3
//        |
//        4
//        |
//        5
//return [3, 4]
//Hint:
//How many MHTs can a graph have at most?
//Note:
//(1) According to the definition of tree on Wikipedia: “a tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any connected graph without simple cycles is a tree.”
//(2) The height of a rooted tree is the number of edges on the longest downward path between the root and a leaf.

//################################################ O(n) : BFS traversal ################################################
vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
    vector<int> res;
    if (n == 1) {
        res.push_back(0);
        return res;
    }
    unordered_map<int, unordered_set<int> > adj;
    //undirected edge
    for (auto &entry : edges) {
        adj[entry.first].insert(entry.second);
        adj[entry.second].insert(entry.first);
    }
    vector<int> leaves;
    //pick all the leaves
    for (auto & entry : adj) {
        if (adj[entry.first].size() == 1) {
            leaves.push_back(entry.first);
        }
    }
    //repeat untill we left with 1/2 vertices
    while(n > 2) {
        n -= leaves.size();
        vector<int> nextLeaves;
        for (int idx = 0; idx < leaves.size(); idx++) {
            int nextNode = *(adj[leaves[idx]].begin()); //leaves[idx] : leaf node // nextNode : non-leaf node
            adj[nextNode].erase(leaves[idx]); //remove the leaf node from next non-leaf node adjaceny
            adj.erase(leaves[idx]); //Remove the leaf node
            //if nextnode is leave
            if (adj[nextNode].size() == 1) {
              nextLeaves.push_back(nextNode);
            }
        }
        leaves = nextLeaves;
    }
    return leaves;
}
