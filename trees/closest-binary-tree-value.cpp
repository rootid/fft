//Closest Leaf in a Binary Tree
//Given a binary tree where every node has a unique value, and a target key k, find the value of the nearest leaf node to target k in the tree.
//Here, nearest to a leaf means the least number of edges travelled on the binary tree to reach any leaf of the tree. Also, a node is called a leaf if it has no children.
//In the following examples, the input tree is represented in flattened form row by row. The actual root tree given will be a TreeNode object.
//Example 1:
//Input:
//root = [1, 3, 2], k = 1
//Diagram of binary tree:
//          1
//         / \
//        3   2
//Output: 2 (or 3)
//Explanation: Either 2 or 3 is the nearest leaf node to the target of 1.
//Example 2:
//Input:
//root = [1], k = 1
//Output: 1
//Explanation: The nearest leaf node is the root node itself.
//Example 3:
//Input:
//root = [1,2,3,4,null,null,null,5,null,6], k = 2
//Diagram of binary tree:
//             1
//            / \
//           2   3
//          /
//         4
//        /
//       5
//      /
//     6
//Output: 3
//Explanation: The leaf node with value 3 (and not the leaf node with value 6) is nearest to the node with value 2.
//Note:
//    root represents a binary tree with at least 1 node and at most 1000 nodes.
//    Every node has a unique node.val in range [1, 1000].
//    There exists some node in the given binary tree for which node.val == k.
//

//######################################### Annotate the leaf #########################################
class Solution {
    List<TreeNode> path;
    Map<TreeNode, LeafResult> annotation;

    public int findClosestLeaf(TreeNode root, int k) {
        path = new ArrayList();
        annotation = new HashMap();

        dfs(root, k);

        int distanceFromTarget = path.size() - 1;
        int dist = Integer.MAX_VALUE;
        TreeNode leaf = null;
        for (TreeNode node: path) {
            LeafResult lr = closestLeaf(node);
            if (lr.dist + distanceFromTarget < dist) {
                dist = lr.dist + distanceFromTarget;
                leaf = lr.node;
            }
            distanceFromTarget--;
        }
        return leaf.val;
    }

    public boolean dfs(TreeNode node, int k) {
        if (node == null) {
            return false;
        } else if (node.val == k) {
            path.add(node);
            return true;
        } else {
            path.add(node);
            boolean ans = dfs(node.left, k);
            if (ans) return true;
            ans = dfs(node.right, k);
            if (ans) return true;
            path.remove(path.size() - 1);
            return false;
        }
    }

    public LeafResult closestLeaf(TreeNode root) {
        if (root == null) {
            return new LeafResult(null, Integer.MAX_VALUE);
        } else if (root.left == null && root.right == null) {
            return new LeafResult(root, 0);
        } else if (annotation.containsKey(root)) {
            return annotation.get(root);
        } else {
            LeafResult r1 = closestLeaf(root.left);
            LeafResult r2 = closestLeaf(root.right);
            LeafResult ans = new LeafResult(r1.dist < r2.dist ? r1.node : r2.node,
                                            Math.min(r1.dist, r2.dist) + 1);
            annotation.put(root, ans);
            return ans;
        }
    }
}
class LeafResult {
    TreeNode node;
    int dist;
    LeafResult(TreeNode n, int d) {
        node = n;
        dist = d;
    }
}

//######################################### Convert to graph #########################################
class Solution {
    public int findClosestLeaf(TreeNode root, int k) {
        Map<TreeNode, List<TreeNode>> graph = new HashMap();
        dfs(graph, root, null);

        Queue<TreeNode> queue = new LinkedList();
        Set<TreeNode> seen = new HashSet();

        for (TreeNode node: graph.keySet()) {
            if (node != null && node.val == k) {
                queue.add(node);
                seen.add(node);
            }
        }

        while (!queue.isEmpty()) {
            TreeNode node = queue.poll();
            if (node != null) {
                if (graph.get(node).size() <= 1)
                    return node.val;
                for (TreeNode nei: graph.get(node)) {
                    if (!seen.contains(nei)) {
                        seen.add(nei);
                        queue.add(nei);
                    }
                }
            }
        }
        throw null;
    }

    public void dfs(Map<TreeNode, List<TreeNode>> graph, TreeNode node, TreeNode parent) {
        if (node != null) {
            if (!graph.containsKey(node)) graph.put(node, new LinkedList<TreeNode>());
            if (!graph.containsKey(parent)) graph.put(parent, new LinkedList<TreeNode>());
            graph.get(node).add(parent);
            graph.get(parent).add(node);
            dfs(graph, node.left, node);
            dfs(graph, node.right, node);
        }
    }
}

//######################################### bfs + DFS  #########################################

class Solution {

    public int findClosestLeaf(TreeNode root, int k) {
        Map<TreeNode, TreeNode> backMap = new HashMap<>();   // store all edges that trace node back to its parent
        Queue<TreeNode> queue = new LinkedList<>();          // the queue used in BFS
        Set<TreeNode> visited = new HashSet<>();             // store all visited nodes

        // DFS: search for node whoes val == k
        TreeNode kNode = DFS(root, k, backMap);
        queue.add(kNode);
        visited.add(kNode);

        // BFS: find the shortest path
        while(!queue.isEmpty()) {
            TreeNode curr = queue.poll();
            if(curr.left == null && curr.right == null) {
                return curr.val;
            }
            if(curr.left != null && visited.add(curr.left)) {
                queue.add(curr.left);
            }
            if(curr.right != null && visited.add(curr.right)) {
                queue.add(curr.right);
            }
            if(backMap.containsKey(curr) && visited.add(backMap.get(curr))) {  // go alone the back edge
                queue.add(backMap.get(curr));
            }
        }
        return -1; // never hit
    }

    private TreeNode DFS(TreeNode root, int k, Map<TreeNode, TreeNode> backMap) {
        if(root.val == k) {
            return root;
        }
        if(root.left != null) {
            backMap.put(root.left, root);        // add back edge
            TreeNode left = DFS(root.left, k, backMap);
            if(left != null) return left;
        }
        if(root.right != null) {
            backMap.put(root.right, root);       // add back edge
            TreeNode right = DFS(root.right, k, backMap);
            if(right != null) return right;
        }
        return null;
    }

}


//######################################### bfs #########################################
//
//             1
//            / \
//           2   3
//          /
//         4
//        /
//       5
//      /
//     6
//
//the graph dict and leaves set look like:
//
//# graph
//{
//  1: [2, 3],
//  2: [1, 4],
//  3: [1],
//  4: [2, 5],
//  5: [4, 6],
//  6: [5],
//}
//
//# leaves
//{3, 6}
class Solution(object):
    def findClosestLeaf(self, root, k):
        # Time: O(n)
        # Space: O(n)
        from collections import defaultdict
        graph, leaves = defaultdict(list), set()
        # Graph construction
        def traverse(node):
            if not node:
                return
            if not node.left and not node.right:
                leaves.add(node.val)
                return
            if node.left:
                graph[node.val].append(node.left.val)
                graph[node.left.val].append(node.val)
                traverse(node.left)
            if node.right:
                graph[node.val].append(node.right.val)
                graph[node.right.val].append(node.val)
                traverse(node.right)
        traverse(root)
        # Graph traversal - BFS
        queue = [k]
        while len(queue):
            next_queue = []
            for node in queue:
                if node in leaves:
                    return node
                next_queue += graph.pop(node, [])
            queue = next_queue
