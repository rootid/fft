//Clone Graph
//Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors.
//OJ's undirected graph serialization:
//Nodes are labeled uniquely.
//We use # as a separator for each node, and , as a separator for node label and each neighbor of the node.
//As an example, consider the serialized graph {0,1,2#1,2#2,2}.
//The graph has a total of three nodes, and therefore contains three parts as separated by #.
//First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
//Second node is labeled as 1. Connect node 1 to node 2.
//Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a self-cycle.
//Visually, the graph looks like the following:
//       1
//      / \
//     /   \
//    0 --- 2
//         / \
//         \_/

//######################################### DFS  ######################################### 
public UndirectedGraphNode cloneGraph(UndirectedGraphNode node) {
    if(node == null) return node;
    Stack<UndirectedGraphNode> vStack = new Stack<>();
    Map<UndirectedGraphNode, UndirectedGraphNode> storeMap = new HashMap<>();
    vStack.push(node);
    storeMap.put(node, new UndirectedGraphNode(node.label));
    while(!vStack.isEmpty()) {
        UndirectedGraphNode tmpNode = vStack.pop();
        for(UndirectedGraphNode nbrNode: tmpNode.neighbors) {
            if(!storeMap.containsKey(nbrNode)) {
                storeMap.put(nbrNode,new UndirectedGraphNode(nbrNode.label));
                vStack.push(nbrNode);
            }
			//establish adjacency A<->B : 1.A 2.B 3. A->B 4. B<-A
            storeMap.get(tmpNode).neighbors.add(storeMap.get(nbrNode));
        }
    }
    return storeMap.get(node);
}

//######################################### Recursion/DFS  ######################################### 
class Solution {
    Map<UndirectedGraphNode, UndirectedGraphNode> storeMap = new HashMap<>();
    //BFS  , DFS  (traversal -> maintain adjacency)
    public UndirectedGraphNode cloneGraph(UndirectedGraphNode node) {
        if(node == null) return node;
        if (!storeMap.containsKey(node)) {
            storeMap.put(node, new UndirectedGraphNode(node.label));
            for (UndirectedGraphNode nbr : node.neighbors)
                storeMap.get(node).neighbors.add(cloneGraph(nbr));
        }
    return storeMap.get(node);
}


//######################################### BFS ######################################### 
class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if (!node) return NULL;
        UndirectedGraphNode* copy = new UndirectedGraphNode(node -> label);
        mp[node] = copy;
        queue<UndirectedGraphNode*> toVisit;
        toVisit.push(node);
        while (!toVisit.empty()) {
            UndirectedGraphNode* cur = toVisit.front();
            toVisit.pop();
            for (UndirectedGraphNode* neigh : cur -> neighbors) {
                if (mp.find(neigh) == mp.end()) {
                    UndirectedGraphNode* neigh_copy = new UndirectedGraphNode(neigh -> label);
                    mp[neigh] = neigh_copy;
                    toVisit.push(neigh);
                }
                mp[cur] -> neighbors.push_back(mp[neigh]);
            }
        }
        return copy; 
    }
private:
    unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> mp;
};

//######################################## DFS Recursive  ######################################## 
class Solution(object):
    def __init__(self):
        self.visited = {}
        
    def cloneGraph(self, node):
        if not node:
            return None
        if node.label in self.visited:
            return self.visited[node.label]

        clone = UndirectedGraphNode(node.label)
        self.visited[node.label] = clone
            
        for n in node.neighbors:
            clone.neighbors.append(self.cloneGraph(n))
        return clone

//######################################## DFS Stack ######################################## 
def cloneGraph(self, node):
    if not node:
        return node
    root = UndirectedGraphNode(node.label)
    stack = [node]
    visit = {}
    visit[node.label] = root
    while stack:
        top = stack.pop()
        for n in top.neighbors:
            if n.label not in visit:
                stack.append(n)
                visit[n.label] = UndirectedGraphNode(n.label)
            visit[top.label].neighbors.append(visit[n.label])
    
    return root
